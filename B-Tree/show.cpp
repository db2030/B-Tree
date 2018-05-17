#include <iostream>
using namespace std;

#include "access_data.h"
#include "get_input.h"

#define MESSAGE 1																// message ON
#define G_I_MSG1 "Enter the Primary Key as A Parameter !!"		// Error msg 1 (get_input.h)
#define G_I_MSG2 "ex) show Alviso"										// Error msg 2 (get_input.h)

int main(int argc, char* argv[])
{
	system("clear");
	string PKey = get_input(argc, argv, G_I_MSG1, G_I_MSG2);					//modify input (get_input.h)
	if (PKey == "NOINPUT") return 0;

	ifstream ifile;
	ifstream dfile;
	ifile.open(INDEX, ios::binary | ios::in);
	dfile.open(DATA, ios::binary | ios::in);

	if ( ifile.is_open() && dfile.is_open() )	{
		Access_Data * show = new Access_Data;
		show -> binarysearch -> Indexptr -> get_info();							// get metadata

		if (show -> binarysearch -> Indexptr -> rtn_inmax() == 0) {			// If the datafile is empty...
				cout << "\nData file is Empty...\n" << endl;
				return 0;
		}

		int pos;
		if (show -> binarysearch -> search(PKey, pos, MESSAGE))	{			// if the data found,

			int rrn = show -> binarysearch -> Indexptr -> index_rrn(pos);	// get RRN of corresponding position
			show -> reddata(rrn, show -> rtn_data_width());						// read data
			show -> single_Display(rrn);												// Diaplay with multiple lines

		} else cout << PKey << " is out of list !!" << endl;

		ifile.close();
		dfile.close();

	} else {																					// Show error if there is no datafiles

		cout << "No \"" << INDEX << "\" or \"" << DATA << "\" Exist..." << endl;
		cout << "Try load first.  ex) load testfile.htm" << endl;

	}
	return 0;
}
