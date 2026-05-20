class ZenTreasure_StashTrigger extends ManTrigger
{
	private ref ZenTreasureTriggerConfig m_TreasureConfig;

	ZenTreasureTriggerConfig GetConfig()
	{
		return m_TreasureConfig;
	}

	void SetConfig(ZenTreasureTriggerConfig p_config)
	{
		m_TreasureConfig = p_config;
	}

	override void OnEnter(Object obj)
	{
		if (!g_Game.IsDedicatedServer())
		{
			return;
		}

		PlayerBase player = PlayerBase.Cast(obj);
		if (!player)
		{
			return;
		}

		ZenOnEnter(player);
	}

	void ZenOnEnter(PlayerBase player)
	{
		if (!m_TreasureConfig)
		{
			Error("[ZenTreasure] Player entered trigger but m_TreasureConfig is null.");
			return;
		}

		ZMPrint("[ZenTreasure] Player " + player.GetCachedID() + " entered trigger.");

		int stashType = -1;

		for (int i = m_TreasureConfig.TreasureHunters.Count() - 1; i >= 0; i--)
		{
			ZenTreasureHunter hunter = m_TreasureConfig.TreasureHunters.Get(i);
			if (hunter && hunter.ZenPlayerID == player.GetCachedID())
			{
				stashType = hunter.ZenStashID;
				m_TreasureConfig.TreasureHunters.Remove(i);
				GetZenTreasureDB().Save();
				break;
			}
		}

		if (stashType == -1)
		{
			return;
		}

		SpawnTreasureLoot(player, stashType);
	}

	void SpawnTreasureLoot(notnull PlayerBase player, int stashType)
	{
		int i;
		int j;

		ZenTreasureStashType treasureConfig = GetZenTreasureConfig().TreasureTypes.Get(stashType);
		if (!treasureConfig)
		{
			Error("[ZenTreasure] Could not spawn treasure loot - config not found for stashType=" + stashType);
			return;
		}

		PluginZenTreasureTriggerManager stashPlugin = PluginZenTreasureTriggerManager.Cast(GetPlugin(PluginZenTreasureTriggerManager));
		if (!stashPlugin)
		{
			Error("[ZenTreasure] Failed to get PluginZenTreasureTriggerManager.");
			return;
		}

		array<Object> objectsNearTreasure = new array<Object>;
		g_Game.GetObjectsAtPosition3D(m_TreasureConfig.Position, 1, objectsNearTreasure, NULL);

		for (i = 0; i < objectsNearTreasure.Count(); i++)
		{
			Object obj = objectsNearTreasure.Get(i);
			if (obj && obj.IsKindOf("ZenTreasure_UndergroundStash"))
			{
				g_Game.ObjectDelete(obj);
			}
		}

		vector containerSpawnPos = m_TreasureConfig.Position;
		EntityAI container = EntityAI.Cast(g_Game.CreateObjectEx(treasureConfig.ContainerType, containerSpawnPos, ECE_SETUP | ECE_CREATEPHYSICS));

		if (!container)
		{
			Error("[ZenTreasure] Failed to spawn treasure loot container - " + treasureConfig.ContainerType + " @ " + m_TreasureConfig.Position);
			return;
		}

		container.Update();
		container.SetLifetimeMax(GetZenTreasureConfig().TreasureStashPersistenceSecs);
		container.SetLifetime(GetZenTreasureConfig().TreasureStashPersistenceSecs);
		container.IncreaseLifetimeUp();

		array<ref ZenTreasureLootSpawn> tempLootArray = new array<ref ZenTreasureLootSpawn>;

		if (stashType == 0 || stashType == 1)
		{
			foreach (ZenTreasureStashType tempConfig : GetZenTreasureConfig().TreasureTypes)
			{
				for (i = 0; i < tempConfig.Loot.Count(); i++)
				{
					tempLootArray.Insert(tempConfig.Loot.Get(i));
				}
			}
		}
		else
		{
			foreach (ZenTreasureLootSpawn zloot : treasureConfig.Loot)
			{
				tempLootArray.Insert(zloot);
			}
		}

		ZMPrint("[ZenTreasure] tempLootArray count=" + tempLootArray.Count() + " for stashType=" + stashType + " config=" + treasureConfig.ConfigName);

		int lootCount = 0;
		int failSpawnCount = 0;

		for (i = 0; i < tempLootArray.Count(); i++)
		{
			ZenTreasureLootSpawn lootSpawn = tempLootArray.Get(i);

			if (!lootSpawn)
			{
				continue;
			}

			if (lootSpawn.ClassName.Contains("Predef_"))
			{
				foreach (ZenTreasurePredefinedType predefLoot : GetZenTreasureConfig().PredefinedTypes)
				{
					if (predefLoot && predefLoot.ConfigName == lootSpawn.ClassName)
					{
						lootSpawn = predefLoot.Item;
						break;
					}
				}
			}

			if (!lootSpawn)
			{
				continue;
			}

			EntityAI itemSpawned = ZenSpawnLootItem(container, lootSpawn);
			if (itemSpawned)
			{
				lootCount++;

				for (j = 0; j < lootSpawn.Attachments.Count(); j++)
				{
					EntityAI attachmentSpawned = ZenSpawnLootItemAttachment(itemSpawned, lootSpawn.Attachments.Get(j));

					if (!attachmentSpawned)
					{
						attachmentSpawned = ZenSpawnLootItemAttachment(container, lootSpawn.Attachments.Get(j));
					}

					if (attachmentSpawned)
					{
						lootCount++;
					}
				}
			}
			else 
			{
				failSpawnCount++;
			}
		}

		float heightOffset = 0.24;
		UndergroundStash stash = UndergroundStash.Cast(g_Game.CreateObject("ZenTreasure_UndergroundStash", m_TreasureConfig.Position, ECE_PLACE_ON_SURFACE));

		if (!stash)
		{
			Error("[ZenTreasure] Failed to spawn buried UndergroundStash @ " + m_TreasureConfig.Position);
			g_Game.ObjectDelete(container);
			return;
		}

		stash.PlaceOnGround();

		vector stashPos = stash.GetPosition();
		stashPos[1] = g_Game.SurfaceY(stashPos[0], stashPos[2]) + heightOffset;
		stash.SetPosition(stashPos);

		vector transform[4];
		stash.GetTransform(transform);

		vector groundPosition;
		vector groundDirection;
		int component;

		DayZPhysics.RaycastRV(transform[3], transform[3] + transform[1] * -100, groundPosition, groundDirection, component, null, null, null, false, true);

		vector surfaceNormal = g_Game.SurfaceGetNormal(groundPosition[0], groundPosition[2]);
		vector localOri = stash.GetDirection();

		transform[0] = surfaceNormal * localOri;
		transform[1] = surfaceNormal;
		transform[2] = surfaceNormal * (localOri * vector.Up);

		stash.SetTransform(transform);
		stash.Update();

		stash.SetLifetimeMax(GetZenTreasureConfig().TreasureStashPersistenceSecs);
		stash.SetLifetime(GetZenTreasureConfig().TreasureStashPersistenceSecs);

		ZenTreasure_StashTransferJob transferJob = new ZenTreasure_StashTransferJob(player, container, stash);
		stashPlugin.AddTransferJob(transferJob);

		stashPlugin.RemoveTrigger(this);

		ZMPrint("[ZenTreasure] " + player.GetCachedID() + " spawned treasure stash @ " + m_TreasureConfig.Position + " with config " + treasureConfig.ConfigName + " lootCount=" + lootCount + " skippedItemCount=" + failSpawnCount);
	}

	EntityAI ZenSpawnLootItem(EntityAI lootEAI, ZenTreasureLootSpawn lootSpawn)
	{
		if (!lootEAI || !lootSpawn || !lootEAI.GetInventory())
		{
			return NULL;
		}

		if (Math.RandomFloat01() > lootSpawn.SpawnChance)
		{
			return NULL;
		}

		string itemType = lootSpawn.ClassName;

		if (itemType.Contains("|"))
		{
			TStringArray itemList = new TStringArray;
			itemType.Split("|", itemList);
			itemType = itemList.GetRandomElement();
		}

		EntityAI item = lootEAI.GetInventory().CreateInInventory(itemType);

		if (!item)
		{
			item = lootEAI.GetInventory().CreateAttachment(itemType);
		}

		if (!item)
		{
			//ZMPrint("[ZenTreasure] Failed to spawn loot item in container: " + itemType + " parent=" + lootEAI + " parentType=" + lootEAI.GetType());
			return NULL;
		}

		item.EEOnCECreate();

		int quantity = Math.RandomIntInclusive(lootSpawn.MinQuantity, lootSpawn.MaxQuantity);
		float health = Math.RandomFloatInclusive(lootSpawn.MinHealth / 100, 1.0);

		Ammunition_Base ammo = Ammunition_Base.Cast(item);
		if (ammo)
		{
			ammo.ServerSetAmmoCount(quantity);
			ammo.SetHealth(item.GetMaxHealth() * health);
			return item;
		}

		ItemBase itemBase = ItemBase.Cast(item);
		if (!itemBase)
		{
			return item;
		}

		itemBase.SetHealth(itemBase.GetMaxHealth() * health);

		if (itemBase.ConfigIsExisting("quantityBar") && itemBase.ConfigGetFloat("quantityBar") != 1)
		{
			ZenFunctions.SetQuantity(itemBase, quantity);
			return item;
		}

		if (itemBase.GetQuantity() == quantity)
		{
			return item;
		}

		for (int extraIndex = 0; extraIndex < lootSpawn.MaxQuantity - 1; extraIndex++)
		{
			if (!lootEAI || !lootEAI.GetInventory())
			{
				continue;
			}

			if (Math.RandomFloat01() > lootSpawn.SpawnChance)
			{
				continue;
			}

			EntityAI extraItem = lootEAI.GetInventory().CreateInInventory(itemType);
			if (!extraItem)
			{
				extraItem = lootEAI.GetInventory().CreateAttachment(itemType);
			}

			if (!extraItem)
			{
				continue;
			}

			if (extraItem.IsKindOf("ZenSwissKnife") || extraItem.IsKindOf("ZenTreasure_PhotoBase"))
			{
				continue;
			}

			float extraHealth = Math.RandomFloatInclusive(lootSpawn.MinHealth / 100, 1.0);
			ItemBase extraItemBase = ItemBase.Cast(extraItem);

			if (extraItemBase)
			{
				extraItemBase.SetHealth(extraItemBase.GetMaxHealth() * extraHealth);
			}
			else
			{
				extraItem.SetHealth(extraItem.GetMaxHealth() * extraHealth);
			}
		}

		return item;
	}

	EntityAI ZenSpawnLootItemAttachment(EntityAI lootEAI, string itemType)
	{
		if (!lootEAI || !lootEAI.GetInventory())
		{
			return NULL;
		}

		float chance = 1.0;
		float minHealth = 0.1;

		if (itemType.Contains("|"))
		{
			TStringArray parameters = new TStringArray;
			itemType.Split("|", parameters);

			foreach (string parameter : parameters)
			{
				parameter.ToLower();

				if (parameter.Contains("c="))
				{
					parameter.Replace("c=", "");
					chance = parameter.ToFloat();
				}
				else if (parameter.Contains("h="))
				{
					parameter.Replace("h=", "");
					minHealth = parameter.ToFloat();
				}
			}

			itemType = parameters.Get(0);
		}

		if (Math.RandomFloat01() > chance)
		{
			return NULL;
		}

		EntityAI item = lootEAI.GetInventory().CreateInInventory(itemType);

		if (!item)
		{
			item = lootEAI.GetInventory().CreateAttachment(itemType);
		}

		if (!item)
		{
			//ZMPrint("[ZenTreasure] Failed to spawn attachment item: " + itemType + " parent=" + lootEAI + " parentType=" + lootEAI.GetType());
			return NULL;
		}

		float health = item.GetMaxHealth() * Math.RandomFloatInclusive(minHealth, 1.0);
		item.SetHealth(health);

		return item;
	}
}