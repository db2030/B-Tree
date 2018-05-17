#include <iostream>
using namespace std;

#include "access_data.h"
#include "get_input.h"

#define MESSAGE 1																					//message ON
#define G_I_MSG1 "Enter Any Ship Name You Want to Input As A Parameter !!"		// ERROR msg1 (get_input.h)
#define G_I_MSG2 "ex) add Alviso"															// ERROR msg2 (get_input.h)

void input_to_struct(Access_Data*, string);

int main(int argc, char* argv[])
{
	system("clear");
	string PKey = get_input(argc, argv, G_I_MSG1, G_I_MSG2);		//modify input (get_input.h)
	if (PKey == "NOINPUT") return 0;

	ifstream ifile;
	ifstream dfile;
	ifile.open(INDEX, ios::binary | ios::in);
	dfile.open(DATA, ios::binary | ios::in);

	if ( ifile.is_open() && dfile.is_open() )	{
		Access_Data * add = new Access_Data;
		add -> binarysearch -> Indexptr -> get_info();		// get metadata

		int pos = 0;

		if (!(add -> binarysearch -> search(PKey, pos, MESSAGE)))	{	// if the Primary key is not exised,

			int rrn = add -> binarysearch -> Indexptr -> rtn_avail_list();		// look up avail_list
			if (rrn == -1) rrn = add -> number_of_data();;							/* if no avail_list available,
																										get recent RRN					*/

			input_to_struct(add, PKey);													// get rest of data from user

			add -> binarysearch -> Indexptr 															// metadata update
				 -> meta_update( add -> binarysearch -> Indexptr -> rtn_inmax() + 1, 	// recent RRN + 1
					    			  add -> binarysearch -> Indexptr -> avail_check(rrn) );

			add -> binarysearch -> Indexptr -> add_index(PKey, pos, rrn, MESSAGE);		// add Primary Key and RRN to INDEX
			add -> wrtdata(rrn, add -> binarysearch -> Indexptr -> rtn_wid());			// Write Data on file

			add -> single_Display( rrn );																// Display it on on one line

		} else cout << "The Shipname \"" << PKey << "\" is already existed !!" << endl;
		ifile.close();
		dfile.close();
	} else {
		cout << "No \"" << INDEX << "\" or \"" << DATA << "\" Exist..." << endl;
		cout << "Try load first.  ex) load testfile.htm" << endl;
	}
	return 0;
}


// Put user input into data structure.
void input_to_struct( Access_Data * data, // Data access pointer
							 string pkey			// Primary key
														)
{
	string temp = pkey;
	temp.resize(MAX_REC_LNG[0], ' ');		// fix the length of RRN and put into structure
	data -> to_struct(temp, 0);

	for ( int i = 1 ; i < NUM_OF_FIELD ; i++)	{  

		cout << data -> title(i);				// Ask user input for rest of data
		getline(cin, temp);
		temp.resize(MAX_REC_LNG[i], ' ');	// fix the size with empty spaces
		data -> to_struct(temp, i);			// put it into data structure

	}
}





