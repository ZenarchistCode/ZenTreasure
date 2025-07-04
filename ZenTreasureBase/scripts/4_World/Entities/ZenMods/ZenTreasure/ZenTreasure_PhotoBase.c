class ZenTreasure_PhotoBase extends ItemBase
{
	protected int m_ZenStashType = -1;
	protected vector m_StashPosition;

	// Called when Central Economy engine spawns this item into the world as loot
	override void EEOnCECreate()
	{
		super.EEOnCECreate();

		// This makes it so you don't gotta set cfgspawnabletypes.xml to spawn photos Pristine.
		// The photos are impossible to see once damaged, so let's always spawn them Pristine.
		// If they get damaged by zombies/combat/etc later.. well, tough luck survivor.
		SetHealth(GetMaxHealth());
	}

	void ZenTreasure_PhotoBase()
	{
		RegisterNetSyncVariableInt("m_ZenStashType");

		// Get photo number for texture purposes (remove 'ZenTreasure_Photo' to get number text only)
		string className = GetType();
		string substringNumber = className.Substring(17, className.Length() - 17);
		int photoNumber = substringNumber.ToInt();
		if (photoNumber < 10)
			substringNumber = "0" + photoNumber.ToString();
		else
			substringNumber = photoNumber.ToString();

		// Assign texture
		AsssignPhotoTexture(substringNumber);
	}

	void AsssignPhotoTexture(string photoNumber)
	{
		if (IsWinterPhoto())
		{
			if (GetHiddenSelectionsTextures().Count() > 0)
				SetObjectTexture(0, GetHiddenSelectionsTextures().Get(1));
			else 
				SetObjectTexture(0, "ZenTreasurePhotos/data/photos/photo" + photoNumber + "_winter.paa");
		}
		else 
		{
			if (GetHiddenSelectionsTextures().Count() > 0)
				SetObjectTexture(0, GetHiddenSelectionsTextures().Get(0));
			else 
				SetObjectTexture(0, "ZenTreasurePhotos/data/photos/photo" + photoNumber + ".paa");
		}
	}

	void AssignRandomStashType()
	{
		if (m_ZenStashType != -1)
			return;

		// Assign a random loot type to this photo
		if (GetZenTreasureConfig().DebugAlwaysSpawnStashID == -1)
			m_ZenStashType = Math.RandomIntInclusive(0, GetZenTreasureConfig().TreasureTypes.Count() - 1);
		else 
			m_ZenStashType = GetZenTreasureConfig().DebugAlwaysSpawnStashID;

		SetSynchDirty();
	}

	override void EEInit()
	{
		super.EEInit();

		m_StashPosition = GetBuryPosition();
	}

	static bool IsWinterPhoto()
	{
		return GetZenTreasureConfig().IsWinterMap;
	}

	override bool DescriptionOverride(out string output)
	{
		string cfgPath = "CfgVehicles ZenTreasure_PhotoBase";
		string treasureTypeText = "";

		if (SpawnedStash())
		{
			cfgPath = "CfgVehicles " + GetType();
			treasureTypeText = ZenTreasureConfig.TreasureDescriptions.Get(m_ZenStashType);
		}

		GetGame().ConfigGetText(cfgPath + " descriptionShort", output);
		output.Replace("TREASURETYPE", treasureTypeText);

		return true;
	}

	// Get bury location from *.cpp file config
	vector GetBuryPosition()
	{
		string cfgPath = "CfgVehicles " + GetType();

		float x = GetGame().ConfigGetFloat(cfgPath + " treasure_stash_x");
		float y = GetGame().ConfigGetFloat(cfgPath + " treasure_stash_z");
		float z = GetGame().SurfaceY(x, y);

		vector buryPos = vector.Zero;
		buryPos[0] = x;
		buryPos[1] = z;
		buryPos[2] = y;

		return buryPos;
	}

	int GetStashType()
	{
		return m_ZenStashType;
	}

	void SetStashType(int type)
	{
		m_ZenStashType = type;
		SetSynchDirty();
	}

	bool SpawnedStash()
	{
		return m_ZenStashType != -1;
	}

	void SpawnStash(PlayerBase player)
	{
		AssignRandomStashType();

		// Spawn stash!
		SpawnTreasureTrigger(player);

		// Debug teleport?
		if (GetZenTreasureConfig().DebugTeleportToPhoto)
		{
			DeveloperTeleport.SetPlayerPosition(player, m_StashPosition);
		}
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionZenReadPhoto);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_ZenStashType))
			return false;

		return true;
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		ctx.Write(m_ZenStashType);
	}

	void PhotoDebugPrint(string msg)
	{
		msg = "[ZenTreasure Debug] " + msg;
		Print(msg);
	}

	void SpawnTreasureTrigger(PlayerBase player)
	{
		if (!player)
		{
			Error("[ZenTreasure] Treasure stashed was spawned with no valid Player responsible for it!");
			return;
		}

		ZenTreasureStashType treasureConfig = GetZenTreasureConfig().TreasureTypes.Get(m_ZenStashType);
		if (!treasureConfig)
		{
			Error("[ZenTreasure] Could not spawn treasure loot trigger - config not found for m_ZenStashType=" + m_ZenStashType);
			return;
		}

		GetZenTreasure_Triggers().SpawnTrigger(GetZenTreasureConfig_SpawnTriggers().AddTreasureTrigger(m_StashPosition, player.GetCachedID(), m_ZenStashType), player);
		Print("[ZenTreasure] " + player.GetCachedID() + " spawned treasure stash TRIGGER @ " + m_StashPosition + " with config " + treasureConfig.ConfigName);
	}

	#ifdef MAPLINK
	override void OnUApiSave(UApiEntityStore data)
	{
		super.OnUApiSave(data);

		data.Write("m_ZenStashType", GetStashType());
		Print("[ZenTreasure_PhotoBase::MapLink] Saving photo - stash ID: " + GetStashType());
	}
	
	override void OnUApiLoad(UApiEntityStore data)
	{
		super.OnUApiLoad(data);
		
		SetStashType(data.GetInt("m_ZenStashType"));
		Print("[ZenTreasure_PhotoBase::MapLink] Loaded photo - stash ID: " + GetStashType());
	}
	#endif
}