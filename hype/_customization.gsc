#include maps\mp\_utility;
#include common_scripts\utility;
#include maps\mp\gametypes\_hud_util;

#include braxi\_common;
#include braxi\_dvar;

init()
{
  level.characterInfo = [];
  level.itemInfo = [];
  level.numItems = 0;
  level.numCharacters = 0;
  
  tables=[];
  tables[0] = "mp/itemTable.csv";
  tables[1] = "mp/characterTable.csv";

  for(i = 0; i < tables.size; i++)
  {
    for(idx=1;isdefined(tablelookup(tables[i],0,idx,0)) && tablelookup(tables[i],0,idx,0)!="";idx++)
    {
      id=int(tablelookup(tables[i],0,idx,1));
      if(tables[i] == "mp/itemTable.csv")
      {
        level.itemInfo[id]["rank"]=(int(tablelookup(tables[i],0,idx,2))-1);
        level.itemInfo[id]["item"]=(tablelookup(tables[i],0,idx,3)+"_mp");
        level.itemInfo[id]["model"]=tablelookup(tables[i],0,idx,4);
        level.itemInfo[id]["name"]=tablelookup(tables[i],0,idx,5);
        level.itemInfo[id]["prestige"]=int(tablelookup(tables[i],0,idx,6));

        precachemodel(level.itemInfo[id]["model"]);
        precacheitem(level.itemInfo[id]["item"]);

        level.numItems++;
      }
      else if(tables[i] == "mp/characterTable.csv")
      {
        level.characterInfo[id]["rank"]=(int(tablelookup(tables[i],0,idx,2))-1);
        level.characterInfo[id]["model"]=tablelookup(tables[i],0,idx,3);
        level.characterInfo[id]["name"]=tablelookup(tables[i],0,idx,4);
        level.characterInfo[id]["prestige"]=int(tablelookup(tables[i],0,idx,5));

        precachemodel(level.characterInfo[id]["model"]);

        level.numCharacters++;
      }      
    }
  }
}

destruct() {
  for(;;) {
    self waittill("end customization");

    if(isDefined(self.previewModel))
    {
      self.previewModel delete();
    }

    // if(isDefined(self.previewHud))
    // {
    //   self.previewHud delete();
    // }

    self.pers["inCustomization"] = false;
    self.pers["customize_weapon"] = undefined;
    self.pers["customize_character"] = undefined;
  }
}

deathCheck() {
  for(;;) {
    self waittill("death");
    self notify("end customization");
    self.previewModel delete();
    self closeMenu();
    self closeInGameMenu();
  }
}

// makePreviewHud()
// {
//     self endon("disconnect");
//     self endon("end customization");

//     hud = self createFontString( "objective", 1.4 );
//     hud setPoint( "BOTTOMCENTER", "BOTTOMCENTER", 0, -64 );
//     hud.foreground = true;
//     hud.alpha = 1;
//     hud.label = "";

//     self.previewHud = hud;

//     for (;;)
//     {
//         wait 0.05; // refresh smoothly

//         if (!isDefined(self.pers["inCustomization"]) || !self.pers["inCustomization"])
//         {
//             hud setText("");
//             continue;
//         }

//         table = self.pers["customize_table"];

//         // Figure out which table we’re in
//         if (table == "weapons")
//         {
//             idx = self.pers["customize_weapon"];
//             name = getWeaponName(idx);

//             if (!(self braxi\_rank::isItemUnlocked(idx)))
//                 hud setText(name + " ^1(Unlocked at level " + (level.itemInfo[idx]["rank"]+1) + ")");
//             else
//                 hud setText(name);
//         }
//         else if (table == "characters")
//         {
//             idx = self.pers["customize_character"];
//             name = getModelName(idx);

//             if (!(self braxi\_rank::isCharacterUnlocked(idx)))
//                 hud setText(name + " ^1(Unlocked at level " + (level.characterInfo[idx]["rank"]+1) + ")");
//             else
//                 hud setText(name);
//         }
//     }
// }


