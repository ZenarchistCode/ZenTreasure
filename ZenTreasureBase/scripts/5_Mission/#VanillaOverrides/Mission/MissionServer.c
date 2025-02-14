modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		GetZenTreasureConfig();
		GetZenTreasure_Triggers().SpawnStartupTriggers();
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);

		SendZenTreasureConfig(player, identity);
	}

	void SendZenTreasureConfig(PlayerBase player, PlayerIdentity identity)
	{
		array<string> m_treasureDescriptions = new array<string>;
		foreach(ZenTreasureStashType treasure : GetZenTreasureConfig().TreasureTypes)
		{
			m_treasureDescriptions.Insert(treasure.Description);
		}

		GetRPCManager().SendRPC("ZenMod_RPC", "RPC_ReceiveZenTreasureTextClient", new Param1<array<string>>(m_treasureDescriptions), true, player.GetIdentity());
	}
}