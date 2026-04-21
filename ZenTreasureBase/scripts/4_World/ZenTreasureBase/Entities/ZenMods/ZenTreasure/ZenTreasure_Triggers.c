ref ZenTreasure_Triggers m_ZenTreasure_TriggersInstance;

static ZenTreasure_Triggers GetZenTreasure_Triggers()
{
	if (!m_ZenTreasure_TriggersInstance)
	{
		ZMPrint("[ZenTreasure_Triggers] Init");
		m_ZenTreasure_TriggersInstance = new ZenTreasure_Triggers();
	}

	return m_ZenTreasure_TriggersInstance;
}

class ZenTreasure_Triggers
{
	static const float TRIGGER_RADIUS = 50;
	protected ref array<ZenTreasure_StashTrigger> m_Triggers = new array<ZenTreasure_StashTrigger>;
	
	array<ZenTreasure_StashTrigger> GetTriggers()
	{
		return m_Triggers;
	}

	void SpawnStartupTriggers()
	{
		// Loop through config to spawn triggers on server startup
		foreach (ZenTreasureTriggerConfig cfg : GetZenTreasureDB().TreasureTriggers)
		{
			SpawnTrigger(cfg);
		}
	}

	void SpawnTrigger(ZenTreasureTriggerConfig cfg, PlayerBase player = null)
	{
		// Check if one already exists for this cfg first
		for (int i = m_Triggers.Count() - 1; i >= 0; i--)
		{
			ZenTreasure_StashTrigger existingTrigger = m_Triggers.Get(i);
			if (!existingTrigger)
			{
				Error("Strange error: ZenTreasure_StashTrigger does not exist for index: " + i);
				m_Triggers.Remove(i);
				continue;
			}

			if (!existingTrigger.GetConfig().Position)
			{
				Error("Strange error: vector Position does not exist for index: " + i);
				m_Triggers.Remove(i);
				continue;
			}

			if (vector.Distance(existingTrigger.GetConfig().Position, cfg.Position) < 1)
			{
				existingTrigger.SetConfig(cfg);
				
				if (player && vector.Distance(existingTrigger.GetPosition(), player.GetPosition()) <= TRIGGER_RADIUS)
				{
					ZMPrint("[ZenTreasure_Triggers] Player is too close to trigger - forcing manual spawn.");
					existingTrigger.ZenOnEnter(player);
				}
				
				Print("ZenTreasure_Triggers::SpawnTrigger() - Updated trigger @ " + cfg.Position);
				return;
			}
		}

		ZenTreasure_StashTrigger trigger = ZenTreasure_StashTrigger.Cast(g_Game.CreateObject("ZenTreasure_StashTrigger", cfg.Position));
		trigger.SetPosition(cfg.Position); // Ensure no place on surface etc happens

		if (!trigger)
		{
			Error("ZenTreasure_Triggers::SpawnTrigger() - Failed to spawn trigger!");
			return;
		}

		trigger.SetConfig(cfg);
		trigger.SetCollisionSphere(TRIGGER_RADIUS);
		m_Triggers.Insert(trigger);
		ZMPrint("ZenTreasure_Triggers::SpawnTrigger() - Spawned trigger @ " + cfg.Position);

		if (player && vector.Distance(trigger.GetPosition(), player.GetPosition()) <= TRIGGER_RADIUS)
		{
			ZMPrint("[ZenTreasure_Triggers] Player is too close to trigger - forcing manual spawn.");
			trigger.ZenOnEnter(player);
		}
	}

	void RemoveTrigger(ZenTreasure_StashTrigger trigger)
	{
		// Don't delete the trigger if other players are still attached to it
		if (trigger.GetConfig().TreasureHunters.Count() > 0)
			return;

		for (int i = m_Triggers.Count() - 1; i >= 0; i--)
		{
			ZenTreasure_StashTrigger existingTrigger = m_Triggers.Get(i);
			if (existingTrigger == trigger)
			{
				existingTrigger.DeleteSafe();
				m_Triggers.Remove(i);
			}
		}
	}
}

