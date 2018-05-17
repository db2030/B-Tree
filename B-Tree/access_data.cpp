#include <iostream>
using namespace std;
#include <iomanip>
#include "access_data.h"

Access_Data::Access_Data()
{ 
	dataptr = new structure; 
	binarysearch = new BS;	  
}

Access_Data::~Access_Data()	{}


int Access_Data::rtn_data_width()
{
	int sum = 0;
	for (int i = 0 ; i < NUM_OF_FIELD ; i++) sum += MAX_REC_LNG[i];
	return sum;
}


string Access_Data::rtn_key(int field	/*field position*/)
{
	structure * temp = rtn_data();
	return temp -> data[field];
}


int Access_Data::number_of_data()
{
	ifstream count_data;
	count_data.open(DATA, ios::binary | ios::in);

	count_data.seekg(0,ios::end);					// move the pointer to the last position of file
	int total = count_data.tellg();

	return total / rtn_data_width();				// Total bytes / length of one record = # of records
}


bool Access_Data::empty()
{
	ofstream data;
	data.open(DATA, ios::in);

	data.seekp (0, ios::end);					// move the pointer to the end
	int length = data.tellp();					// read the position of pointer.
	data.seekp (0, ios::beg);

	if (length <= 0) return true;				// Return true, if nothing found
	else return false;							// Otherwise return false.
}


void Access_Data::to_struct(	string field, 	// Field data
									 	int count	  	// Target position
															)
{
	if (count > NUM_OF_FIELD)	{
		cout << "Struct is out of size !!" << endl;		
		return;
	}

	field.resize(MAX_REC_LNG[count], ' ');			// Fill empty spaces into each field
	dataptr -> structure_datrtn(count) = field;	// Put modified field into data structure.
	
}


string Access_Data::title(	int num	// The position of the field
												)
{
	string temp;
	switch (num) {
		case 0	:	temp = "Ship's Name : "; break;
		case 1	:	temp = "Type        : "; break;
		case 2	:	temp = "Year Built  : "; break;
		case 3	:	temp = "Year Sunk   : "; break;
		case 4	:	temp = "Cause       : "; break;
		case 5	:	temp = "Owner       : "; break;
		case 6	:	temp = "Captain     : "; break; 
		case 7	:	temp = "Length      : "; break;
		case 8	:	temp = "Beam        : "; break;
		case 9	:	temp = "Tonage      : "; break;
		case 10	:	temp = "Engine      : "; break;
		case 11	:	temp = "County      : "; break;
		case 12	:	temp = "Latitude    : "; break;
		case 13	:	temp = "Longitude   : "; break;
		case 14	:	temp = "RRN         : "; break;
	}
	temp.resize(14, ' ');
	return temp;
}


void Access_Data::single_Display(	int rrn	// RRN
															)
{
	string temp1;
	cout << "=========================================\n";
	cout << title(14) << setfill('0') << setw(MAX_DIGIT) 
		  << rrn << endl;
	for (int i = 0 ; i < NUM_OF_FIELD ; i++)	{				// Display each field line by line with its title
			temp1 = dataptr -> data[i];
			temp1.resize(MAX_REC_LNG[i]);
			cout << title(i) << temp1 << endl;
	}
	cout << "=========================================\n\n";
}


void Access_Data::reddata(	int pos, // RRN
									int w		// Length of record
																			)
{
	ifstream read_data;
	read_data.open(DATA, ios::binary | ios::in);

	read_data.seekg(pos * w * sizeof(char), ios::beg);		// Calculate the position of coresponding RRN

	for (int i = 0 ; i < NUM_OF_FIELD ; i++)	{

		char temp[MAX_REC_LNG[i]];
		read_data.read(reinterpret_cast<char*>(&temp), MAX_REC_LNG[i] * sizeof(char));
		temp[MAX_REC_LNG[i]] = '\0';
		dataptr -> structure_datrtn(i) = temp;
	}
	read_data.close();
}




#include <fstream>
void Access_Data::wrtdata(	int line, 	// RRN
								  	int width	// Length of One Record
													)
{
	ofstream write_data;
	if (empty()) write_data.open(DATA, ios::out);	// If the file is empty, creat new one
	else write_data.open(DATA, ios::in);				// Otherwise, open file w/o distory it

	char * temp2 = new char [width];		// Storage for one record.
	string temp = "";							// Storage for appending each field
	int size = rtn_data_width();								// the length of appended field

	for (int i = 0 ; i < NUM_OF_FIELD ; i++)	{
		temp += dataptr -> data[i];
	}

	temp.resize(size);						// Resize the length of appended record
	strcpy(temp2, temp.c_str());			// Dump record into char
	temp2[width+1] = '\0';					// Put null char at the end of record storage

	write_data.seekp(line * width * sizeof(char) , ios::beg);
	int pos = write_data.tellp();
	write_data.write(temp2, strlen(temp2) * sizeof(char));
	write_data.close();
}








void Access_Data::delete_data(int rrn)
{
	ofstream del_data;
	del_data.open(DATA, ios::out | ios::in);

	del_data.seekp(rrn * rtn_data_width() * sizeof(char), ios::beg);
	del_data << "@" << setfill('0') << setw(MAX_DIGIT) 
		 << binarysearch -> Indexptr -> 
			 itoa( binarysearch -> Indexptr -> rtn_avail_list() );  // change integer to string.

	del_data.close();
}
























