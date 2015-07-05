
template<class T, typename META = unsigned char> 
class ReferenceVector {
	std::vector<T*> holdings;
	bool issaturated;
	unsigned int sat;//number of objects (saturated length)
	unsigned int unsat;//number of continuous spaces including the first one and the last existing object in the vector (unsaturated length)
public:
	unsigned int containerid;
	unsigned int saturate ();
	unsigned int unsaturation () {return unsat - sat;}//says the amount of unnecesary spaces in the array.\
	Call the function "saturate" when this number gets too large \
	in order to increase efficiency of the object.
	T* operator[] (LocId i) {return holdings [i-1];}
	T* replace (const LocId& p, T* object);
	LocId getblank ();
	LocId findtype (META type);
	bool deleteel (LocId target);
	LocId spawnel (META id);
	
	ReferenceVector (unsigned con = 0) {issaturated = true; sat = 0; unsat = 0; containerid = con;}
	unsigned size () {return sat;}
	unsigned capacity () {return unsat;}
};

template<class T, typename META>
unsigned int ReferenceVector<T,META>::saturate () {
	for (LocId i = 0, j = 0; i < sat && j < unsat; j++) 
		if (holdings [j] != 0) 
			holdings [i++] = holdings [j];
	unsat = sat;
	holdings.resize (sat);
}

template<class T, typename META>
T* ReferenceVector<T,META>::replace (const LocId& p, T* object) {
	T* retval = 0;
	unsigned char i = p - 1;
	if (p > unsat) 
		holdings.resize (unsat = p);
	else
		retval = holdings [i];
	holdings [i] = object;
	if (retval == 0) unsat++;
	if (object == 0) unsat--;
	else MoveForMe (object, containerid);
	return retval;
}

template<class T, typename META>
LocId ReferenceVector<T,META>::getblank () {
	if (sat == unsat) return (unsat + 1);
	unsigned char i = 0;
	while (holdings [i] != 0) i++;
	return i+1;//one more so that it is a loc reference not an array reference
}

template<class T, typename META>
LocId ReferenceVector<T,META>::findtype (META type) {
	for (LocId i = 0; i < unsat; i++) 
	{
		if (holdings [i] = 0) break;
		if (holdings [i] -> getid () == type) return (i+1);
	}
	return 0;
}

template<class T, typename META>
bool ReferenceVector<T,META>::deleteel (LocId target) {
	if (holdings [target] == 0)
		return false;
	delete holdings [target];
	replace (target, 0);
	
	return true;
}

template<class T, typename META>
LocId ReferenceVector<T,META>::spawnel (META id) {
	T* pass;
	LocId use = getblank ();
	CreateForMe (pass, id);
	replace (use, pass);
	return use;
}






template<typename T> 
struct interpretor {
	struct IntEl {
		T* thing;
		string name;
		inline bool test (string arg) {return (name == arg);}
		inline bool test (T* arg) {return (thing == arg);}
		inline bool test (T arg) {return (*thing == arg);}
		//IntEl (T* hold, string assoc) {thing = hold; name = assoc;}
	}Default;
	std::vector<IntEl> content;
	unsigned find (string tofind) {for (unsigned i = 0; i < content.size(); i++) if (content [i].test(tofind)) return i + 1; return 0;}
	unsigned find (T* tofind) {for (unsigned i = 0; i < content.size(); i++) if (content [i].test(tofind)) return i + 1; return 0;}
	T* operator[] (unsigned i) {if (i == 0) return Default.thing; return content [i - 1].thing;}
	string getname (unsigned i) {if (i == 0) return Default.name; return content [i - 1].name;}
	T* operator() (string tofind) {
		for (unsigned i = 0; i < content.size(); i++) 
			if (content [i].test(tofind)) 
				return (content[i].thing); 
		return Default.thing;
	}
	string operator() (T* tofind) {
		for (unsigned i = 0; i < content.size(); i++) 
			if (content [i].test(tofind)) 
				return (content [i].name); 
		return Default.name;
	}
	void push_back (T* hold, string assoc) {
		IntEl pass; 
		pass.thing = hold; 
		pass.name = assoc; 
		content.push_back (pass);
	}
};