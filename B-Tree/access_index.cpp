#include <iostream>
using namespace std;

#include <fstream>
#include <iomanip>

#include "access_index.h"

Access_Index::Access_Index()
:width(0), index_max(0), avail(-1)
{
	for (int i = 0 ; i < NUM_OF_FIELD ; i++) width += MAX_REC_LNG[i];		// calculate the length of one record
}



bool Access_Index::empty()
{
	ofstream lookup_index;
	lookup_index.open(INDEX, ios::binary | ios::in);

	lookup_index.seekp (0, ios::end);		// move the pointer to the end
	int length = lookup_index.tellp();				// read the position of pointer.
	lookup_index.seekp (0, ios::beg);

	lookup_index.close();

	if (length <= 0) return true;				// Return true, if nothing found
	else return false;							// Otherwise return false.
}


bool Access_Index::get_info()
{
	ifstream lookup_meta;
	lookup_meta.open(INDEX, ios::binary | ios::in);

	if (lookup_meta.is_open())	{
		char TEMP[3][MAX_DIGIT + 1];
		lookup_meta.seekg(0, ios::beg);

		for (int i = 0 ; i < 3 ; i++)	{
			lookup_meta.width(sizeof(char) * MAX_DIGIT + 1);
			lookup_meta >> TEMP[i];
			TEMP[i][MAX_DIGIT] = '\0';
		}

		width = atoi(TEMP[0]);
		index_max = atoi(TEMP[1]);

		if (TEMP[2][MAX_DIGIT - 2] == '-') avail= -1; 
		else avail = atoi(TEMP[2]);
	
		lookup_meta.close();
		return true;
	} else return false;
}


void Access_Index::index_initialize(	int w, 		// RRN
													int max, 	// # of indexdata
													int ava		// Avail_list
																	)
{
	ofstream initial_index;
	initial_index.open(INDEX, ios::binary | ios::in);

	initial_index.seekp(0, ios::beg);
	initial_index << setfill('0') << setw(MAX_DIGIT) << itoa(w) 
					  << setfill('0') << setw(MAX_DIGIT) << itoa(max) 
					  << setfill('0') << setw(MAX_DIGIT) << itoa(ava) << endl;
	initial_index.close();
}


int Access_Index::index_rrn(	int num	/* position of index */ )
{
	ifstream lookup_rrn;
	lookup_rrn.open(INDEX, ios::binary | ios::in);

	char rrn[MAX_DIGIT];
	
	lookup_rrn.seekg(0, ios::beg);
	lookup_rrn.seekg((MAX_DIGIT * 3 + 1) + MAX_REC_LNG[KEY] + (MAX_REC_LNG[KEY] + MAX_DIGIT + 1) * num);
	lookup_rrn.read(rrn,  MAX_DIGIT * sizeof(char));

	rrn[MAX_DIGIT] = '\0';
	lookup_rrn.close();
	return atoi(rrn);
}


string Access_Index::index_pkey( int num	/* position of index */ )
{	
	ifstream lookup_PKey;
	lookup_PKey.open(INDEX, ios::binary | ios::in);
	char temp[MAX_REC_LNG[KEY]];
	lookup_PKey.seekg(0, ios::beg);
	lookup_PKey.seekg((MAX_DIGIT * 3 + 1) + (MAX_REC_LNG[KEY] + MAX_DIGIT + 1)  * num);
	lookup_PKey.read(temp, MAX_REC_LNG[KEY] * sizeof(char));
	lookup_PKey.close();
	temp[MAX_REC_LNG[KEY]] = '\0';
	return temp;
}


int Access_Index::avail_check( int line /* RRN */ )
{
	ifstream lookup_avail;
	lookup_avail.open(DATA, ios::binary | ios::in);

	lookup_avail.seekg(width * line * sizeof(char), ios::beg);

	string temp;
	lookup_avail.width(MAX_DIGIT + 1);
	lookup_avail >> temp;
	lookup_avail.close();

	if ( (temp[0] == '@') && (temp.find("-1") == string::npos) ) {

		temp.replace(temp.begin(),temp.begin() + 1," ");
		const char *chartemp = temp.c_str();
		line = atoi(chartemp);

	} else return -1;

	return line;
}


