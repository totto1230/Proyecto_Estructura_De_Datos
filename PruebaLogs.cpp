#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

void logging(){
	ofstream file;
	file.open("TEST.txt",ios::out);
	
	if(file.fail()){
		cout<<"ERROR WHILE LOGGING"<< endl;	
		exit(1);
	}
//	string test= system("date";)
	file<<""<< endl;
	file<<"TEST"<< endl;
	file<<"TEST"<< endl;
	file.close();
}


int main (){
	logging();
	system("pause");
	
}
