#include "eco.h"

#define ECO_ITEM_axe 0x0001
#define ECO_ITEM_bat 0x0002

//#include <IOstream>


#include "eco.item.cpp"
#include "eco.entity.cpp"

// * * * * * * * * * * * //
// * Class Definitions * //
// * * * * * * * * * * * //



//struct

struct locator {
	sack* context;
	LocId index;
	locator (sack* plc, LocId loc) {context = plc; index = loc;}
};

// * * * * * * * * * * * * ** //
// * Manipulation Functions * //
// ** * * * * * * * * * * * * //




void CreateForMe (entity* &pass, EntityType data) {
	pass = new entity(*focusdomain, GetStockModuleSet(data), GetStockModuleSize(data));
}

void MoveForMe (entity* &object, unsigned containerid) {
	object -> location = focusdomain;
}


// * Miscellaneous * //

string stringifystate (failstate convert) {
	switch (convert)
	{
#define returncase(string) case string: return (#string);
	returncase(invalid)
	returncase(success)
	returncase(generic)
	returncase(interrupted)
	returncase(nodouble)
	returncase(isprotected)
	returncase(badinstrument)
#undef returncase
	default: return ("generic");
	}
};

string stringifystate (bool convert) {
	if (convert)
		return "true";
	else
		return "false";
}