// This trigger spawns a buried stash when the player who activated the treasure hunt enters it
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
			return;

		PlayerBase player = PlayerBase.Cast(obj);
		if (!player)
			return;
		
		ZenOnEnter(player);
	}
	
	void ZenOnEnter(PlayerBase player)
	{
		ZMPrint("[ZenTreasure] Player " + player.GetCachedID() + " entered trigger.");

		int stashType = -1;
		for (int i = m_TreasureConfig.TreasureHunters.Count() - 1; i >= 0; i--)
		{
			ZenTreasureHunter hunter = m_TreasureConfig.TreasureHunters.Get(i);
			if (hunter.ZenPlayerID == player.GetCachedID())
			{
				stashType = hunter.ZenStashID;
				m_TreasureConfig.TreasureHunters.Remove(i);
				GetZenTreasureDB().Save();
				break;
			}
		}

		if (stashType == -1)
			return;

		// Spawn treasure, delete self + delete config.
		SpawnTreasureLoot(player, stashType);
	}

	//! LOOT SPAWN CODE
	void SpawnTreasureLoot(notnull PlayerBase player, int stashType)
	{
		int i;
		int j;

		ZenTreasureStashType treasureConfig = GetZenTreasureConfig().TreasureTypes.Get(stashType);
		if (!treasureConfig)
		{
			Error("[ZenTreasure] Could not spawn treasure loot - config not found for m_StashType=" + stashType);
			return;
		}

		// Check for existing treasure and delete
		array<Object> objectsNearTreasure = new array<Object>;
		g_Game.GetObjectsAtPosition3D(m_TreasureConfig.Position, 1, objectsNearTreasure, NULL);
		for (i = 0; i < objectsNearTreasure.Count(); i++)
		{
			Object obj = objectsNearTreasure.Get(i);
			if (obj && obj.IsKindOf("ZenTreasure_UndergroundStash"))
				g_Game.ObjectDelete(obj);
		}

		// Spawn container
		EntityAI container = EntityAI.Cast(g_Game.CreateObject(treasureConfig.ContainerType, m_TreasureConfig.Position - "0 10 0", ECE_SETUP));
		if (!container)
		{
			Error("[ZenTreasure] Failed to spawn treasure loot container - " + treasureConfig.ContainerType + " @ " + m_TreasureConfig.Position);
			return;
		}

		// Clone loot array which auto-deletes after spawning everything (makes it easier to load generic loot from all possible loot configs)
		array<ref ZenTreasureLootSpawn> tempLootArray = new array<ref ZenTreasureLootSpawn>;

		// If loot type is 0 or 1 (generic) then fill Loot array with all possible loot 
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

		// Spawn loot into container 
		int lootCount = 0;
		for (i = 0; i < tempLootArray.Count(); i++)
		{
			ZenTreasureLootSpawn lootSpawn = tempLootArray.Get(i);

			if (lootSpawn.ClassName.Contains("Predef_"))
			{
				foreach (ZenTreasurePredefinedType predefLoot : GetZenTreasureConfig().PredefinedTypes)
				{
					if (predefLoot.ConfigName == lootSpawn.ClassName)
					{
						lootSpawn = predefLoot.Item;
						break;
					}
				}
			}

			EntityAI itemSpawned = ZenSpawnLootItem(container, lootSpawn);
			if (itemSpawned != NULL)
			{
				lootCount++;

				// Spawn attachments
				for (j = 0; j < lootSpawn.Attachments.Count(); j++)
				{
					lootCount++;
					if (ZenSpawnLootItemAttachment(itemSpawned, lootSpawn.Attachments.Get(j)) == NULL)
						ZenSpawnLootItemAttachment(container, lootSpawn.Attachments.Get(j)); // If couldn't spawn on gun, try spawning in container
				}
			}
		}

		// Spawn stash
		float heightOffset = 0.24;
		UndergroundStash stash = UndergroundStash.Cast(g_Game.CreateObject("ZenTreasure_UndergroundStash", m_TreasureConfig.Position, ECE_PLACE_ON_SURFACE));

		if (!stash)
		{
			Error("[ZenTreasure] Failed to spawn buried UndergroundStash @ " + m_TreasureConfig.Position);
			return;
		}

		stash.PlaceOnGround();

		// Correct for surface placement (if buried below treehouse for example, PlaceOnGround places the stash on the treehouse floor)
		vector stashPos = stash.GetPosition();
		stashPos[1] = g_Game.SurfaceY(stashPos[0], stashPos[2]) + heightOffset;
		stash.SetPosition(stashPos);

		// Align to ground 
		vector transform[4];
		stash.GetTransform(transform);
		vector ground_position, ground_dir; 
		int component;
		DayZPhysics.RaycastRV(transform[3], transform[3] + transform[1] * -100, ground_position, ground_dir, component, null, null, null, false, true);
		vector surface_normal = g_Game.SurfaceGetNormal(ground_position[0], ground_position[2]);
		vector local_ori = stash.GetDirection();
		transform[0] = surface_normal * local_ori;
		transform[1] = surface_normal;
		transform[2] = surface_normal * (local_ori * vector.Up);
		stash.SetTransform(transform);
		stash.Update();

		// Place container inside stash and set persistence
		stash.SetLifetimeMax(GetZenTreasureConfig().TreasureStashPersistenceSecs);
		stash.SetLifetime(GetZenTreasureConfig().TreasureStashPersistenceSecs);
		
		// Why the fuck doesn't this callqueue work anymore? 1.29 bug? CallQueue doesn't trigger ZenMoveToStash() at all anymore
		//ZMPrint("[ZenTreasure] Schedule loot transfer to stash.");
		//g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ZenMoveToStash, 1000, true, player, container, stash);

		ZenMoveToStash(player, container, stash);
		
		// Finally, remove this trigger.
		GetZenTreasure_Triggers().RemoveTrigger(this);

		ZMPrint("[ZenTreasure] " + player.GetCachedID() + " spawned treasure stash @ " + m_TreasureConfig.Position + " with config " + treasureConfig.ConfigName + " lootCount=" + lootCount);
	}

	void ZenMoveToStash(PlayerBase player, EntityAI container, UndergroundStash stash)
	{
		ZMPrint("[ZenTreasure] ZenMoveToStash player=" + player + " container=" + container + " stash=" + stash);
		
		if (!player)
		{
			Error("ZenMoveToStash triggered with null player!");
			return;
		}
		
		if (!container)
		{
			Error("ZenMoveToStash triggered with null container!");
			return;
		}
		
		if (!stash)
		{
			Error("ZenMoveToStash triggered with null stash!");
			return;
		}
		
		if (player.ServerTakeEntityToTargetCargo(stash, container))
		{
			ZMPrint("[ZenTreasure] Took container " + container.GetType() + " to stash " + stash.GetType() + " @ " + stash.GetPosition());
			g_Game.GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(ZenMoveToStash);
		}
		else 
		{
			Error("Failed to take " + container + " to stash " + stash);
		}
	}

	EntityAI ZenSpawnLootItem(EntityAI lootEAI, ZenTreasureLootSpawn lootSpawn)
	{
		// Check random chance
		if (!lootEAI || !lootSpawn || !lootEAI.GetInventory() || Math.RandomFloat01() > lootSpawn.SpawnChance)
			return NULL;

		// Create item
		string itemType = lootSpawn.ClassName;

		// Check if it's a list
		if (itemType.Contains("|"))
		{
			TStringArray itemList = new TStringArray;
			itemType.Split("|", itemList);
			itemType = itemList.GetRandomElement();
		}

		EntityAI item = lootEAI.GetInventory().CreateInInventory(itemType);
		if (!item)
			item = lootEAI.GetInventory().CreateAttachment(itemType);

		if (!item)
			return NULL;

		// If item was successfully created, set its health & quantity
		item.EEOnCECreate();
		int quantity = Math.RandomIntInclusive(lootSpawn.MinQuantity, lootSpawn.MaxQuantity);
		float health = Math.RandomFloatInclusive(lootSpawn.MinHealth / 100, 1.0);

		Ammunition_Base ammo = Ammunition_Base.Cast(item);
		if (ammo) // Item is ammunition, treat it differently to itembase
		{
			ammo.ServerSetAmmoCount(quantity);
			ammo.SetHealth(item.GetMaxHealth() * health);
		}
		else // Item is ItemBase
		{
			ItemBase ib = ItemBase.Cast(item);
			if (ib)
			{
				ib.SetHealth(ib.GetMaxHealth() * health);

				if (ib.ConfigIsExisting("quantityBar") && ib.ConfigGetFloat("quantityBar") != 1)
				{
					ZenFunctions.SetQuantity(ib, quantity);
				}
				else
				if (ib.GetQuantity() != quantity)
				{
					EntityAI item2;
					ItemBase itemBase2;

					for (int i = 0; i < lootSpawn.MaxQuantity - 1; i++)
					{
						if (lootEAI && lootEAI.GetInventory() && Math.RandomFloat01() <= lootSpawn.SpawnChance)
						{
							itemBase2 = ItemBase.Cast(lootEAI.GetInventory().CreateInInventory(itemType));

							if (item2)
							{
								if (item2.IsKindOf("ZenSwissKnife") || item2.IsKindOf("ZenTreasure_PhotoBase"))
									continue;

								float health2 = Math.RandomFloatInclusive(lootSpawn.MinHealth / 100, 1.0);
								itemBase2 = ItemBase.Cast(item2);

								if (itemBase2)
								{
									itemBase2.SetHealth(itemBase2.GetMaxHealth() * health2);
								}
							}
						}
					}
				}
			}
		}

		return item;
	}

	EntityAI ZenSpawnLootItemAttachment(EntityAI lootEAI, string itemType)
	{
		if (!lootEAI || !lootEAI.GetInventory())
			return NULL;

		float chance = 1.0;
		float minHealth = 0.1;
		int quantity = 1;

		// Check if it's a list
		if (itemType.Contains("|"))
		{
			TStringArray parameters = new TStringArray;
			itemType.Split("|", parameters);
			foreach (string s : parameters)
			{
				s.ToLower();
				if (s.Contains("c="))
				{
					s.Replace("c=", "");
					chance = s.ToFloat();
				}
				else 
				if (s.Contains("h="))
				{
					s.Replace("h=", "");
					minHealth = s.ToFloat();
				}
			}
			itemType = parameters.Get(0);
		}

		if (Math.RandomFloat01() > chance)
			return NULL;

		EntityAI item = lootEAI.GetInventory().CreateInInventory(itemType);
		if (!item)
			item = lootEAI.GetInventory().CreateAttachment(itemType);

		if (!item)
			return NULL;

		// If item was successfully created, set its health & quantity
		float health = item.GetMaxHealth() * Math.RandomFloatInclusive(minHealth, 1.0);
		item.SetHealth(health);
		return item;
	}
}
