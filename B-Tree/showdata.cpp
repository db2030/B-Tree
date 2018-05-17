#include "access_data.h"

int Access_Data::get_buffer(ifstream& data)
{
	data.seekg(0, ios::end);	
	int size = data.tellg();
	data.seekg(0, ios::beg);	

	char * buffer = new char[size];
	data.read((char*)buffer,size);
	buffer[size] = '\0';

	inter_buffer.clear();
	inter_buffer = buffer;

	return size;
}




bool Access_Data::tagsearch(string tag1, string tag2, int& start, int& end)
{
	size_t found = start;

	found = inter_buffer.find(tag1, found);
	if (found != string::npos)	start = found;
	else return false;

	found = inter_buffer.find(tag2, found);
	if (found != string::npos)	end = found + tag2.size();
	else return false;

	return true;
}



int Access_Data::howmanytag(string tag1, string tag2, int start, int end)
{
	int orgend = end, count = 0;

	while (true)	{
		bool found = tagsearch(tag1, tag2, start, end);
		if (found && end <= orgend) {	
			count++;	
			start = end;		
			end = orgend;		
		} else break;
	}
	
	return	count;
}






/*******************************************************************************************************
*							void showdata::Display(int &)
********************************************************************************************************
*	Veriable		: temp1, temp2	- temporary string storage to packing data
*
*	Input		: RRN number
*	Description 	: Packing entire fields into one string with delimiter, then print out
*	Output		: Entire useful data, line per record with RRN number.
*******************************************************************************************************/
#include <iomanip>
bool Access_Data::oneline_Display(int RRN)
{
	string temp1, temp2;
	int g = 0;

	for (int i = 0 ; i < NUM_OF_FIELD ; i++)	{
		temp1 = dataptr -> data[i];

		temp1.resize(MAX_PTR_LNG[i]);
		temp2 = temp2 + temp1 + "|";
	}
	cout << setw(MAX_DIGIT) << setfill('0') << RRN << "|" << temp2 << endl;

	return true;
}





/*******************************************************************************************************
*						bool showdata::html_narrow_srch (int&, int&, int)
********************************************************************************************************
*	Veriable		: start	- start position, integer
*				  end	- end position, integer address
*
*	Input		: start, end position, and selection
*	Description 	: searching for each tags correspoding choice. 1 - <table>, 2 - <TR>, 3 - <TD>
*				  Then, check they are available
*	Output		: Return true, if operation is successed.
*******************************************************************************************************/
bool Access_Data::html_narrow_srch (int& a, int& b, int choice)
{
	int start = a, end = b;

	switch (choice)	{

		case 1	:	if (!tagsearch(TBS, TBE, start, end))	return false;
					a = start;		
					b = end;	
					break;

		case 2	:	if (!tagsearch(TRS, TRE, start, end))	return false;

		case 3	:	if (howmanytag(TDS, TDE, start, end) == NUM_OF_FIELD)		{

						a = start + strlen((char*)TDS);	
						b = end - strlen((char*)TDE);

				} else {	a = end;	return false;	}
	}

	return true;
}




/*******************************************************************************************************
*						string showdata::html_grab_data(int , int )
********************************************************************************************************
*	Veriable		: temp	- temporary storage for each field, string
*				  b		- end position storage, integer
*				  pos	- position of first open tag, size_t
*				  pos1	- position of first close tag, size_t
*
*	Input		: start, end position
*	Description 	: searching open and close tags, dump them into temp string if the gap between 
*				  tags and they are printable.  Remove any unprintable character and specail HTML tags
*				  from temp string
*	Output		: data fo field.
*******************************************************************************************************/
string Access_Data::html_grab_data(int start, int end)
{
	string temp = "";
	int b = end;

	while (true)	{

		if ( start >= b || !tagsearch(">", "<", start, b) )		break;

		if ( b - start > 0 )	{
			for (int  i = start + 1 ; i < b - 1 ; i++)
				if (	isprint(inter_buffer[i]) && !ispunct(inter_buffer[i])) temp += inter_buffer[i];
		}
		start = b;
		b = end;
	}

	while (true)	{
		size_t pos = temp.find("&");
		size_t pos1 = temp.find(";", pos) - pos + 1;
		if (pos != string::npos && pos1 != string::npos)	temp.replace(pos, pos1, " ");	
		else break;
	}

	return temp;
}




