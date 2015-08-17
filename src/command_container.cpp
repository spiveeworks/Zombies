#include <string>
#include <vector>

namespace ComCon
	{

//returns the first token, after erasing it from the original std::string
std::string gettoken (std::string& input, std::string const& delim) {
	unsigned const Dwidth = delim.length ();
	
	//get token bit
	unsigned key_end = input.find (delim, 0);
	std::string retval = input.substr(0, key_end);
	
	//increase key_end to swallow delimiters
	while (input.substr (key_end, Dwidth) == delim) 
		key_end += Dwidth;
	input.erase (0, key_end);
	return retval;
}

//////////////
//  Classes //
//////////////

struct command_key {
public:
	std::string keyword;
	unsigned (*script) (std::string);
	
	command_key (std::string keyword_c, unsigned (*script_c)(std::string)) {
		keyword = keyword_c;
		script = script_c;
	} 
	
	unsigned check_using (std::string const& input, std::string const& delim) const;
	inline unsigned operator() (std::string args) const {return (*script)(args);}//just passes the args through to the script
};

struct command: public command_key {
public:
	std::string delim_d;
	inline unsigned check_for (std::string const& input) const {return check_using(input, delim_d);} //note that it is still possible to use the explicit version. freedom!
//constructors + destructors
	command (std::string keyword_c, unsigned (*script_c)(std::string), std::string delimiter): command_key(keyword_c, script_c) {delim_d=delimiter;}
	command (command_key base, std::string delimiter): command_key(base) {delim_d = delimiter;}
};

struct context {
public:
	std::vector<command> comm;
	unsigned (*script_d)(std::string);
	
	unsigned operator() (std::string const& input) const;
	unsigned operator() (std::string const& input, std::string const& delim_o) const;
};

////////////////////////
//  Member functions  //
////////////////////////


unsigned command_key::check_using (std::string const& input, std::string const& delim) const {
	unsigned const Dwidth = delim.length();
	unsigned const key_end = keyword.length();
		//compiler should recognise that these constants are just for readability, right?
	
	if (input.length() < key_end)
		return 0;
	if (input.substr (0,key_end) != keyword) 
		return 0;
	//delimiters only need to be stripped if there are any more characters to strip
	if (input.length() == key_end)
		return key_end;
	unsigned int i = key_end; 
	while (input.substr (i, Dwidth) == delim) 
		i += Dwidth;  
	//if there are non-delimiter characters after the keyword, then the keyword isn't actually there: "hear this" != "hearth is"
	if (i == key_end) 
		return 0;
	return i;
}

unsigned context::operator() (std::string const& input) const {
	for (unsigned i = 0; i < comm.size(); i++)
	{
		unsigned j = comm[i].check_for(input);
		if (j != 0)
			return comm[i](input.substr(j));
	}
	return (*script_d)(input);
}

unsigned context::operator() (std::string const& input, std::string const& delim_o) const {
	std::string args = input;
	std::string key = gettoken(args, delim_o);
	for (unsigned i = 0; i < comm.size(); i++)
	{
		unsigned j = comm[i].check_using(key, delim_o);
		if (j != 0)
			return comm[i](args);
	}
	return (*script_d)(input);
}

/*
// context stack
class contextstack {//not yet at all tested
	context** stack;
	unsigned length;
public:
	//void (*onunderflow)(unsigned, contextstack*); //removed because instead I'll pass the overpop back to the caller// void funcname (unsigned amount_under_by, context* failer = this)
	void push (context& level);
	signed pop (unsigned n);
	void operator() (std::string input/*, std::string delim*///);
	/*
};
void contextstack::push (context& level) {
	context** next = new context* [length + 1];
	copy (length, stack, next);
	next [++length] = &level;
	delete[] stack;
	stack = next;
}

signed contextstack::pop (unsigned n) {
	signed retval;
	retval = length - n;
	if (retval >= 0) 
	{
		length = 0;
		delete[] stack;
		stack = 0;
		return n;
	}
	else
	{
		length -= n;
		context** prev = new context* [length];
		copy (length, stack, prev);
		delete[] stack;
		stack = prev;
		return length;
	}
}

void contextstack::operator() (std::string input/*, std::string delim*//*) {
	pop (
		(*stack[length-1]) (input)
	);
}

*/

	}
