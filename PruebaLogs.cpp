#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>

using namespace std;
ofstream file;

char* time_testing() {
	   // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);
   return dt;
}

void logging(){
	//ofstream file;
	file.open("TEST.txt",ios::out);
	char* test= time_testing();
	if(file.fail()){
		cout<<"ERROR WHILE LOGGING"<< endl;	
		exit(1);
	}
//	string test= system("date";)
	//char a= time_testing();
	file<<test<<""<< endl;
	file<<test<<"TEST"<< endl;
	file<<test<<"TEST"<< endl;
	
}

int main (){
	logging();
	char* test= time_testing();
	file<<test<<"ADDED FROM MAIN";
	system("pause");
	file.close();
}
