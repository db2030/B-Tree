#include <iostream>
using namespace std;

#include "access_data.h"
#include "get_input.h"

#define MESSAGE 1																					//message ON
#define G_I_MSG1 "Enter Any Ship Name You Want to Delete As A Parameter !!"	// ERROR msg1 (get_input.h)
#define G_I_MSG2 "ex) add Alviso"															// ERROR msg2 (get_input.h)

int main(int argc, char* argv[])
{
	system("clear");
	string PKey = get_input(argc, argv, G_I_MSG1, G_I_MSG2);							//modify input (get_input.h)
	if (PKey == "NOINPUT") return 0;

	ifstream ifile;
	ifstream dfile;
	ifile.open(INDEX, ios::binary | ios::in);
	dfile.open(DATA, ios::binary | ios::in);

	if ( ifile.is_open() && dfile.is_open() )	{
	
		cout << "Are You Sure to Delete \"" 
			  << PKey << "\" From Database ? (Y / N) :";				// Ask user to delete data.
		string temp;
		getline(cin, temp);
		if (!(temp == "y" || temp == "Y")) return 0;


		Access_Data * del = new Access_Data;
		del -> binarysearch -> Indexptr -> get_info();				// get metadata

		int pos = 0;

		if (del -> binarysearch -> search(PKey, pos, MESSAGE) )	{				// if the data exists,

			int delpos = del -> binarysearch -> Indexptr -> index_rrn(pos);	// get RRN of corresponding Primary key

			del -> delete_data(delpos);													/* Making '@' mark with avail_list at
																										the first 4 charactors				  */
			del -> binarysearch -> Indexptr -> delete_index(pos, MESSAGE);		// delete indexfile

			int line = del -> binarysearch -> Indexptr -> rtn_inmax() - 1;		// number of indexfile = current - 1
			del -> binarysearch -> Indexptr -> meta_update(line, delpos);		// update metadata

			cout << "\nData \"" << PKey << "\" is Removed From Data Base." << endl;

		} else cout << "The Shipname \"" << PKey << "\" is not in data !!" << endl;
		
		ifile.close();
		dfile.close();

	} else {
		cout << "No \"" << INDEX << "\" or \"" << DATA << "\" Exist..." << endl;
		cout << "Try load first.  ex) load testfile.htm" << endl;
	}
	return 0;
}



