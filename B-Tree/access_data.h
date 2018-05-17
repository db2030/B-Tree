#ifndef ACCESS_DATA_H
#define ACCESS_DATA_H

#include "metadata.h"
#include "BS.h"

class Access_Data
{
	private:

		struct structure
		{
			string * data;						/* Dynamic allocated string
													for generic propose	   */		
			structure()						{	data = new string[NUM_OF_FIELD];}
			~structure()								{	delete data;			}
			string & structure_datrtn(int num)	{	return data[num];		}
		};

		typedef structure * datptr;
		
		datptr dataptr;						// Pointer to the structure
		string inter_buffer;					// Buffer for data.

	public:
		BS * binarysearch;					// Pointer to the Binary Search Tree Class (BS.cpp)

		Access_Data();
		~Access_Data();

		// IO functions for datafile (access_data.cpp)

		structure * rtn_data()				// Return the structure poiter
		{	return dataptr;			}		


/******************************************************************************************************/
												int rtn_data_width();
/*******************************************************************************************************
*	Input				: N/A
*	Description 	: Sumataion whole of the length of each field
*	Output			: The length of one records
*******************************************************************************************************/


/******************************************************************************************************/
												string rtn_key(int);
/*******************************************************************************************************
*	Input				: Position of Field
*	Description 	: Returns corrsponding field data
*	Output			: field data
*******************************************************************************************************/


/******************************************************************************************************/
												int number_of_data();
/*******************************************************************************************************
*	Input				: N/A
*	Description 	: Returns the number of data stored in the DATA file
*	Output			: # of data
*******************************************************************************************************/


/******************************************************************************************************/
												bool empty();
/*******************************************************************************************************
*	Input				: N/A
*	Description 	: check the file is empty
*	Output			: true if any data found. otherwise return false
*******************************************************************************************************/


/******************************************************************************************************/
											void to_struct(string, int);
/*******************************************************************************************************
*	Input				: Filed data and column number
*	Description 	: Put the actual data into correspond field in structure.
*						  Resize them with blank space.
*	Output			: N/A
*******************************************************************************************************/


/******************************************************************************************************/
											string title(int num);
/*******************************************************************************************************
*	Input				: Position of field
*	Description 	: Returns the Title of corresponding field.
*	Output			: the Title of the Field
*******************************************************************************************************/


/******************************************************************************************************/
											void single_Display(int);
/*******************************************************************************************************
*	Input				: RRN
*	Description 	: Display a single data of the RRN
*	Output			: One record in multiple lines
*******************************************************************************************************/


/******************************************************************************************************/
											void reddata(int, int);
/*******************************************************************************************************
*	Input				: RRN, the Length of one record
*	Description 	: Read a record into structure.
*	Output			: N/A
*******************************************************************************************************/


/******************************************************************************************************/
											void wrtdata(int, int);	
/*******************************************************************************************************
*	Input				: RRN, length of the record, flag for new file
*	Description 	: Packing one record into a temp, and write it on textfile in RAW mode
*						  If the file is not existed, make new file and write it.
*	Output			: N/A
*******************************************************************************************************/


/******************************************************************************************************/
											void delete_data(int);
/*******************************************************************************************************
*	Input				: RRN
*	Description 	: Mark the first 4 bytes of data as deleted (replaced by availlist with '@' sign)
*	Output			: N/A
*******************************************************************************************************/


		//searching & data abstract (from LAB2, showdata.cpp)
		bool oneline_Display(int);
		int get_buffer(ifstream&);
		bool tagsearch(string, string, int&, int&);
		int howmanytag(string, string, int, int);
		bool html_narrow_srch (int&, int&, int);
		string html_grab_data (int a, int b);
};


#endif
