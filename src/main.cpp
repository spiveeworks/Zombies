
#include <string>

#include <array>
#include <vector>
#include <map>
#include <list>

#include "environment.h"


#include <iostream>
#include <sstream>

using namespace std;

ItemSpace hand;

#include "commands.h"


ComCon::context HC_Cc_main ();

ComCon::context Cc_interpret;


#define APPEND(ident) push_back(ComCon::command(# ident , Co_::ident , " "))
ComCon::context HC_Cc_main () {
	std::vector<ComCon::command> set;
	set.APPEND(exit);
	set.APPEND(spawn);
	set.APPEND(destroy);
	set.APPEND(identify);
	set.APPEND(open);
	ComCon::context out;
	out.script_d = Co_::badcommand;
	swap(out.comm, set);
	return out;
}
#undef APPEND


int main () {
	ItemSpecies test;
	{
		ItemSpecies temp[3];
#define INIT_SPECIES(pre, num, name) const ItemType pre ## name = num; temp[num] = ItemSpecies(MakeDevStr(#name));
#define SPEC_CONST xECO_ITEM_
		INIT_SPECIES (SPEC_CONST_, 0, null);
		INIT_SPECIES (SPEC_CONST_, 1, axe);
		INIT_SPECIES (SPEC_CONST_, 2, bat);
#undef INIT_SPECIES
#undef SPEC_CONST
		
		cat_item = Catalogue<ItemSpecies> (temp, temp + 3);
	}
	/* 
	for (ItemSpecies &test2: cat_item.space)
		cout << (test2.dev_str == test.dev_str);
	*/
	
	//Santa.push_back (&hand, "hand");
	
//	room.entities.spawnel (1);
//	room.entities.spawnel (2);
//	IntEnt.push_back (room.entities[1], "door");
//	IntEnt.push_back (room.entities[2], "cabinet");
	
	//EntitySet ents;
	
	
//	entity* door = new entity (room, GetStockModuleSet(1), GetStockModuleSize(1));//make a door for individual testing
//	cout << (int) ents.replace(1, door) << "\r\n";
	//cout << ents.spawnel(1) << "\r\n";
	//mod_openstate* OS = getmod_OS (*(ents[1]));
//	std::cout << "hit!";
	//cout << ents[1] -> getmem();
	//cout << stringifystate (OS -> open()) << "\r\n";
	//cout << ents[1] -> getmem();
	
	//std::cout << "  * * * END DEBUG * * *" << endl;
	Cc_interpret = HC_Cc_main ();
	Co_::spawn("axe");
	int retval = 0;
	while (retval == 0)
	{
		string command;
		cout << ">";
		getline (cin, command);
		retval = Cc_interpret(command);
	}
	return 0;
}
