#include <iostream>
using namespace std;

#define MESSAGE 0				//message OFF
#include "access_data.h"
#include "showdata.cpp"

int main()
{
	ifstream ifile;
	ifstream dfile;
	ifile.open(INDEX, ios::binary | ios::in);
	dfile.open(DATA, ios::binary | ios::in);

	if ( ifile.is_open() && dfile.is_open() )	{
		Access_Data * list = new Access_Data;
		list -> binarysearch -> Indexptr -> get_info();						// get metadata
		int max_size = list-> binarysearch -> Indexptr -> rtn_inmax(); // get number of indexdata

		if (max_size == 0)	{
			cout << "Nothing to display !!" << endl;
			return 0;
		}

		for (int i = 0 ; i < max_size ; i++)	{

			list -> reddata(	list-> binarysearch -> Indexptr -> index_rrn(i), 
									list-> binarysearch -> Indexptr -> rtn_wid()		);	//read data from datafile

			list -> oneline_Display(list-> binarysearch -> Indexptr -> index_rrn(i));  // displaying line by line
		}
		ifile.close();
		dfile.close();
	} else {
		cout << "No \"" << INDEX << "\" or \"" << DATA << "\" Exist..." << endl;
		cout << "Try load first.  ex) load testfile.htm" << endl;
	}
	return 0;
}
