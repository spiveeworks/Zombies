
//scaffold

class scaffold {
	string debug;
	bool isdefined;
public:
	scaffold (string name) {debug = name; isdefined = true;}
	scaffold () {isdefined = false;}
	bool operator== (string name) {return name == debug;}
	bool operator!= (string name) {return name != debug;}
	bool define (string name) {
		if (isdefined) 
			return false; 
		debug = name;
		return true;
	}
	bool operator= (string name) {return define (name);}
	string getname () {return debug;}
};

interpretor<scaffold> type;

//Item

class item {
	//item** container;
	//LocId index;
	ItemType typeId;
public:
	//static item* newitem (ItemType, item**, LocId);
	ItemType setid (ItemType typeId2) {return (typeId = typeId2);}
	ItemType getid () {return typeId;}
	item (ItemType typeId2) {typeId = typeId2;}
};
/*
item* item::newitem (ItemType type, item** container, LocId index) {
	item* retval = new item (type);
	container [index] = retval;
	retval -> container = container;
	retval -> index = index;
	return retval;
}
*/

//Sack
sack hand;
interpretor <sack> Santa;

void CreateForMe (item* &pass, ItemType data) {
	pass = new item (data);
}
void MoveForMe (item* &pass, unsigned containerid) {
}
/*
class sack {
	std::vector<item*> holdings;
	bool issaturated;
	unsigned int sat;//number of objects (saturated length)
	unsigned int unsat;//number of continuous spaces including the first one and the last existing object in the vector (unsaturated length)
public:
	unsigned int saturate ();
	unsigned int unsaturation () {return unsat - sat;}//says the amount of unnecesary spaces in the array.\
	Call the function "saturate" when this number gets too large \
	in order to increase efficiency of the object.
	item* operator[] (unsigned int i) {return holdings [i];}
	item* replace (const LocId& p, item* object);
	LocId getblank ();
	LocId findtype (ItemType type);
	bool deleteitem (LocId target);
	LocId spawnitem (ItemType id);
}hand;
*/
/*
unsigned int sack::saturate () {
	for (LocId i = 0, j = 0; i < sat && j < unsat; j++) 
		if (holdings [j] != 0) 
			holdings [i++] = holdings [j];
	unsat = sat;
	holdings.resize (sat);
}

item* sack::replace (const LocId& p, item* object) {
	item* retval = 0;
	unsigned char i = p - 1;
	if (p > unsat) 
		holdings.resize (unsat = p);
	else
		retval = holdings [i];
	holdings [i] = object;
	if (retval == 0) unsat++;
	if (object == 0) unsat--;
	return retval;
}

LocId sack::getblank () {
	if (sat == unsat) return (unsat + 1);
	unsigned char i = 0;
	while (holdings [i] != 0) i++;
	return i+1;//one more so that it is a loc reference not an array reference
}

LocId sack::findtype (ItemType type) {
	for (LocId i = 0; i < unsat; i++) 
	{
		if (holdings [i] = 0) break;
		if (holdings [i] -> getid () == type) return (i+1);
	}
	return 0;
}

bool sack::deleteitem (LocId target) {
	if (holdings [target] == 0)
		return false;
	delete holdings [target];
	replace (target, 0);
	
	return true;
}

LocId sack::spawnitem (ItemType id) {
	LocId use = getblank ();
	replace (use, new item (id));
	return use;
}
*/