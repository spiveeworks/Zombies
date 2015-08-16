/* 


struct DevStrType {
	char d_str[DEVSTR_LEN];
	DevStrType (const char* base = "") {
		for (unsigned char i = 0; i < DEVSTR_LEN; i++) 
		{
			d_str[i] = base[i];
			if (base[i]=='\0') break;
		}
		d_str[DEVSTR_LEN-1] = '\0';
	}
	DevStrType (DevStrType const& devstr_str): DevStrType(devstr_str.d_str) {}
	DevStrType (std::string const& devstr_str): DevStrType(devstr_str.c_str()) {}
	
	
	DevStrType& operator= (char const* base) {
		for (unsigned char i = 0; i < DEVSTR_LEN; i++) 
		{
			d_str[i] = base[i];
			if (base[i]=='\0') break;
		}
		d_str[DEVSTR_LEN-1] = '\0';
	}
	inline DevStrType& operator= (DevStrType base) {return operator=(base.d_str);}
	inline DevStrType& operator= (std::string const& base) {return operator=(base.c_str());}
	
	bool operator== (char const* comp) const {
		for (unsigned char i = 0; i < DEVSTR_LEN; i++)
		{
			if (d_str[i] != comp[i]) return false;
			if (d_str[i] == '\0') break;
		}
		return true;
	}
	inline bool operator== (DevStrType comp) const {return operator== (comp.d_str);}
	inline bool operator== (std::string const& comp) const {return operator== (comp.c_str());}
	bool operator< (char const* comp) const {
		for (unsigned char i = 0; i < DEVSTR_LEN; i++)
		{
			if (d_str[i] != comp[i]) return d_str[i] < comp[i];
			if (d_str[i] == '\0') break;
		}
		return true;
	}
	inline bool operator< (DevStrType comp) const {return operator< (comp.d_str);}
	inline bool operator< (std::string const& comp) const {return operator< (comp.c_str());}
	
	bool operator!= (char const* comp) const {
		for (unsigned char i = 0; i < DEVSTR_LEN; i++)
		{
			if (d_str[i] != comp[i]) return true;
			if (d_str[i] == '\0') break;
		}
		return false;
	}
	inline bool operator!= (DevStrType comp) const {return operator!= (comp.d_str);}
	inline bool operator!= (std::string const& comp) const {return operator!= (comp.c_str());}
	
	
};
*/

#define DEVSTR_LEN 16
typedef std::array<char, DEVSTR_LEN> DevStrType;

DevStrType& MakeDevStr (std::string const &base, DevStrType& fill) {
	if (base.size() >= DEVSTR_LEN)
		return MakeDevStr (base.substr(0,DEVSTR_LEN - 1), fill);
	auto oIt = fill.begin(), oEnd = fill.end();
	for (const char& i: base)
		*(oIt++) = i;
	while (oIt != oEnd)
		*(oIt++) = '\0';
	return fill;
}

/* 
DevStrType& MakeDevStr (const char *base, DevStrType& fill) {
	unsigned i = 0;
	for (char j = base[i]; j != '\0' && i < DEVSTR_LEN - 1; j = base[++i])
		fill[i] = j;
	while (i < DEVSTR_LEN)
		fill[i++] = '\0';
	return fill;
}
 */

template<class C>
DevStrType MakeDevStr (C const &base) {
	DevStrType out;
	return MakeDevStr(base, out);
}

class named {
public:
	DevStrType dev_str;
	named () = default;
	named (named const &base) = default;
	named (DevStrType const &dev_str_c): dev_str(dev_str_c) {}
	named (std::string dev_str_str): dev_str(MakeDevStr(dev_str_str)) {}
	
};

template<class likenamed>
class Catalogue {
public:
	std::vector<likenamed> space;
	std::map<DevStrType, unsigned> sorted;
	Catalogue (): space(), sorted() {
		static_assert(std::is_base_of<named, likenamed>::value, "Bad Catalogue initialised.");
	}
	Catalogue (Catalogue<likenamed> const&) = default;
	
	template <typename... Args>
	Catalogue (Args... args): space(args...), sorted() {
		static_assert(std::is_base_of<named, likenamed>::value, "Bad Catalogue initialised.");
		for (unsigned i = 0; i < space.size(); ++i)
			sorted[space[i].dev_str] = i;
	}
};

/* 
ordinal NameToOrdinal (namelist const& within, DevStrType const& goalstr) {
	for (ordinal num = 1; num < within.size(); num++)
		if (within[num] -> devstr == goalstr) return num;
	return 0;
};
inline named* NameToObject (namelist const& within, DevStrType const& goalstr) {return within[NameToOrdinal(within, goalstr)];}

ordinal ObjectToOrdinal (namelist const& within, named *object) {
	for (ordinal num = 1; num < within.size(); num++)
		if (within[num] == object) return num;
	return 0;
}
inline ordinal ObjectToOrdinal (namelist const& within, named &object) {return ObjectToOrdinal(within, &object);}

//note that ObjectToName would be equivalent to object -> devstr \
	No implementation for u as a result
 */
