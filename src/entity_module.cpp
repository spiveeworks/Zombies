
typedef unsigned short ModClassNum;
typedef unsigned int ModSizeNum;
	
struct module {
public:
	virtual inline constexpr ModClassNum ModId () const = 0;
	virtual inline constexpr ModSizeNum ModSize () const = 0;
//friend entity; //not needed I believe?
};

namespace mod
	{


// * * * * * * * * * * ** //
// * Module Definitions * //
// ** * * * * * * * * * * //

template<ModClassNum T_id, class T_mod>
struct ModuleFactory: public module {
	inline constexpr ModClassNum ModId () const {return T_id;}
	inline constexpr ModSizeNum ModSize () const {return sizeof(T_mod);}
};

#define Define_Module(T_id, T_mod) T_mod: public ModuleFactory<T_id, T_mod>
	//	Sorry about this.

struct Define_Module (1, Counter) {
public:
	unsigned char count;
};


struct OpenState {
public:
	bool isopen;
	virtual failstate open() {
		if (isopen) 
			return nodouble; 
		isopen = true; 
		return success;
	}
	failstate shut() {
		if (!isopen) 
			return nodouble; 
		isopen = false; 
		return success;
	}
};

struct Define_Module (2, BasicLock), public OpenState {
public:
	bool islocked;
	virtual failstate lock() {if (islocked) return nodouble; islocked = true; return success;}
	virtual failstate unlock() {if (!islocked) return nodouble; islocked = false; return success;}

	failstate open() {
		if (islocked) 
			return isprotected; 
		return OpenState::open();
	}
};

struct Define_Module (3, Inventory) {
public:
	ItemSpace content;
};
/* 
struct Define_Module (5, Conduit) {
public:
	domain *Aside, *Bside;
	failstate transfer (EntityId toswap) {
		auto tryA = Aside -> ent.find(toswap);
		auto tryB = Bside -> ent.find(toswap);
		if (tryA != Aside -> ent.end())
		{
			Bside -> ent[toswap] = move(*tryA);
			Aside -> ent.remove(toswap);
			return success;
		}
		if (tryB != Bside -> ent.end())
		{
			Aside -> ent[toswap] = move(*tryB);
			Bside -> ent.remove(toswap);
			return success;
		}
		return distant;
	}
};
 */
#undef Define_Module

// * * * * * * * * * ** //
// * Module Functions * //
// ** * * * * * * * * * //

constexpr ModSizeNum CN2Size (ModClassNum m) {
#define checkfor(i, T_mod) (i == m)? sizeof(T_mod):
	return 
		0==m ? sizeof(module) :
		checkfor (1,Counter)
		checkfor (2,BasicLock)
		checkfor (3,Inventory)
		//checkfor (Conduit)
	-1;
#undef checkfor
}

	}
