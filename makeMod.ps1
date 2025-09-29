<# 
.SYNOPSIS
  Build DeathRun mod.ff for CoD4 (robocopy edition)

.DESCRIPTION
  - Deletes local mod.ff
  - Uses robocopy to sync directories into ..\..\raw (quiet, folder-by-folder logs only)
  - Copies a few single files into ..\..\raw and ..\..\zone_source
  - Runs linker_pc.exe from ..\..\bin
  - Copies built zone\english\mod.ff back to the current mod folder
#>

[CmdletBinding()]
param(
  # Root of your CoD4 install (defaults to two levels up from this script)
  [string]$GameRoot = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path,

  # Optional: show “Press Enter to exit” at the end
  [switch]$PauseOnExit
)

# ---------- Pretty output helpers (emoji as strings; no [char] casting) ----------
$Check  = "✅"
$Cross  = "❌"
$Gear   = "⚙"
$Truck  = "🚚"
$Disk   = "💾"
$Zap    = "⚡"
$Broom  = "🧹"

function Write-Step($msg) { Write-Host "$Gear  $msg" -ForegroundColor Cyan }
function Write-Done($msg) { Write-Host "$Check $msg" -ForegroundColor Green }
function Write-Info($msg) { Write-Host "  - $msg " -ForegroundColor Gray }
function Write-Fail($msg) { Write-Host "$Cross $msg" -ForegroundColor Red }

# Fail fast on errors; keep terse output
$ErrorActionPreference = 'Stop'

# Ensure we're running from the mod folder
$ModDir = $PSScriptRoot

# Important paths
$RawDir        = Join-Path $GameRoot 'raw'
$ZoneSourceDir = Join-Path $GameRoot 'zone_source'
$BinDir        = Join-Path $GameRoot 'bin'
$ZoneEnglish   = Join-Path $GameRoot 'zone\english'

# Quick sanity check
if (-not (Test-Path $RawDir) -or -not (Test-Path $ZoneSourceDir) -or -not (Test-Path $BinDir)) {
  Write-Fail "Could not find expected CoD4 directories under '$GameRoot'."
  Write-Info "Expected: 'raw', 'zone_source', 'bin'."
  exit 1
}

# Warn if not elevated and path is under Program Files
$needsAdmin = $GameRoot -match '\\Program Files'
if ($needsAdmin -and -not ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()
  ).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
  Write-Info "You are not running as Administrator, and your game path is under Program Files."
  Write-Info "This may cause 'Access is denied' during copies. Consider re-running PowerShell as Administrator."
}

# ---------- Helpers ----------
# Robocopy wrapper: quiet, fast, error-aware. Matches xcopy /S (no empty dirs), overwrite when newer/different.
function Invoke-RoboCopy($Source, $Dest) {
  if (-not (Test-Path $Source)) { Write-Info "Skipping missing folder: $(Split-Path -Leaf $Source)"; return }
  if (-not (Test-Path $Dest))   { New-Item -Force -ItemType Directory -Path $Dest | Out-Null }

  # Announce just the folder being copied
  Write-Host "$Truck  $(Split-Path -Leaf $Source)  ->  $([System.IO.Path]::GetFileName($Dest))" -ForegroundColor Yellow

  # /S        subdirs, skip empty (like xcopy /S)
  # /R:2      retry twice on locked files
  # /W:1      1s wait between retries
  # /MT:16    multithread (adjust if disk is slow)
  # /NFL      no file list
  # /NDL      no directory list
  # /NJH /NJS no header/summary
  # /NP       no progress per file
  # /XO       skip older destination (keeps speed high; still updates changed files)
  robocopy $Source $Dest /S /R:2 /W:1 /MT:16 /NFL /NDL /NJH /NJS /NP /XO | Out-Null

  # Robocopy exit code bitmask: 0/1/2/3/5/6/7 are success-ish; >=8 is failure
  $code = $LASTEXITCODE
  if ($code -ge 8) {
    throw "ROBOCOPY failed ($Source -> $Dest) with exit code $code"
  }
}

# Copy one file to a folder (quiet).
function Copy-One($FilePath, $DestFolder) {
  if (-not (Test-Path $FilePath)) { Write-Info "Missing $(Split-Path -Leaf $FilePath) (skipped)"; return }
  if (-not (Test-Path $DestFolder)) { New-Item -Force -ItemType Directory -Path $DestFolder | Out-Null }
  Copy-Item -Force -LiteralPath $FilePath -Destination $DestFolder
}

