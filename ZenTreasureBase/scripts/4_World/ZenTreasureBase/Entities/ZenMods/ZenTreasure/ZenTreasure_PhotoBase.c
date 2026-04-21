class ZenTreasure_PhotoBase extends ItemBase
{
	protected int m_ZenStashType = -1;
	protected vector m_StashPosition;
	protected string m_StashCreatorID;
	protected int m_StashCreatorID_SyncHash;

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
		RegisterNetSyncVariableInt("m_StashCreatorID_SyncHash");

		SetStashCreatorID("");

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
		if (!g_Game.IsDedicatedServer())
			return;
		
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
		//SetAllowDamage(false); // set to invincible if preferred and repack.
	}

	static bool IsWinterPhoto()
	{
		if (!g_Game.IsDedicatedServer())
			return false;
		
		return GetZenTreasureConfig().UseWinterPhotoTexture;
	}

	override bool DescriptionOverride(out string output)
	{
		if (!g_Game)
			return super.DescriptionOverride(output);

		PlayerBase pb = PlayerBase.Cast(g_Game.GetPlayer());
		if (!pb || !pb.GetIdentity())
			return super.DescriptionOverride(output);

		if (m_StashCreatorID_SyncHash != 0 && pb.GetIdentity().GetPlainId().Hash() != m_StashCreatorID_SyncHash)
		{
			output = "#STR_ZenTreasure_CantRead";
		}
		else
		{
			string cfgPath = "CfgVehicles ZenTreasure_PhotoBase";
			string treasureTypeText = "";

			if (SpawnedStash())
			{
				cfgPath = "CfgVehicles " + GetType();
				treasureTypeText = ZenTreasureConfig.TreasureDescriptions.Get(m_ZenStashType);
			}

			g_Game.ConfigGetText(cfgPath + " descriptionShort", output);
			output.Replace("TREASURETYPE", treasureTypeText);
		}
		
		return true;
	}

	// Get bury location from *.cpp file config OR JSON override if this photo classname has a config.
	vector GetBuryPosition()
	{
		if (!g_Game.IsDedicatedServer())
			return Vector(0, 0, 0);
		
		float x, y, z;
		
		ZenTreasureLocation loc;
		if (GetZenTreasureConfig().TreasureLocationOverrides.Find(GetType(), loc))
		{
			x = loc.StashX;
			z = loc.StashZ;
		}
		else 
		{
			string cfgPath = "CfgVehicles " + GetType();
			x = g_Game.ConfigGetFloat(cfgPath + " treasure_stash_x");
			z = g_Game.ConfigGetFloat(cfgPath + " treasure_stash_z");
		}
		
		y = g_Game.SurfaceY(x, z);

		vector buryPos = vector.Zero;
		buryPos[0] = x;
		buryPos[1] = y;
		buryPos[2] = z;

		return buryPos;
	}

	string GetStashCreatorID()
	{
		return m_StashCreatorID;
	}

	void SetStashCreatorID(string id)
	{
		m_StashCreatorID = id;

		if (g_Game.IsDedicatedServer())
		{
			if (id == "")
			{
				m_StashCreatorID_SyncHash = 0;
			}
			else 
			{
				m_StashCreatorID_SyncHash = m_StashCreatorID.Hash();
			}

			SetSynchDirty();
		}
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

		if (!ctx.Read(m_StashCreatorID))
			return false;

		return true;
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		ctx.Write(m_ZenStashType);
		ctx.Write(m_StashCreatorID);
	}

	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();

		// Force sync
		SetStashCreatorID(m_StashCreatorID);
	}

	void PhotoDebugPrint(string msg)
	{
		msg = "[ZenTreasure Debug] " + msg;
		ZMPrint(msg);
	}

	void SpawnTreasureTrigger(PlayerBase player)
	{
		if (!player || !player.GetIdentity())
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

		if (!m_StashPosition)
		{
			m_StashPosition = GetBuryPosition();
		}

		float x = m_StashPosition[0];
		float y = m_StashPosition[0];
		float z = m_StashPosition[0];

		if (x < 0 || y < 0 || z < 0)
		{
			Error("Tried to spawn a treasure stash with bad XYZ config: " + m_StashPosition);
			return;
		}

		GetZenTreasure_Triggers().SpawnTrigger(GetZenTreasureDB().AddTreasureTrigger(m_StashPosition, player.GetCachedID(), m_ZenStashType), player);
		ZMPrint("[ZenTreasure] " + player.GetCachedID() + " spawned treasure stash TRIGGER @ " + m_StashPosition + " with config " + treasureConfig.ConfigName);
	
		SetStashCreatorID(player.GetIdentity().GetPlainId());
	}

	#ifdef MapLink
	override void OnUApiSave(UApiEntityStore data)
	{
		super.OnUApiSave(data);

		data.Write("m_ZenStashType", GetStashType());
		data.Write("m_StashCreatorID", GetStashCreatorID());
		//Print("[ZenTreasure_PhotoBase::MapLink] Saving photo - stash ID: " + GetStashType());
	}
	
	override void OnUApiLoad(UApiEntityStore data)
	{
		super.OnUApiLoad(data);
		
		SetStashType(data.GetInt("m_ZenStashType"));
		//Print("[ZenTreasure_PhotoBase::MapLink] Loaded photo - stash ID: " + GetStashType());
	}
	#endif
}