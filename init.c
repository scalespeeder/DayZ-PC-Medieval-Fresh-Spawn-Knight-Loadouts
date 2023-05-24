void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

class CustomMission: MissionServer

{
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);
		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	

	EntityAI assaultClass(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("WoodAxe");
		

		return gun;
	}

	EntityAI sniperClass(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("Sword");

		return gun;
	}

	EntityAI smgClass(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("Mace");
		

		return gun;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		player.RemoveAllItems();
		
	player.GetInventory().CreateInInventory("Chainmail");
		player.GetInventory().CreateInInventory("Chainmail_Coif");
		player.GetInventory().CreateInInventory("Chainmail_Leggings");
		player.GetInventory().CreateInInventory("Chestplate");
		player.GetInventory().CreateInInventory("MedievalBoots");
		player.GetInventory().CreateInInventory("WoolGlovesFingerless_Green");
		player.GetInventory().CreateInInventory("Apple");
		player.GetInventory().CreateInInventory("DisinfectantAlcohol");
		player.GetInventory().CreateInInventory("Pear");
		player.GetInventory().CreateInInventory("Lard");
		player.GetInventory().CreateInInventory("Vodka");
		player.GetInventory().CreateInInventory("Ammo_HuntingBolt");
		player.GetInventory().CreateInInventory("HuntingKnife");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);

		EntityAI primary;
		EntityAI axe = player.GetInventory().CreateInInventory("Crossbow_Wood");

		switch (Math.RandomInt(0, 3)) {
			case 0: primary = assaultClass(player); break;
			case 1: primary = sniperClass(player); break;
			case 2: primary = smgClass(player); break;
		}

		player.LocalTakeEntityToHands(primary);
		player.SetQuickBarEntityShortcut(primary, 0, true);
		player.SetQuickBarEntityShortcut(primary, 0, true);
		player.SetQuickBarEntityShortcut(rags, 2, true);
		player.SetQuickBarEntityShortcut(axe, 3, true);
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
