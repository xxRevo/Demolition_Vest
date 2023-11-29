#define _ARMA_

class CfgPatches
{
 class RevoPDA
 {
  units[] = {"SuicideVest_Black"};
	weapons[] = {};
	requiredVersion = 0.1;
	requiredAddons[] = {"DZ_Data"};
 }
};
class CfgMods
{
 class RevoPDA
 {
  	dir = "RevoPDA";
	picture = "";
	action = "";
	hideName = 1;
	hidePicture = 1;
	name = "RevoPDA";
	credits = "Revo";
	author = "Revo";
	authorID = "0";
	version = "9.0";
	extra = 0;
	type = "mod";
	inputs = "";

  
  class defs
  {
   class worldScriptModule
   {
    value = "";
    files[] = {"RevoPDA/scripts/4_World"};
   }
  }
 }
}
class CfgVehicles {
  class Clothing;
  class SuicideVest_ColorBase: Clothing
	{
		displayName="Suicide Vest";
		descriptionShort="Made by Revo";
		model="\DZ\characters\vests\pressVest_g.p3d";
		attachments[]=
		{
			"TriggerRemoteDetonator_Receiver",
			"TriggerAlarmClock",
			"TriggerKitchenTimer",
			"VestGrenadeA"
		};
		inventorySlot[]=
		{
			"Vest"
		};
		itemInfo[]=
		{
			"Clothing",
			"Vest"
		};
		weight=2000;
		itemSize[]={2,2};
		itemsCargoSize[]={};
		quickBarBonus=1;
		varWetMax=0.49000001;
		heatIsolation=0.69999999;
		repairableWithKits[]={3,8};
		repairCosts[]={25,25};
		visibilityModifier=0.94999999;
		hiddenSelections[]=
		{
			"camoGround",
			"camoMale",
			"camoFemale"
		};
		class ClothingTypes
		{
			male="\DZ\characters\vests\pressVest_m.p3d";
			female="\DZ\characters\vests\pressVest_f.p3d";
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=170;
					transferToAttachmentsCoef=0.5;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\characters\vests\Data\PressVest.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\characters\vests\Data\PressVest.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\characters\vests\Data\PressVest_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\characters\vests\Data\PressVest_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\characters\vests\Data\PressVest_destruct.rvmat"
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0.5;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0.75;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0.75;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0.55000001;
					};
				};
				class Infected
				{
					class Health
					{
						damage=0.75;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0.55000001;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0.5;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0.5;
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="Shirt_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="Shirt_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class SuicideVest_Black: SuicideVest_ColorBase
	{
		scope = 2;
		visibilityModifier = 0.9;
		hiddenSelectionsTextures[]=
		{
			"\dz\characters\vests\data\PressVest_Blue_co.paa",
			"\dz\characters\vests\data\PressVest_Blue_co.paa",
			"\dz\characters\vests\data\PressVest_Blue_co.paa"
		};
	};
};