onresponse(table, response)
{
  self thread deathCheck();
  self thread destruct();
  // self thread makePreviewHud();
  isSpectator = false;
  if(self.pers["team"] == "spectator") {
    isSpectator = true;
  }
  spawnangles = (0, level.spawn["spectator"].angles[1], 0);
  headangles = (0,168,0);
  model_spawn= (0,-20,0);
  persVar = "";
  switch(table) {
    case "weapons":
      model_spawn = (level.spawn["spectator"].origin+(0,0,10)+vector_scale(anglesToForward(spawnAngles), 50));
      persVar = "customize_weapon";
      break;
    case "characters":
      model_spawn = (level.spawn["spectator"].origin+(0,0,-20)+vector_scale(anglesToForward(spawnAngles), 150));
      persVar = "customize_character";
      break;
  }

  if(isSpectator) self setplayerangles(spawnangles);
  currentChar = self getStat(98);
  currentItem = self getStat(981);

  if(!isdefined(self.previewModel) && response == "open_" + table) {
    self.pers["inCustomization"] = true;
    self.pers["customize_table"] = table;
    self setClientDvar("customize_table", table);
    self closeMenu();
    self openMenu("dr_" + table);

    if(isSpectator) {
      self setorigin(level.spawn["spectator"].origin);
      self.previewModel = spawn("script_model", model_spawn);
      self.previewModel.angles = headangles;
      self.previewModel hide();
      self.previewModel showToPlayer(self);
      self thread RotatePreview();
    } else {
      if(table == "weapons") {
        item = level.itemInfo[currentItem];
        self takeAllWeapons();
        self giveWeapon(item["item"]);
        self switchToWeapon(item["item"]);
      } else if(table == "characters") {
        char = level.characterInfo[currentChar];
        self setClientDvar( "cg_thirdPerson", 1 );
        self setClientDvar( "cg_thirdPersonAngle", -180 );
        self setClientDvar( "cg_thirdPersonRange", 180 );
        self setModel(char["model"]);
      }
    }

    if(table == "weapons") {
      self.pers[persVar] = currentItem;
      self setClientDvar("drui_weapon", self.pers[persVar]);
      if(isSpectator) self.previewModel setModel(level.itemInfo[self.pers[persVar]]["model"]);
    } else if(table == "characters") {
      self.pers[persVar] = currentChar;
      self setClientDvar("drui_character", self.pers[persVar]);
      if(isSpectator) self.previewModel setModel(level.characterInfo[self.pers[persVar]]["model"]);
    }
  } else if(isdefined(self.previewModel) && response == "close_" + table) {
    self.pers["inCustomization"] = false;
    self notify("end customization");
    if(isDefined(self.previewModel)) {
      self.previewModel delete();
    }
    self.previewModel delete();
    self closeMenu();
    self closeInGameMenu();
  } else if(!isSpectator && response == "close_" + table) {
    self notify("end customization");
    if(isDefined(self.previewModel)) {
      self.previewModel delete();
    }
    if(table == "weapons") {
      self takeAllWeapons();
      item = level.itemInfo[currentItem];
      self setClientDvar("drui_weapon", currentItem);
      self giveWeapon(item["item"]);
      self giveStartAmmo(item["item"]);
      self switchToWeapon(item["item"]);
    } else if(table == "characters") {
      self setClientDvar( "cg_thirdPerson", 0 );
      self setClientDvar( "cg_thirdPersonAngle", 0 );
      self setClientDvar( "cg_thirdPersonRange", 120 );
      char = level.characterInfo[currentChar];
      self setModel(char["model"]);
    }
    self.pers["inCustomization"] = false;
    self closeMenu();
    self closeInGameMenu();
  }

  if(response == "previous" || response == "next") {
    navigate(table, response);
  } else if(response == "select") {
    select(table, self.pers[persVar]);
  }
}

RotatePreview()
{
  self endon( "disconnect" );
  self endon( "end customization");
  self notify( "stop preview rotation" );
  self endon( "stop preview rotation" );

  while(isDefined(self.previewModel)) {
    self.previewModel rotateYaw(360, 6);
    wait 6;
  }
}

getweaponName(what)
{
	what=level.iteminfo[what]["name"];
	return what;
}

getmodelName(what)
{
  what=level.characterinfo[what]["name"];

	return what;
}

navigate(table, direction)
{
  isSpectator = false;
  if(self.pers["team"] == "spectator") {
    isSpectator = true;
  }

  persVar = "";
  if(table == "weapons") {
    persVar = "customize_weapon";
  } else if(table == "characters") {
    persVar = "customize_character";
  }

  if(direction == "previous") {
    self.pers[persVar]--;
    if(self.pers[persVar] < 0) {
      self.pers[persVar] = level.itemInfo.size-1;
    }
  }
  else if(direction == "next") {
    self.pers[persVar]++;
    if(self.pers[persVar] >= level.itemInfo.size) {
      self.pers[persVar] = 0;
    }
  }

  switch(table) {
    case "weapons":
      self setClientDvar("drui_weapon", self.pers[persVar]);
      if(isSpectator) self.previewModel setModel(level.itemInfo[self.pers[persVar]]["model"]);
      else {
        self takeAllWeapons();
        item = level.itemInfo[self.pers[persVar]]["item"];
        self giveWeapon(item);
        self switchToWeapon(item);
      }
      break;
    case "characters":
      self setClientDvar("drui_character", self.pers[persVar]);
      if(isSpectator) self.previewModel setModel(level.characterInfo[self.pers[persVar]]["model"]);
      else {
        self setModel(level.characterInfo[self.pers[persVar]]["model"]);
      }
      break;
  }
}

select(table, option)
{
  self closeMenu();
  self closeInGameMenu();
  if(table == "weapons") {
    if((self braxi\_rank::isItemUnlocked(option))) {
      self iprintlnbold("Your weapon will change after you respawn.");
      self setStat(981, option);
    } else {
      self iprintlnbold("^1You need to unlock this weapon first.");
    }
  } else if(table == "characters") {
    if((self braxi\_rank::ischaracterUnlocked(option))) {
      self iprintlnbold("Your character will change after you respawn.");
      self setClientDvar("cg_thirdPerson", 0);
      self setStat(980, option);
    } else {
      self iprintlnbold("^1You need to unlock this character first.");
    }
  }
}