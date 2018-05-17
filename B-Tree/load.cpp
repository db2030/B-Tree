#include <iostream>
using namespace std;

#include "access_data.h"
#include "showdata.cpp"

#define MESSAGE 0				// message OFF

/******************************************************************************************************/
							void parsing (int , int , int, Access_Data*);
/*******************************************************************************************************
*	Veriable		: initial_end		- position of end of file (= file size), integer
*				  	  RRN					- RRN trakcer, integer
*				     is_this_quilified - check the range is valid for grab data
*				     initial_tr_end 	- position of </tr>, integer
*				     tr					- number of <tr> and </tr> pairs in specific range.
*				     initial_td_end	- position of </td>, integer
*
*	Input			: start, and end position, current rrn, showdata object pointer, and 
*	Description : Narrow down the range of data by following the hierarchy sequence of HTML tags.
*					  If the range is valid for data, grab them and put them into structure.
*					  Resize each fileds with empty spaces, write them on the screen.  Then, write them
*				 	  into textfile in RAW mode.
*	Output		: Entire parsed data, 100 character per line.
*******************************************************************************************************/


int main (int argc, char* argv[])
{
	system("clear");

	ifstream input;
	input.open(argv[1]);

	if (input.is_open())	{

		Access_Data * parser = new Access_Data;
		int rrn = 0;

		if (!(parser -> binarysearch -> Indexptr -> empty())){	// check the indexfile is empty
			rrn = parser -> number_of_data();							// track the current RRN
		}

		parsing (0, parser -> get_buffer(input), rrn, parser);

	}	else	{

		cout << "\nNeed to have input file" << endl;
		cout << "ex) load test1.htm\n" << endl;

	}
	input.close();

	return 0;
}




void parsing (	int start, 			// start position
					int end, 			// end position
					int RRN, 			// current RRN
					Access_Data * a   // Data access operation pointer.
											)
{
	int initial_end = end;

		bool is_this_quilified;
		int tb = a -> howmanytag(TBS, TBE, start, end);				

			for (int i = 0 ; i < tb ; i++)
			{	
				is_this_quilified = a -> html_narrow_srch(start, end, 1);	

				if (is_this_quilified)	{

					int initial_tr_end = end;
					int tr = a -> howmanytag(TRS, TRE, start, end);		

					for (int k = 0 ; k < tr ; k++)	{

						is_this_quilified = a -> html_narrow_srch(start, end, 2);	

						if (is_this_quilified && k >= SKIP_TR )	{

							for (int j = 0 ; j < NUM_OF_FIELD ; j++)	{
							int initial_td_end = end;

							a -> tagsearch(TDS, TDE, start, end);
							a -> to_struct(a -> html_grab_data(start, end), j);
													
							start = end;
							end = initial_td_end;
							}
	
							int availlist = a -> binarysearch -> Indexptr -> rtn_avail_list();  // got recent info.
							int width = a -> rtn_data_width();
							int pos = 0;

							if (!(a -> binarysearch -> Indexptr -> empty())) {		// if the indexfile is not empty,
								a -> binarysearch -> Indexptr -> get_info();			// updata metadata
							}

							/* Only if the Primary key is not empty, and no duplicate key found, 
								do the following operation															*/
							if ( !(a -> binarysearch -> string_emptychecker(a -> rtn_key(KEY))) &&
								  !(a -> binarysearch -> search(a -> rtn_key(KEY), pos, MESSAGE))   )	{	
								
								a -> oneline_Display(RRN);																// Display record
								a -> wrtdata(RRN, a -> rtn_data_width());											// Write on datafile

								a -> binarysearch -> Indexptr -> add_index(	a -> rtn_key(KEY),			// Write on indexfile
																							pos, 
																							RRN, 
																							MESSAGE					
																														);

								a -> binarysearch -> Indexptr 
								  -> meta_update(	a -> binarysearch -> Indexptr -> rtn_inmax() + 1, 		// update metadata
														availlist														);  
								RRN++;
							}

						}	else	end = initial_tr_end;

					}

				}
				end = initial_end;				
			}
}







