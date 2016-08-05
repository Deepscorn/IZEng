#include "dllinc.h"

//STL
#include <fstream>

using namespace std;

void Trace(char* strError) { 
	static fstream LogFile("IZEng.log",ios::out);
	LogFile<<strError<<endl; 
}