try {
  # ---------- 1) Clean local mod.ff ----------
  Write-Step "$Broom Removing local mod.ff (if present)"
  $LocalModFF = Join-Path $ModDir 'mod.ff'
  if (Test-Path $LocalModFF) {
    Remove-Item -Force $LocalModFF
    Write-Done "Deleted $LocalModFF"
  } else {
    Write-Info "No local mod.ff to delete."
  }

  # ---------- 2) Directory copies to raw (ROBOCOPY, quiet per-folder) ----------
  Write-Step "$Truck Copying directories to RAW (quiet)"
  $CopyMap = @(
    @{ src = 'animtrees';           dst = 'animtrees' }
    @{ src = 'braxi';               dst = 'braxi' }
    @{ src = 'hype';                dst = 'hype' }
    @{ src = 'plugins';             dst = 'plugins' }
    @{ src = 'english';             dst = 'english' }
    @{ src = 'fx';                  dst = 'fx' }
    @{ src = 'images';              dst = 'images' }
    @{ src = 'maps';                dst = 'maps' }
    @{ src = 'material_properties'; dst = 'material_properties' }
    @{ src = 'materials';           dst = 'materials' }
    @{ src = 'info';                dst = 'info' }
    @{ src = 'mp';                  dst = 'mp' }
    @{ src = 'shaders';             dst = 'shaders' }
    @{ src = 'soundaliases';        dst = 'soundaliases' }
    @{ src = 'sound';               dst = 'sound' }
    @{ src = 'techniques';          dst = 'techniques' }
    @{ src = 'techsets';            dst = 'techsets' }
    @{ src = 'ui';                  dst = 'ui' }
    @{ src = 'ui_mp';               dst = 'ui_mp' }
    @{ src = 'weapons';             dst = 'weapons' }
    @{ src = 'vision';              dst = 'vision' }
    @{ src = 'xanim';               dst = 'xanim' }
    @{ src = 'xmodel';              dst = 'xmodel' }
    @{ src = 'xmodelparts';         dst = 'xmodelparts' }
    @{ src = 'xmodelsurfs';         dst = 'xmodelsurfs' }
  )

  foreach ($item in $CopyMap) {
    $src = Join-Path $ModDir $item.src
    $dst = Join-Path $RawDir $item.dst
    Invoke-RoboCopy -Source $src -Dest $dst
  }
  Write-Done "Folder sync to RAW complete."

  # ---------- 3) File copies to raw / zone_source (quiet) ----------
  Write-Step "$Disk Copying single files"
  Copy-One (Join-Path $ModDir 'DeathRun_ReadMe.txt') $RawDir
  Copy-One (Join-Path $ModDir 'cleanup.cfg')         $RawDir
  Copy-One (Join-Path $ModDir 'mod.csv')             $ZoneSourceDir
  Write-Done "File copies complete."

  # ---------- 4) Build: linker_pc.exe ----------
  Write-Step "$Zap Running linker_pc.exe"
  Push-Location $BinDir
  $proc = Start-Process -FilePath (Join-Path $BinDir 'linker_pc.exe') `
                        -ArgumentList @('-language','english','-compress','-cleanup','mod') `
                        -NoNewWindow -Wait -PassThru
  if ($proc.ExitCode -ne 0) { throw "linker_pc.exe returned exit code $($proc.ExitCode)" }
  Pop-Location
  Write-Done "linker_pc.exe finished successfully."

  # ---------- 5) Bring mod.ff back to mod folder ----------
  Write-Step "$Truck Copying built mod.ff back to mod folder"
  $BuiltModFF = Join-Path $ZoneEnglish 'mod.ff'
  if (-not (Test-Path $BuiltModFF)) { throw "Expected '$BuiltModFF' was not produced." }
  Copy-Item -Force -LiteralPath $BuiltModFF -Destination $ModDir
  Write-Done "Copied mod.ff to '$ModDir'."

  Write-Host ""
  Write-Done "All done!"
  if ($PauseOnExit) { [void](Read-Host "Press Enter to exit") }
}
catch {
  Write-Fail "Build failed: $($_.Exception.Message)"
  if ($PauseOnExit) { [void](Read-Host "Press Enter to exit") }
  exit 1
}
