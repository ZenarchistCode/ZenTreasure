class CfgPatches
{
	class ZenTreasureBase
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class ZenTreasureBase
	{
		dir = "ZenTreasureBase";
		name = "Zen's Treasure";
		author = "Zenarchist";
		credits = "";
		version = "1.0";
		type = "mod";
		dependencies[] = 
		{ 
			"Game", 
			"World", 
			"Mission" 
		};
		class defs
		{
			class engineScriptModule
			{
				files[]=
				{
					"ZenTreasureBase/scripts/1_Core",
					"ZenTreasureBase/scripts/Common"
				};
			};
			class gameLibScriptModule
			{
				files[]=
				{
					"ZenTreasureBase/scripts/2_GameLib",
					"ZenTreasureBase/scripts/Common"
				};
			};
			class gameScriptModule
			{
				files[] = 
				{ 
					"ZenTreasureBase/scripts/3_Game",
					"ZenTreasureBase/scripts/Common"
				};
			};
			class worldScriptModule
			{
				files[] = 
				{ 
					"ZenTreasureBase/scripts/4_World",
					"ZenTreasureBase/scripts/Common"
				};
			};
			class missionScriptModule
			{
				files[] = 
				{ 
					"ZenTreasureBase/scripts/5_mission",
					"ZenTreasureBase/scripts/common"
				};
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class Box_Base;
	class UndergroundStash;
	class WoodenCrate;
	class SeaChest;
	class Shovel;

	//! TREASURE 
	// Turns into a random ammo box
	class ZenRandomAmmoBox : Box_Base
	{
		scope = 2;
		displayName = "$STR_CfgVehicles_AmmoBox_556x45_20Rnd0";
		descriptionShort = "$STR_CfgVehicles_AmmoBox_556x45_20Rnd1";
		model = "\dz\weapons\ammunition\556_20RoundBox.p3d";
		debug_ItemCategory = 5;
		rotationFlags = 17;
		weight = 85;
	};

	class ZenTreasure_UndergroundStash : UndergroundStash {};

	class ZenTreasure_WoodenCrate : WoodenCrate
	{
		scope = 2;
		descriptionShort = "$STR_CfgVehicles_ZenDamagedBox";
		inventorySlot[] = {};
	};
	class ZenTreasure_SeaChest : SeaChest
	{
		scope = 2;
		descriptionShort = "$STR_CfgVehicles_ZenDamagedBox";
	};

	class ZenTreasure_DebugShovel : Shovel
	{
		scope = 2;
		displayName = "TREASURE DEBUG SHOVEL";
		descriptionShort = "NOT FOR ORDINARY HUMANS - WILL DIG UP STASHES VERY FAST!";
	};

	class ZenTreasure_PhotoBase : Inventory_Base
	{
		scope = 0;
		displayName = "$STR_CfgVehicles_ZenPhoto0";
		descriptionShort = "$STR_CfgVehicles_ZenPhoto1";
		model = "ZenTreasureBase\data\models\treasure\photo.p3d";
		hiddenSelections[] = { "front" };
		weight = 1;
		itemSize[] = { 1,1 };
		isMeleeWeapon = 1;
		absorbency = 1;
		rotationFlags = 16; // 1 = rotate front-up, 16 = rotate front-down
		varWetMax = 1;
		treasure_stash_x = -1.0;
		treasure_stash_z = -1.0;
		mapName = "missing";
		inventorySlot[] += // ZenModPack Journal slots
		{
			"ZenJournal_Paper1",
			"ZenJournal_Paper2",
			"ZenJournal_Paper3",
			"ZenJournal_Paper4",
			"ZenJournal_Paper5"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 15;
					healthLevels[] =
					{

						{
							1,

							{
								"ZenTreasureBase\data\textures\treasure\photo_material.rvmat"
							}
						},

						{
							0.69999999,

							{
								"ZenTreasureBase\data\textures\treasure\photo_material.rvmat"
							}
						},

						{
							0.5,

							{
								"ZenTreasureBase\data\textures\treasure\photo_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"ZenTreasureBase\data\textures\treasure\photo_damage.rvmat"
							}
						},

						{
							0,

							{
								"ZenTreasureBase\data\textures\treasure\photo_destruct.rvmat"
							}
						}
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
					soundSet = "pickUpPaper_SoundSet";
					id = 797;
				};
			};
		};
		soundImpactType = "cloth";
	};

	// This turns into a random photograph upon spawn. The spawn list is determined by photo *.cpp entries.
	// Name any child photos in treasure addons 'ZenTreasure_PhotoXX', where XX is the photo number, in order, from 01-99+ (eg. ZenTreasure_Photo69)
	class ZenTreasure_RandomPhoto : ZenTreasure_PhotoBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = { "ZenTreasureBase\data\textures\treasure\photo_random.paa" };
	};
};