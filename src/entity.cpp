
class entity;

//How will domains work??
//Set of universal entries?
//Pass universe to domain function?
//Sounds good, but then domains would be nested inside universes? golly idk man

#include "entity_module.cpp"

typedef unsigned int EntityId;



// * * * * ** //
// * Entity * //
// ** * * * * //


class entity {
public:
	virtual module* ShowMod (ModClassNum) = 0;
	virtual module& FindMod (ModClassNum) = 0;
};

class GenericEntity: public entity {//not tested lol
protected:
	std::vector<unsigned char> bytes;
	std::map<ModClassNum, unsigned> lace;
public:
	template<class MCNCon>
	GenericEntity (MCNCon ModNums) {
		ModSizeNum i = 0;
		for (ModClassNum n: ModNums)
		{
			//Map the given module to this offset
			lace[n] = i;
			//Find the size of such a module, then increase the offset by this size
			i += mod::CN2Size (n);
		}
		bytes.resize(i/sizeof(unsigned char));
	}
	GenericEntity (GenericEntity const&) = default;
	
	module* ShowMod (ModClassNum mod) {
		return (module*)(bytes.data() + lace.at(mod));
	}//This is kind of beautiful, you've gotta admit
	module& FindMod (ModClassNum mod) {return *ShowMod(mod);}
};

// * * * * * * * * * * * //
// * Stock Definitions * //
// * * * * * * * * * * * //


namespace StockEntity 
{
	template<class Mods>
	class Stock: public entity {
	public:
		union {
			Mods modules;
			unsigned char bytes[sizeof(Mods)/sizeof(unsigned char)];
		};
		module& FindMod (ModClassNum num) {return modules.FindMod(num);}
		module* ShowMod (ModClassNum num) {return &FindMod(num);}
		
		Stock(): modules() {}
		~Stock() {}
	};
	
	struct doorbase {
	public:
		mod::BasicLock lock;
		module& FindMod (ModClassNum num) {
			switch (num) 
			{
				case 2: return lock;
				default: throw std::out_of_range("Bad Ask");
			}
		}
	};
	class door: public Stock<doorbase> {};
	struct cabinetbase {
	public:
		mod::BasicLock lock{};
		mod::Inventory content{};
		module& FindMod (ModClassNum num) {
			switch (num)
			{
				case 2: return lock;
				case 4: return content;
				default: throw std::out_of_range("Bad Ask");
			}
		}
	};
	class cabinet: public Stock<cabinetbase> {};
}


