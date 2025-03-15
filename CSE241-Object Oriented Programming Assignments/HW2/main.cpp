#include "myShell.h"
#include <stdexcept>
#include <iostream>
using std::cout;
using std::endl;

int main(){
	//A shell object is created and shell started.
	try{
 		myOS::myShell shell1;
		shell1.startShell();
		//Delete the allocated memory
	}
	catch(std::runtime_error& e){
		cout << "Exception throwned: " << e.what() << endl;
	}
	catch(...){
		cout << "Exception throwned." << endl;
	}
	
	
	return 0;
}