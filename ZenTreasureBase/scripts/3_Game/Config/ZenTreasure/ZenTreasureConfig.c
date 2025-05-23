class ZenTreasureConfig
{
	// Static constant config version (is NOT saved to json)
	static const string CONFIG_VERSION = "1";

	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\";
	private const static string zenConfigName = "ZenTreasureConfig.json";

	// Main config data
	string ConfigVersion = "";
	bool DebugZenMapCompatibility = false;
	bool DebugTeleportToPhoto = false;
	int DebugAlwaysSpawnStashID = -1;
	int TreasurePersistenceSecs = 3600; // 1 hour, after player enters trigger & spawns stash.
	bool IsWinterMap = false;
	float SpawnPhotosOnZombiesChance = 0.01;
	int PhotoSpawnStartNumber = 0;
	int PhotoSpawnStopNumber = 0;
	static ref array<string>					TreasureDescriptions	= new array<string>;
	ref array<ref ZenTreasurePredefinedType>	PredefinedTypes			= new array<ref ZenTreasurePredefinedType>;
	ref array<ref ZenTreasureStashType>			TreasureTypes			= new array<ref ZenTreasureStashType>;

	void Load()
	{
		// Load JSON on server only
		if (!GetGame().IsDedicatedServer())
			return;

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<ZenTreasureConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			// If version mismatch, backup old version of json before replacing it
			if (ConfigVersion != CONFIG_VERSION)
			{
				JsonFileLoader<ZenTreasureConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Config exists and version matches, stop here.
				Save();
				ShuffleLoot();
				return;
			}
		}

		ConfigVersion = CONFIG_VERSION;
		SetupDefaultConfig();
		Save();
	}

	void SetupDefaultConfig()
	{
		// Prepare predefined loot types 
		// SVD
		ZenTreasureLootSpawn predef_SVD = new ZenTreasureLootSpawn("SVD|SVD_Wooden", 1, 1);
		predef_SVD.Attachments.Insert("Mag_SVD_10Rnd");
		predef_SVD.Attachments.Insert("PSO11Optic|h=0.01|c=0.5");
		predef_SVD.Attachments.Insert("Battery9V");
		predef_SVD.Attachments.Insert("AmmoBox_762x54Tracer_20Rnd|c=0.9");
		predef_SVD.Attachments.Insert("AmmoBox_762x54Tracer_20Rnd|c=0.9");
		PredefinedTypes.Insert(new ZenTreasurePredefinedType("Predef_SVD", predef_SVD));
		// DMR
		ZenTreasureLootSpawn predef_DMR = new ZenTreasureLootSpawn("M14", 1, 1);
		predef_DMR.Attachments.Insert("Mag_M14_20Rnd");
		predef_DMR.Attachments.Insert("MK4Optic_Green|h=0.01|c=0.5");
		predef_DMR.Attachments.Insert("AmmoBox_308WinTracer_20Rnd|c=0.9");
		predef_DMR.Attachments.Insert("AmmoBox_308WinTracer_20Rnd|c=0.9");
		PredefinedTypes.Insert(new ZenTreasurePredefinedType("Predef_DMR", predef_DMR));
		// AKM
		ZenTreasureLootSpawn predef_AKM = new ZenTreasureLootSpawn("AKM", 1, 1);
		predef_AKM.Attachments.Insert("Mag_AKM_Drum75Rnd");
		predef_AKM.Attachments.Insert("AK_WoodBttstck_Black");
		predef_AKM.Attachments.Insert("AK_WoodHndgrd_Black");
		predef_AKM.Attachments.Insert("PSO11Optic|h=0.01|c=0.5");
		predef_AKM.Attachments.Insert("Battery9V");
		predef_AKM.Attachments.Insert("AmmoBox_762x39Tracer_20Rnd|c=0.9");
		predef_AKM.Attachments.Insert("AmmoBox_762x39Tracer_20Rnd|c=0.9");
		PredefinedTypes.Insert(new ZenTreasurePredefinedType("Predef_AKM", predef_AKM));
		// Mosin
		ZenTreasureLootSpawn predef_Mosin = new ZenTreasureLootSpawn("Mosin9130|Mosin9130_Camo|Mosin9130_Black|Mosin9130_Green", 1, 1);
		predef_Mosin.Attachments.Insert("PUScopeOptic");
		predef_Mosin.Attachments.Insert("AmmoBox_762x54Tracer_20Rnd");
		predef_Mosin.Attachments.Insert("AmmoBox_762x54Tracer_20Rnd|c=0.9");
		PredefinedTypes.Insert(new ZenTreasurePredefinedType("Predef_Mosin", predef_Mosin));
		// Winchester
		ZenTreasureLootSpawn predef_Winchester = new ZenTreasureLootSpawn("Winchester70|Winchester70_Black|Winchester70_Green", 1, 1);
		predef_Winchester.Attachments.Insert("HuntingOptic");
		predef_Winchester.Attachments.Insert("AmmoBox_308WinTracer_20Rnd");
		predef_Winchester.Attachments.Insert("AmmoBox_308WinTracer_20Rnd|c=0.9");
		PredefinedTypes.Insert(new ZenTreasurePredefinedType("Predef_Winchester", predef_Winchester));
		// AmmoBox 
		ZenTreasureLootSpawn predef_AmmoBox = new ZenTreasureLootSpawn("AmmoBox", 1, 1);
		for (int i = 0; i < 40; i++)
		{
			predef_AmmoBox.Attachments.Insert("ZenRandomAmmoBox");
		}
		PredefinedTypes.Insert(new ZenTreasurePredefinedType("Predef_AmmoBox", predef_AmmoBox));

		// 0 - Generic loot small (wooden crate) - filled with all possible loot from other configs
		TreasureTypes.Insert(new ZenTreasureStashType("Generic_Small", "valuable", "ZenTreasure_WoodenCrate"));

		// 1 - Generic loot large (sea chest) - filled with all possible loot from other configs
		TreasureTypes.Insert(new ZenTreasureStashType("Generic_Large", "valuable", "ZenTreasure_SeaChest"));

		// 2 - Hunting loot (wooden crate)
		ZenTreasureStashType huntingLootSmall = new ZenTreasureStashType("HuntingLoot_Small", "hunting", "ZenTreasure_WoodenCrate");
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Predef_Winchester", 1, 1, 1.0));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Predef_Mosin", 1, 1, 1.0));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_762x54", 10, 20, 0.9));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_762x54", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_762x54", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_762x54", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_762x54", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_762x54", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_308Win", 10, 20, 0.9));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_308Win", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_308Win", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_308Win", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_308Win", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Ammo_308Win", 10, 20, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("HuntingOptic", 1, 1, 0.6));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.9));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.5));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Whetstone", 1, 1, 0.9));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("WeaponCleaningKit", 1, 1, 0.9));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("ZenTreasure_RandomPhoto", 1, 1, 0.1));
		#ifdef ZENMODPACK
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("ZenSwissKnife", 1, 1, 0.9));
		huntingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("ZenFlint", 1, 1, 0.6));
		#endif
		TreasureTypes.Insert(huntingLootSmall);

		// 3 - Basebuilding loot (wooden crate)
		ZenTreasureStashType basebuildingLootSmall = new ZenTreasureStashType("Basebuilding_Small", "basebuilding", "ZenTreasure_WoodenCrate");
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.5));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.9));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.9));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("HandSaw", 1, 1, 0.9));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Hatchet", 1, 1, 0.9));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Pliers", 1, 1, 0.9));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Whetstone", 1, 1, 0.9));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Whetstone", 1, 1, 0.9));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Whetstone", 1, 1, 0.9));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Whetstone", 1, 1, 0.9));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.25));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.25));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.25));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("MetalWire", 1, 1, 0.2));
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("ZenTreasure_RandomPhoto", 1, 1, 0.1));
		#ifdef ZENCOMBOLOCKS
		basebuildingLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Zen_CombinationLock5", 1, 1, 0.1));
		#endif
		TreasureTypes.Insert(basebuildingLootSmall);

		// 4 - Military loot SVD (wooden crate)
		ZenTreasureStashType militaryLootSmall = new ZenTreasureStashType("Military_Small", "military", "ZenTreasure_WoodenCrate");
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Predef_SVD", 1, 1, 1.0));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Predef_DMR", 1, 1, 1.0));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Predef_AKM", 1, 1, 1.0));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("AK_Suppressor", 1, 1, 0.9));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Mag_SVD_10Rnd", 1, 1, 0.9));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("AmmoBox_762x54Tracer_20Rnd", 1, 2, 0.9));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("AmmoBox_308WinTracer_20Rnd", 1, 2, 0.9));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("AmmoBox_762x39_20Rnd", 1, 1, 0.9));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 3, 0.9));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("MetalWire", 1, 1, 0.9));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("WeaponCleaningKit", 1, 1, 0.9));
		militaryLootSmall.Loot.Insert(new ZenTreasureLootSpawn("ZenTreasure_RandomPhoto", 1, 1, 0.1));
		TreasureTypes.Insert(militaryLootSmall);

		// 5 - Military loot high grade (sea chest)
		ZenTreasureStashType militaryLootLarge = new ZenTreasureStashType("Military_Large", "high-grade military", "ZenTreasure_SeaChest");
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("Predef_SVD", 1, 1, 1.0));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("Predef_DMR", 1, 1, 1.0));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("AK_Suppressor", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("M4_Suppressor", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("Mag_SVD_10Rnd", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("Mag_M14_10Rnd", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("Plastic_Explosive", 1, 1, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("RemoteDetonator", 1, 1, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("AmmoBox_762x54Tracer_20Rnd", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("AmmoBox_762x54Tracer_20Rnd", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("ZenRandomAmmoBox", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("MetalWire", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("WeaponCleaningKit", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("RGD5Grenade", 1, 5, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("M67Grenade", 1, 5, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("LandMineTrap", 1, 1, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("Predef_AmmoBox", 1, 1, 0.9));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("ZenTreasure_RandomPhoto", 1, 1, 0.1));
		#ifdef ZENMODPACK
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("Zen_ArtillerySmokeGrenade", 1, 1, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("Zen_ArtillerySmokeGrenadeChem", 1, 1, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("Zen_ConcussionGrenade", 1, 1, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("ZenRaybans_Black", 1, 1, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("ZenSwissKnife", 1, 1, 0.5));
		militaryLootLarge.Loot.Insert(new ZenTreasureLootSpawn("ZenZippoLighter_Zenarchist", 1, 1, 0.5));
		#endif
		TreasureTypes.Insert(militaryLootLarge);

		// 6 - Medical
		ZenTreasureStashType medicalLootSmall = new ZenTreasureStashType("Medical_Small", "medical", "ZenTreasure_SeaChest");
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Predef_NBC", 1, 1, 1.0));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("VitaminBottle", 1, 1, 0.6));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("DisinfectantAlcohol", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("IodineTincture", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("ChelatingTablets", 1, 1, 0.6));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("PurificationTablets", 1, 1, 0.6));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("CharcoalTablets", 1, 1, 0.6));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("PainkillerTablets", 1, 1, 0.6));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("BandageDressing", 1, 3, 0.3));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("SalineBagIV", 1, 1, 0.6));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("AntiChemInjector", 1, 2, 0.9));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Morphine", 1, 2, 0.9));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Epinephrine", 1, 3, 0.9));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NailBox", 1, 1, 0.6));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NBCGlovesGray", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NBCHoodGray", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NBCPantsGray", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NBCBootsGray", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("GasMask", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NBCBootsWhite", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NBCPantsWhite", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NBCHoodWhite", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("NBCGlovesWhite", 1, 1, 0.5));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("GasMask_Filter", 1, 1, 0.6));
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("ZenTreasure_RandomPhoto", 1, 1, 0.1));
		#ifdef ZENMODPACK
		medicalLootSmall.Loot.Insert(new ZenTreasureLootSpawn("Zen_NBCCase", 1, 1, 0.9));
		#endif
		TreasureTypes.Insert(medicalLootSmall);	
	}

	// Shuffle the loot arrays so loot isn't always spawned in the same config order to get better dispersion/randomness.
	// There's probably a better way but this will do, we just want to keep the stashes interesting that's the only goal here.
	void ShuffleLoot()
	{
		foreach(ZenTreasureStashType spawn : TreasureTypes)
		{
			spawn.Loot.ShuffleArray();
		}
	}

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ZenTreasureConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}
}

// Define a loot spawn item
class ZenTreasureLootSpawn
{
	string ClassName;
	int MinQuantity;
	int MaxQuantity;
	int MinHealth = 10;
	float SpawnChance;
	ref array<string> Attachments = new array<string>;

	void ZenTreasureLootSpawn(string p_type, int p_min_quantity, int p_max_quantity, float p_chance = 1.0)
	{
		this.ClassName = p_type;
		this.MinQuantity = p_min_quantity;
		this.MaxQuantity = p_max_quantity;
		this.SpawnChance = p_chance;
	}
};

// Define predefined type
class ZenTreasurePredefinedType
{
	string ConfigName;
	ref ZenTreasureLootSpawn Item;

	void ZenTreasurePredefinedType(string p_configName, ZenTreasureLootSpawn p_item)
	{
		ConfigName = p_configName;
		Item = p_item;
	}
};

// Define default loot config
class ZenTreasureStashType
{
	string ConfigName;
	string Description;
	string ContainerType;
	ref array<ref ZenTreasureLootSpawn> Loot = new array<ref ZenTreasureLootSpawn>;

	void ZenTreasureStashType(string p_configName, string p_description, string p_containerName)
	{
		ConfigName = p_configName;
		Description = p_description;
		ContainerType = p_containerName;
	}
};

ref ZenTreasureConfig m_ZenTreasureConfig;

static ZenTreasureConfig GetZenTreasureConfig()
{
	if (!m_ZenTreasureConfig)
	{
		Print("[ZenTreasureConfig] Init");
		m_ZenTreasureConfig = new ZenTreasureConfig;
		m_ZenTreasureConfig.Load();
	}

	return m_ZenTreasureConfig;
}
