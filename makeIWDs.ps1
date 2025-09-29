<#
.SYNOPSIS
  Build IWD archives with local 7z.exe (same folder as script), using a simple config.

.EDITING
  - Modify the CONFIG section ($Archives) to control which files/folders
    go into which IWD.
  - Paths are relative to the script folder.

.EXAMPLE
  PS> .\makeIWDs.ps1
#>

[CmdletBinding()]
param(
  [switch]$PauseOnExit
)

# =========================
# ======== CONFIG =========
# =========================
# Define which items go into which IWD.
# - Name  : output IWD file name
# - Items : array of folders/files (relative to script folder)
$Archives = @(
  @{
    Name  = 'dx_images.iwd'
    Items = @(
      'images',
      'dr_sprays.cfg'
    )
  },
  @{
    Name  = 'dx_sounds.iwd'
    Items = @(
      'sound',
      'dr_songs.cfg'
    )
  },
  @{
    Name = 'dx_weapons.iwd'
    Items = @(
      'weapons'
    )
  },
  @{
    Name = 'dx_misc.iwd'
    Items = @(
      'deathrun_readme.txt'
    )
  }
)
# =========================
# ====== END CONFIG =======
# =========================

# ---------- Pretty output helpers ----------
$Check  = "✅"
$Cross  = "❌"
$Gear   = "⚙"
$Truck  = "📦"
$Broom  = "🧹"

function Write-Step($msg) { Write-Host "$Gear  $msg" -ForegroundColor Cyan }
function Write-Done($msg) { Write-Host "$Check $msg" -ForegroundColor Green }
function Write-Info($msg) { Write-Host "  - $msg " -ForegroundColor Gray }
function Write-Fail($msg) { Write-Host "$Cross $msg" -ForegroundColor Red }

$ErrorActionPreference = 'Stop'
$BaseDir = $PSScriptRoot
$SevenZip = Join-Path $BaseDir '7z.exe'

if (-not (Test-Path $SevenZip)) {
  Write-Fail "7z.exe not found in $BaseDir"
  exit 1
}

function Invoke-7zZip {
  param(
    [Parameter(Mandatory)] [string]$ArchivePath,
    [Parameter(Mandatory)] [string[]]$Items
  )

  $archiveFull = Join-Path $BaseDir $ArchivePath

  # Remove old archive if it exists
  if (Test-Path $archiveFull) { Remove-Item -Force $archiveFull }

  # Filter only existing sources
  $sources = @()
  foreach ($i in $Items) {
    $full = Join-Path $BaseDir $i
    if (Test-Path -LiteralPath $full) {
      $sources += "`"$full`""
    } else {
      Write-Info "Skipping missing: $i"
    }
  }

  if ($sources.Count -eq 0) {
    throw "No inputs found for $ArchivePath"
  }

  Write-Host "$Truck $(Split-Path -Leaf $ArchivePath)" -ForegroundColor Yellow

  # Quiet 7-zip (supported on modern 7z.exe)
  $args = @('a','-r','-tzip','-bso0','-bsp0','-bse0',"`"$archiveFull`"") + $sources

  $p = Start-Process -FilePath $SevenZip -ArgumentList $args -NoNewWindow -Wait -PassThru
  if ($p.ExitCode -ne 0) { throw "7z failed for $ArchivePath (exit $($p.ExitCode))" }
}

try {
  # ---------- Cleanup ----------
  Write-Step "$Broom Cleaning old IWDs"
  foreach ($def in $Archives) {
    $target = Join-Path $BaseDir $def.Name
    if (Test-Path $target) {
      Remove-Item -Force $target
      Write-Info "Deleted $($def.Name)"
    }
  }
  Write-Done "Cleanup complete."

  # ---------- Build archives from config ----------
  foreach ($def in $Archives) {
    Write-Step "Packing $($def.Name)"
    Invoke-7zZip -ArchivePath $def.Name -Items $def.Items
    Write-Done "$($def.Name) created."
  }

  Write-Host ""
  Write-Done "All IWDs built successfully."
}
catch {
  Write-Fail $_
  if ($PauseOnExit) { [void](Read-Host "Press Enter to exit") }
  exit 1
}

if ($PauseOnExit) { [void](Read-Host "Press Enter to exit") }
