#include <string>
#include <vector>
#include <IOstream>
#include <sstream>

//using namespace std;
typedef std::string string;

typedef unsigned short LocId;
enum failstate {
	invalid = -1,//the task is actually impossible for an obscure reason, such as the thing trying to be read is a mackerel.
	success = 0,//The task worked
	generic,//The task failed in a predictable way (ie simply not capable)	
	distant, //an item involved in the task is out of reach or is in another location entirely
	interrupted,//The task was cancelled or made impossible due to an event that happened in its progression
	nodouble,//The task has already been completed and cannot be completed again
	isprotected,//The task is being prevented by some form of protection
	badinstrument//The task failed on account of the object being used to complete the task
};

#include "template.cpp"

#line 1 "eco.item.h"
typedef unsigned char ItemType;

class scaffold;
class item;

typedef ReferenceVector<item> sack;

//class sack;


#line 1 "eco.entity.h"
typedef unsigned char EntityType;

class entity;
class module;

module* createmodule (unsigned m);

unsigned* GetStockModuleSet (unsigned number);
unsigned GetStockModuleSize (unsigned number);

#line 0 "template.h"

void CreateForMe (item* &pass, ItemType data);
void CreateForMe (entity* &pass, ItemType data);

void MoveForMe (item* &pass, unsigned containerid);
void MoveForMe (entity* &pass, unsigned containerid);

#line 0 "entity.class"

typedef ReferenceVector<entity> EntitySet;

class domain {
public:
	sack ground;
	EntitySet entities;
	
	bool contains (entity& detail) {
		for (unsigned i = 1; i <= entities.capacity(); i++)
			if entities[i] = &detail
				return true;
		return false;
	}
	
}*focusdomain;