class ZenTreasure_RandomPhoto extends ZenTreasure_PhotoBase
{
	static ref array<int> ALLOWED_PHOTO_IDS = new array<int>;

	override void EEInit()
	{
		super.EEInit();

		if (GetGame().IsDedicatedServer())
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ShapeshifterMorph, 1000, false);
	}

	private void ShapeshifterMorph()
	{
		string spawnType = "ZenTreasure_Photo";

		int rand = ALLOWED_PHOTO_IDS.GetRandomElement();
		if (rand < 10)
		{
			spawnType = spawnType + "0" + rand.ToString();
		}
		else
		{
			spawnType = spawnType + rand.ToString();
		}

		GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, new ReplacePhotoWithNewLambda(this, spawnType));
	}
}

class ReplacePhotoWithNewLambda : ReplaceItemWithNewLambdaBase
{
	void ReplacePhotoWithNewLambda(EntityAI old_item, string new_item_type)
	{
		m_OldItem = old_item;
		m_NewItemType = new_item_type;
	}

	override void OnSuccess(EntityAI new_item)
	{
		if (new_item != NULL)
		{
			MiscGameplayFunctions.TransferItemProperties(m_OldItem, new_item);
			new_item.SetLifetimeMax(m_OldItem.GetLifetimeMax()); // Inherit original item's persistence timer
			new_item.SetHealth(new_item.GetMaxHealth()); // Don't allow fresh spawned photos to be damaged as they're hard to see
		}
	}
}