DayZ  Code To Give Fresh Spawns One Of Three Medieval Loadouts On Community Or Local Server xml Snippet Mod Changelog & Terms Of Use

Limited Testing on PC Chernarus Local Server DAYZ Version 1.21 May 2023.

Created by @scalespeeder. Please report bugs & errors to scalespeeder@gmail.com with screenshots.

TERMS OF USE
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Using these modded xml files could break the functioning of your DAYZ server, requiring a reinstall that would wipe
all player progress.

Using these modded xml files neccessitates increased regular restarts to prevent server crashing.

It is suggested you thoroughly test your server after applying these files to ensure proper
functioning of your server.

To activate the code to give fresh spawns on of three random loadots (AXE / SWORD / MACE) either upload the complete init.c file provided over the top of your existing
init.c inside your mission folder (only really recommended for Chernarus Servers) OR copy and paste the below Code Snippet over the top of the existing section in your init.c :
(Look for the "class case CustomMission:" entry, and you're copy and pasting over the top of that, including the code right to the end of the file.

// AUTHOR: teaearlgraycold @ https://gist.github.com/teaearlgraycold/8c20f5c5582e84f7fd6c64a9a2247423 
// Code Obtained from https://github.com/ravmustang/DayZ_SA_ClassName_Dump/blob/master/Everything%20DayZ/DayZ%20SA%20Community%20Scripting/PVPLoadout_init.c
// Below code until end is the code that creates the three different random loadouts

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





Thanks, Rob.