#ifndef AGENDAITEM_H
#define AGENDAITEM_H

#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdlib.h>

class agendaitem{
	//vars
	private:
		std::string begindate;
		std::string enddate;
		std::string title;
		std::string description;
		std::string location;
		bool haslocation;
		bool hasdescription;

	//functions
	public:
		agendaitem( );
		//calls all the set function so the user can provide the information to fill the item.
		void fillitem( );
		//add the current item to the ical file
		void addtofile( std::ofstream* );
		//returns the title of the event
		std::string returntitle();
		//returns the begindate of the event
		std::string returnbegindate();
		//returns the enddate of the event
		std::string returnenddate();
		//returns the description of the event
		std::string returndescription();
		//returns the location of the event
		std::string returnlocation();
		//allows the user to set the begin date of the event
		void setbegindate( );
		//allows the user to set the end date of the event
		void setenddate( );
		//allows the user to set the title of the event
		void settitle( );
		//allows the user to set the description of the event
		void setdescription( );
		//allows the user to set the location of the event
		void setlocation( );

		
	private:
		//removes the spaces from a string
		char* removespaces( char* );
		//creates a DTSTART out of the given date (also works for DTEND) 
		//input = yyyymmdd:hhmm
		std::string getDTSTART( std::string );
		//creates a DTSTAMP out of the current time
		std::string  getDTSTAMP( tm* );
};
#endif