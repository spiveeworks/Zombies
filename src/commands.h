#include <iostream>
#include <string>
#include <sstream>
#include "command_container.cpp"
using namespace std;
using namespace ComCon;


unsigned C_exit (string arb) {
	return 1;
}

unsigned C_spawn (string name) {
/*
	ItemType typen = type.find(name);
	if (typen == 0) 
		cout << "Please enter a valid item type\r\n";
	else
	{
		LocId place = hand.spawnel (typen);
		cout << "Spawned a(n) " << name << " at location " << place << "!\r\n";
	}
*/
	return 0;
}

unsigned C_delete (string name) {
/*
	LocId X;
	if (stringstream (name) >> X)
	{
		if (hand.deleteel (X))
			cout << "Deleted item! :D";
		else
			cout << "Error deleting item " << name << ".\r\n";
	}
	else
	{
		cout << "Please enter a valid number\r\n";
	}
*/
	return 0;
}

unsigned C_identify (string id) {
	/*cout << "Item is of type: ";
	switch (getItemType ()) {
		case ECO_ITEM_axe:
			cout << "axe";
		break;
		case ECO_ITEM_bat:
			cout << "bat";
		break;
	}*/
	/* 
	LocId X;
	if (stringstream (id) >> X)
		if (hand [X] != 0)
			cout << "The item is a(n) " << type.getname(hand [X]->getid ());
		else
			cout << "No item here.";
	else
		cout << "Please enter a valid number";
	cout << "\r\n";
	*/
	return 0;
}

unsigned C_open (string target) {
/* 
	entity* toOpen = IntEnt(target);
	switch (getmod_OS (*toOpen) -> open())
	{
	case invalid:
		cout << "Impossible!";
	break;
	case success:
		cout << "It opens!";
	break;
	case nodouble:
		cout << "You fail to open what is already open.";
	break;
	case isprotected:
		cout << "Locked :(";
	break;
	default:
		cout << "An unknown error occured.";
	}
	cout << "\r\n";
 */
	return 0;
}

//unsigned C_

/*
unsigned C_list (string arb) {
		cout << "Existing players: " << "\r\n";
		cout << all.listnames (string ("\r\n") ) << "\r\n";
		return 0;
}

unsigned C_remplayer (string name) {
	byte test = all.findplayer(name);
	if (test == all.size ()) {
		cout << "No player of name \"" << name << "\"\r\n";//No player of name "Spivee" [CRLF]
		return 0;
	}
	delete all.member (test);
	all.remove (test);
	return 0;
}

unsigned C_startG (string arb) {
	if (hasstarted)
		cout << "Game has already started" << endl;
	else
		maingame = new game (all);
	return hasstarted = true;
}

unsigned C_tagDup (string playaz) {
	if (!hasstarted)
		cout << "Start a game first" << endl;
	else
	{
		unsigned int token = playaz.find (" ", 0);
		string kappa = playaz.substr (0, token++), target = playaz.substr (token, playaz.length () - token);
		byte k = maingame->findplayer (kappa), t = maingame->findplayer (target), badid = maingame->size ();
		if (k == badid) 
		{
			cout << "Player \"" << kappa << "\" does not appear to be in that game" << endl;
			return 0;
		}
		if (t == badid) 
		{
			cout << "Player \"" << target << "\" does not appear to be in that game" << endl;
			return 0;
		}
		if (maingame->tag (k, t)) 
			cout << kappa << " has been eliminated!\r\n";
		else
			cout << target << " has been eliminated!\r\n";
	}
	return 0;
}

unsigned C_spoilG (string arb) {
	if (!hasstarted)
		cout << "Start a game first" << endl;
	else
	{
		byte i = 0;
		do
		{
			cout << maingame -> member (i) -> name << ",\r\n"; /////////
			i = maingame -> nodeid (i).t;
		}
		while (i != 0);
		debug ();
		return 0;
	}
}
*/
unsigned C_badcommand (string arb) {
	cout << "Please enter a valid command" << endl;
	return 0;
}