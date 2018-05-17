#include <iostream>
#include <iomanip>
using namespace std;

#include "BS.h"
 

BS::BS()
{
	Indexptr = new Access_Index;
}





BS::~BS()
{
	delete Indexptr;
}





bool BS::search ( string val, // Primary Key
						int& pos, 	// Corresponding position (will be returned)
						int msg		// message flag
										)
{
	val.resize(20, ' ');
	if (msg) cout << "searching...";
	bool result = B_search (0, Indexptr -> rtn_inmax(), val, pos, msg);
	if (msg) cout << endl;
	return result;
}




bool BS::B_search (	int beg, 	// start position
							int end, 	// end position
							string val, // Primary Key
							int& pos, 	// Returned position
							int msg		// message flag
											)
{

	if (Indexptr -> rtn_inmax() == 0 ) {	// if the indexfile is empty, return false.
		return false;
	}
	
	pos = (beg + end) / 2;						// calculate the middle

	if (beg > end || Indexptr -> rtn_inmax() <= pos) {
		pos = beg;									// if the middle is out of range, stop to search
		return false;
	}

	if (msg) cout << pos << " ";				// show the movement

	if (Indexptr -> index_pkey(pos) == val)	{ 
		cout << "\nData \"" << val << "\" is in Database!!" << endl;
		return true;

	} else if (Indexptr -> index_pkey(pos) > val)	{	// if the value is smaller than indexdata,

		return B_search (beg, pos-1, val, pos, msg);		// searching for left boundry

	} else if (Indexptr -> index_pkey(pos) < val)	{	// if the value is bigger than indexdata,

		return B_search (pos + 1, end, val, pos, msg);	// searching for right boundry

	}
}




bool BS::string_emptychecker(string temp)
{
	int count = 0;
	while (true)
	{
		if (count >= temp.size()) break;
		if ( !isspace( temp[count] ) ) break;
		count++;
	}
	if (count == temp.size()) return true;
	else return false;
}


