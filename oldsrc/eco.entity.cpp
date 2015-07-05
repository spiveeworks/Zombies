

// * * * * * * * * * * ** //
// * Module Definitions * //
// ** * * * * * * * * * * //

#define SizeAndType(x,y) virtual inline unsigned memnum() {return (x);} virtual inline unsigned entid() {return (y);}
class module {
protected:
	char* memstart;
	
public:
	virtual inline unsigned memnum() {return (0);} 
	virtual inline unsigned entid() {return (0);}
friend entity;
};

class mod_counter: public module {
public:
	SizeAndType(1,1)
};


class mod_openstate: public module {
public:
	inline bool& isopen() {return ((bool*)memstart)[0];}
	virtual failstate open() {if (isopen()) return nodouble; isopen() = true; return success;}
	failstate shut() {if (!( isopen() )) return nodouble; isopen() = false; return success;}
	
	SizeAndType(sizeof(bool),2)
};

class mod_lockmech: public mod_openstate {
public:
	inline bool& islocked() {return ((bool*)memstart)[1];}
	virtual failstate lock() {if (islocked()) return nodouble; islocked() = true; return success;}
	virtual failstate unlock() {if (!islocked()) return nodouble; islocked() = false; return success;}

	failstate open() {
		if (islocked()) 
			return isprotected; 
		if (isopen()) 
			return nodouble; 
		isopen() = true; 
		return success;
	}
	
	SizeAndType(2*sizeof(bool),3)
};

class mod_inventory: public module {
public:
	inline sack& contains() {return **((sack**) memstart);}
	SizeAndType(sizeof(sack*),4)
};

class mod_transfer: public module {
public:
	inline domain& Aside() {return ((domain*)memstart)[0];}
	inline domain& Bside() {return ((domain*)memstart)[1];}
	failstate transfer (entity& toswap) {
		if (Aside().contains (toswap) )
		{
			Bside().giveent (toswap);
			return success;
		}
		if (Bside().contains (toswap))
		{
			Aside.givenet (toswap);
			return success;
		}
		return distant;
	}
	SizeAndType(sizeof(domain*)*2,5)
}

#undef SizeAndType

// * * * * * * * * * ** //
// * Module Functions * //
// ** * * * * * * * * * //

module* createmodule (unsigned m) {
#define givemodule(m, name) case m: return new mod_ ## name;
	switch (m)
	{
	givemodule(1, counter)
	givemodule(2, openstate)
	givemodule(3, lockmech)
	default:
		return new module;
	}
#undef givemodule
}

// * * * * ** //
// * Entity * //
// ** * * * * //

class entity {
protected:
	char* memory;
	unsigned size;
	
	module** modset;
	unsigned modnum;
public:
	domain* location;
	entity (domain& loc, unsigned* fnc, unsigned num) {
		location = &loc;
		modset = new module* [num];
		
		modnum = num;
		//std::cout << "DEBUG: length " << modnum << ": " << modset << "\r\n";
		size = 0;
		module* pass;
		for (unsigned i = 0; i < num; i++)
		{
			pass = createmodule (fnc[i]);
			modset[i] = pass;
			size += pass -> memnum();
		}
		memory = new char [size]();
		for (unsigned i = 0, j = 0; i < num; j += modset [i++] -> memnum ())
			modset[i] -> memstart = memory + j;
	}
	~entity () {
		for (unsigned i = 0; i < modnum; i++) delete modset[i];
		delete[] modset;
		delete[] memory;
	}
	bool containsmodule(unsigned modid) {
		module* pass;
		for (unsigned i = 0; i < modnum; i++)
		{
			std::cout << modset[i] -> entid () << " == " << modid << "\r\n";
			if (modset[i] -> entid () == modid)//this line causes a crash; problem with modset[i]
				return true;
		}
		return false;
	}
	unsigned getmodtype (unsigned modid) {return modset[modid] -> entid ();}
	module* operator[] (unsigned modid) {return modset[modid];}
	string getmem () {
		std::stringstream out;
		for (unsigned i = 0; i < modnum; i++)
			out 
				<< i 
				<< ": " 
				<< (unsigned) memory[i] 
				<< "; "
			;
		out << "\r\n";
		return out.str();
	}
};
// * * * * * * * * * * * * * * //
// * Entity Hard Definitions * //
// * * * * * * * * * * * * * * //

unsigned* GetStockModuleSet (unsigned number) {
	unsigned* retval;
	switch (number)
	{
		case 1://door
			retval = new unsigned [1];
			retval[0] = 2;//lockmech (openable and lockable)
			return retval;
		case 2://cabinet
			retval = new unsigned [2];
			retval[0] = 2;//openable
			retval[1] = 4;//contains items
			return retval;
		default:
			retval = 0;
			return 0;
	}
}

unsigned GetStockModuleSize (unsigned number) {
	switch (number)
	{
#define case(x,y) case x: return (y);
		case(1,1)
		case(2,2)
		default: return 0;
#undef case
	}
}



// *  * //

mod_openstate* getmod_OS (entity& tofind) {
	if 
	(!(
		tofind.containsmodule (2) 
	||
		tofind.containsmodule (3)
	))
		return 0;
	unsigned i = 0;
	while 
	(!(
		tofind.getmodtype(i) == 2 
	|| 
		tofind.getmodtype(i) == 3
	)) 
		i++;
	return (mod_openstate*) tofind[i];
}