#include "libs/agendaitem.h"
#include <list>

using namespace std;

char getyn(){
	string answer;
	getline(cin, answer);
	return answer[0];
}

bool stringtoint(string input, int &output){
	bool number = false;
	for(int i = 0; i<input.size();i++){
		if(!isdigit(input[i]))
			return false;
		if(isdigit(input[i]))
			number = true;
	}
	if(number)
		output = stoi(input);
	return number;
}

void alteritem(list<agendaitem>* agendaitems, int index){
	list<agendaitem>::iterator it = agendaitems->begin();
	advance(it, index-1);
	cout<<"Type the number of the data you want to alter. Type exit to exit.\n";
	cout<<"1.title: " << it->returntitle() << endl;
	cout<<"2.begindate: " << it->returnbegindate() << endl;
	cout<<"3.enddate: " << it->returnenddate() << endl;
	cout<<"4.description: " << it->returndescription() << endl;
	cout<<"5.location:  " << it->returnlocation() << endl;

	string input = "";
	int number = 0;

startlabel:
	
	getline(cin, input);
	if(input == "exit")
		return;
	
	while(!stringtoint(input, number)){
		cout<<"Input is not an integer.\n";
		cout<<"Type the number of the data you want to alter. Type exit to exit.\n";
		getline(cin, input);
		if(input == "exit")
			return;

	}
	if(number>5||number<1){
		cout<<"Wrong number\n";
		goto startlabel;
	}

	switch(number){
		case 1:
			it->settitle();
			break;
		case 2:
			it->setbegindate();
			break;
		case 3:
			it->setenddate();
			break;
		case 4:
			it->setdescription();
			break;
		case 5:
			it->setlocation();
			break;
		default:
			cout<<"I do not know how but the number is wrong. Please try again!\n";
			goto startlabel;
	}

}

//manage the current items in the list
void manageitems(list<agendaitem>* agendaitems, int itemsadded){
	cout<<"you currently have "<<itemsadded<<" events added. \n";
	int itemn = 1;
	//show all added items to the user by title and number added.
	for(list<agendaitem>::iterator it= agendaitems->begin(); it != agendaitems->end(); it++){
		cout<<itemn<<". "<<it->returntitle()<<endl;
		itemn++;
	}

	string input;
	int number = 0;

startlabel2:
	cout<<"Type the number of the event you want to alter. Type exit to exit.\n";
	
	getline(cin, input);
	if(input == "exit")
		return;
	
	while(!stringtoint(input, number)){
		cout<<"Input is not an integer.\n";
		cout<<"Type the number of the event you want to alter. Type exit to exit.\n";
		cin.ignore();
		getline(cin, input);
		if(input == "exit")
			return;
	}
	if(number>itemsadded||number<itemsadded){
		cout<<"Wrong number\n";
		goto startlabel2;
	}
	cout<<"alteritem\n";
	alteritem(agendaitems, number);

}

void menu(ofstream* file){
	int itemsadded = 0;
	bool ready = false;
	list<agendaitem> agendaitems;
beginlabel:
	while(true){
		cout<<"you currently have "<<itemsadded<<" events added. \n Do you want to add an event? (y/n)\n";
		//if user is done adding items break from the while loop (we use tolower to also allow user to use a Y instead of y.)
		if( tolower(getyn()) != 'y' ){
			break;
		}
		
		agendaitem newitem;

		//fill the item
		newitem.fillitem();

		//add the item to the list
		itemsadded++;
		agendaitems.emplace_back(newitem);

		//allow user to manage the events
		cout<<"Do you want to manage the events? (delete or change events)\n";
		if( tolower(getyn()) == 'y' ){
			manageitems(&agendaitems, itemsadded);
		}

	}

	cout<<"Are you sure you do not want to add anymore items?(y/n)\n";

	//loop back to menu if user wants to continue
	if(tolower(getyn()) == 'n')
		//I know goto's are kinda a nono but they are just too convenient.
		goto beginlabel;

	//allow user to manage the items before making the final ical file.
	cout<<"Do you want to manage the events?(y/n) (delete or change events)\n";
	if( tolower(getyn()) == 'y' ){
		manageitems(&agendaitems, itemsadded);
	}

	cout<<"Your items will now be turned into an ical file please stand by.\n";
	//iterate over all items and add them to the file
	for(list<agendaitem>::iterator it=agendaitems.begin(); it != agendaitems.end(); it++){
		it->addtofile(file);
	}
	
}

int main ( ){
	
	string filename;
	bool klaar = false;
	time_t rawtime;
	tm* localtm;
	
	cout<<"------------------------------------"<<endl
		<<"  Welcome to my ical file creator."<<endl
		<<"  Created by: Thomas Coret 2019"<<endl
		<<"------------------------------------"<<endl
		<<"please enter the filename below (no spaces and no extension)"<<endl;
	
	
	getline(std::cin, filename);

	filename.append(".ics");
	
	ofstream file(filename.c_str());
	
	//Standard file start
	file<<"BEGIN:VCALENDAR\r\n"
		<<"VERSION:2.0\r\n"
		<<"PRODID:Thomassawesomeicalcreator\r\n";

	menu(&file);
	
	file<<"END:VCALENDAR";	
	file.close();

	return 0;
}
