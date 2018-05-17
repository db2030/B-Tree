#ifndef GET_INPUT_H
#define GET_INPUT_H

/**************************************************************************************************/
								string get_input(int, char**, string, string);
/***************************************************************************************************
*	This function will modify the argv arguments from C++ to the actual user input
*	Input		:	Argc, Argv, Error Message 1, Erroe Message 2
*	Output	:	Return "NODATA" string with the error messages if NO Input detected, or the size of 
*					input is longer than Primary Key size.  
*					Otherwise, return the modified input from shell command.
***************************************************************************************************/

string get_input(int argc,    	// Number on argument from shell command input
					  char** argv, 	// Actual Data of shell command input from user
					  string MSG1, 	// Error message 1
					  string MSG2  	// Error message 2
					 )
{
	if (argc < 2)	{										// Error 1, when No input detected.
		cout << MSG1 << endl << MSG2 << endl;
		return "NOINPUT";
	}

	string PKey = "";										// Primary Key Storage.

	if (argc > 2)	{										/* If the user input is more than one word
																	append them with empty spaces				*/
		for (int i = 1 ; i < argc ; i++) PKey = PKey + argv[i] + " ";
	} else PKey = argv[1];

	if ( (PKey.size() > MAX_REC_LNG[KEY] && argc == 2) ||		// Warning when size of PKey > size of field
		  (PKey.size() - 1 > MAX_REC_LNG[KEY] && argc >= 3) ) {
			cout << "Invalied Size. The Size of Primary Key Should be Less than or Equal to " 
				  << MAX_REC_LNG[KEY] << " Characters." << endl;
			return "NOINPUT";
	}


	if (argc > 2) PKey.resize(PKey.size() - 1);	// Remove the last empty space.
	else PKey.resize(PKey.size());

	return PKey;
}

#endif