void Access_Index::meta_update( int max_rrn,  // # of indexdata
										  int avail_val // recent Avail_list
															 )
{
	ofstream write_meta;
	write_meta.open(INDEX, ios::binary | ios::in);
	write_meta.seekp(MAX_DIGIT, ios::beg);
	write_meta.width(MAX_DIGIT * 2);

	write_meta << setfill('0') << setw(MAX_DIGIT) << itoa(max_rrn) 
				  << setfill('0') << setw(MAX_DIGIT) << itoa(avail_val);

	write_meta.close();	
}




string Access_Index::index_store_old( int beg, // Begin position
												  int end  // End position
															 )
{
	string temp;
	if (beg == -1) beg = 0;							  // If the begin position is 1, read the entire data.
	else beg = (MAX_DIGIT * 3 + 1) + (MAX_REC_LNG[KEY] + MAX_DIGIT + 1) * beg;
	end = (MAX_DIGIT * 3 + 1) + (MAX_REC_LNG[KEY] + MAX_DIGIT + 1) * end;

	ifstream read_index;
	read_index.open(INDEX, ios::binary | ios::in);
	read_index.seekg(beg, ios::beg);

	char olddata[end - beg];
	read_index.read(olddata, end - beg);
	temp = olddata;
	temp.resize(end - beg);

	read_index.close();
	return temp;
}




void Access_Index::add_index( string pkey, // Primary Key
										int pos,		 // Position of data in indexfile
										int rrn, 	 // Corresponing RRN
										int msg		 // flag for displaying message
															)
{
	string temp;

	if (pos < rtn_inmax())	
		temp = index_store_old( pos, rtn_inmax() );	// Store the old data into buffer

	ofstream write_index;
	if (empty()) write_index.open(INDEX, ios::out | ios::app);	// If the file is empty, creat new one
	else write_index.open(INDEX, ios::in);								// Otherwise, open file w/o distory it

	if (empty())	index_initialize(width,0,-1);		// If it is new file, initialize indexfile

	write_index.seekp( (MAX_DIGIT * 3 + 1) +								// metadata offset 
						 	(MAX_REC_LNG[KEY] + MAX_DIGIT + 1) * pos, 	// data line offset
							ios::beg												);

	pkey.resize(MAX_REC_LNG[0], ' ');
	string RRN = itoa(rrn);
	write_index << pkey 
					<< setfill('0') << setw(MAX_DIGIT) << RRN << endl;	// write indexdata

	if (msg)	{
		if (pos < rtn_inmax())	{
			cout << "Index Line Number " << pos
				<< " to " << rtn_inmax()
				<< " Are Pushed Down." << endl;
		} else {
			cout << "Index Line Number " << pos
			<< " is Pushed Down." << endl;
		}
	}

	write_index.seekp( (MAX_DIGIT * 3 + 1) + 									/* Searching for the postion of
																								nextline of the new data */
							(MAX_REC_LNG[KEY] + MAX_DIGIT + 1) * (pos + 1), 
							ios::beg														);
	write_index << temp << endl;

	write_index.close();
}


void Access_Index::delete_index( int line, 	// indexdata position
											int msg		// flag for displaying message
														)
{
	
	string temp = index_store_old(-1, rtn_inmax());				// dump whole indexfile into string buffer
	temp.erase(	(MAX_DIGIT * 3 + 1) + 								/* Searching for the target position
																					and erase that line					*/
					(MAX_REC_LNG[KEY] + MAX_DIGIT + 1) * line , 
				  	(MAX_REC_LNG[KEY] + MAX_DIGIT + 1)				);

	if (msg)	{
		if (line + 1 < rtn_inmax())	{
			cout << "Index Line Number " 
				  << line + 2 << " to " << rtn_inmax()
				  << " Are Pushed Up." << endl;
		} else {
			cout << "Index Line Number " 
				  << line + 1 << " is Removed." << endl;
		}
	}
	ofstream del_index;													// Rewrite modified indexdata on file
	del_index.open(INDEX, ios::trunc | ios::out);
	del_index.width((MAX_REC_LNG[KEY] + MAX_DIGIT + 1) * (rtn_inmax() - 1));
	del_index << temp << endl;
	del_index.close();
	
}



string Access_Index::itoa(int integer)
{

	int digit = 0;
	char temp;
	bool minus = false;
	string result;
	
	if (integer < 0) {
		integer = integer * -1;
		minus = true;
	}

	for (;;)
	{
		digit = integer % 10;
		temp = digit + '0';
		integer = integer / 10;		
			
		result.insert(result.begin(),temp);
		if (integer < 1) break;
	}
	result.resize(result.size());
	if (minus) result.insert(result.begin(),'-');
	return result;
}







