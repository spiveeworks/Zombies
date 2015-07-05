#include "eco.cpp"


interpretor<entity> IntEnt;
domain room;
#include "commands.h"


context HC_Cc_main ();

context Cc_interpret;

bool takecommand () {
	string command;
	cout << ">";
	getline (cin, command);
	return (Cc_interpret (command) == 0);
}

#define comInit(ident) new command ( # ident , C_ ## ident , " ")
context HC_Cc_main () {
	context set = context() 
	+ comInit (exit)
	+ comInit (spawn)
	+ comInit (identify)
	+ comInit (open);
/*
	+ new command ("spawn", 	C_spawn		," ")
	//+ new command ("respawn", 	C_respawn	," ")
	+ new command ("identify", 	C_identify	," ");
	+ new command ("identify", 	C_identify	," ");
*/
	set.setDefault (C_badcommand);
	return set;
}


domain* playerlocation;

int main () {
/*
#define initialise(pre, num, name) const ItemType pre ## name = num; type [num] = #name;
	initialise (xECO_ITEM_, 0, null);
	initialise (xECO_ITEM_, 1, axe);
	initialise (xECO_ITEM_, 2, bat);
#undef initialise
*/
	Santa.push_back (&hand, "hand");
	
	type.Default.name = "null";
	type.push_back (new scaffold ("axe"), "axe");
	type.push_back (new scaffold ("bat"), "axe");
	
//	room.entities.spawnel (1);
//	room.entities.spawnel (2);
//	IntEnt.push_back (room.entities[1], "door");
//	IntEnt.push_back (room.entities[2], "cabinet");
	std::cout << "\r\n\r\n";
	
	EntitySet ents;
	
	
//	entity* door = new entity (room, GetStockModuleSet(1), GetStockModuleSize(1));//make a door for individual testing
//	cout << (int) ents.replace(1, door) << "\r\n";
	cout << ents.spawnel(1) << "\r\n";
	mod_openstate* OS = getmod_OS (*(ents[1]));
//	std::cout << "hit!";
	cout << ents[1] -> getmem();
	cout << stringifystate (OS -> open()) << "\r\n";
	cout << ents[1] -> getmem();
	
	Cc_interpret = HC_Cc_main ();
	bool retval;
	do {retval = takecommand ();}
	while (retval);
	return 0;
}
