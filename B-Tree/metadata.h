/**************************************************************************************************
*	Auther 			:	Dae A Kim
*	Data   			:  Nov. 13. 2008
*	Version			:	3.5
*	Project ID		:	LAB Assignment 3
*	CmpE Class		:	CmpE 130
*	Program 			
*	Language			:	C++
*	OS/Hardware 		
*	dependencies	:	None
***************************************************************************************************
*	Problem 	 		:	Using five files - load, show, list, add, and delete - creat two text files
*	Description			- datafile and indexfile - and do random data access using avail_list.
**************************************************************************************************/
#ifndef METADATA_H
#define METADATA_H

#define DATA "datafile.txt"
#define INDEX "indexfile.txt"

#define MAX_DIGIT 3 						/* Maximum number of digit of number of capable data
											      ex) 3 digit -> max is 999, 4 digit -> max is 9999 */
#define NUM_OF_FIELD 14					// Required number of field
#define SKIP_TR 1							// Number of table nedd to be skipped
#define KEY 0								// Position of Primary Key

#define TBS "<table"						// HTML tags
#define  TBE "</table>"
#define TRS "<tr"	
#define  TRE "</tr>"
#define TDS "<td"		
#define  TDE "</td>"
												// The length of each field for recording data
static const int MAX_REC_LNG[NUM_OF_FIELD] = {20, 20,  4,  4, 10,  7,  7, 10,  8,  5,  6, 15, 13, 14};
												// The length of each field for displaying data
static const int MAX_PTR_LNG[NUM_OF_FIELD] = {20, 10,  4,  4,  5,  5,  5,  3,  2,  4,  5,  9,  3,  3};

#endif
