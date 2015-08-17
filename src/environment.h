
typedef unsigned short ordinal;

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


#include "name_handling.cpp"

//ItemSpecies

class ItemSpecies: public named {
public:
	ItemSpecies () = default;
	ItemSpecies (ItemSpecies const &base) = default;
	ItemSpecies (DevStrType dev_str_c): named{dev_str_c} {}
};

Catalogue<ItemSpecies> cat_item;

//Item

typedef ordinal ItemType;

class item {
private:
	ItemType type_id;
public:
	item (ItemType type_id_c = 0): type_id(type_id_c) {}
	item (item const& base): item(base.type_id) {}
	
	//static item* newitem (ItemType, item**, LocId);
	ItemType setType (ItemType type_id_c) {return (type_id = type_id_c);}
	ItemType getType () const {return type_id;}
	ItemSpecies& getTypeData () const {return cat_item.space[type_id];}
	DevStrType& getName () const {return getTypeData().dev_str;}
	
	bool operator== (item comp) {return (type_id == comp.type_id);}
	bool operator!= (item comp) {return (type_id != comp.type_id);}
};




class ItemSpace {
private:
	std::vector<item*> holdings;
	mutable unsigned minfree = 0;
	item* GetFromMin() {
		if (holdings.size() > minfree)
			return holdings[minfree];
		minfree = holdings.size();
		holdings.push_back(nullptr);
		return nullptr;
	}
		
		
public:
	std::vector<item*> const el () const {return holdings;}
	template<class... Args>
	unsigned create(Args... args) {
		while (GetFromMin() != nullptr) 
			minfree++;
		holdings[minfree] = new item (args...);
		return minfree++;
	}
	item remove(unsigned i) {
		item retval (*holdings[i]);
		delete holdings[i];
		holdings[i] = nullptr;
		minfree = i;
		return retval;
	}
	unsigned find(item comp) {
		unsigned i = 0;
		while (i < holdings.size())
			if (*holdings[i] == comp)
				break;
			else
				i++;
		return i;
	}
	
	~ItemSpace () {
		for (item* i: holdings)
			delete i;
	}
};
 
 
 
 
 