#ifndef BS_H
#define BS_H

#include <fstream>
#include <string>
using namespace std;

#include "access_index.h"

class BS
{
	public:
		Access_Index * Indexptr;	// pointer to access the index operations

		BS();
		~BS();

/******************************************************************************************************/
		bool search (string , int&, int);	
/*******************************************************************************************************
*	Input				: Primary key, return position, message flag
*	Description 	: Triger of recursive B_search function
*	Output			: true - when Primary key is found.  Otherwise, false
*******************************************************************************************************/




/******************************************************************************************************/
		bool B_search (int ,int ,string , int&, int);
/*******************************************************************************************************
*	Input				: Start and end position, Primary key, return position, message flag
*	Description 	: Binary search for the indexfile
*	Output			: true - when Primary key is found.  Otherwise, false
*******************************************************************************************************/




/******************************************************************************************************/
		bool string_emptychecker(string);
/*******************************************************************************************************
*	Input				: Primary Key
*	Description 	: Check the Key is full of empty space or not.
*	Output			: true, if it is empty. otherwise false
*******************************************************************************************************/




};	

#endif
