#include "main.h"
#include "Restaurant.cpp"
#include <fstream>
#include <ctime>
#include <chrono>

int MAXSIZE;

void simulate(string filename, imp_res* r)
{
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
			// cout << MAXSIZE << endl;
    	}
        else if(str == "RED") // RED <NAME> <ENERGY>
        {
            ss >> name;
            ss >> energy;
            r->RED(name, stoi(energy));
    	}
    	else if(str == "BLUE") // BLUE <NUM>
    	{
                ss >> num;
    			r->BLUE(stoi(num));
		}
    	else if(str == "PURPLE") // PURPLE
    	{
    			r->PURPLE();
		}
		else if(str == "REVERSAL") // REVERSAL
		{
    			r->REVERSAL();	
		}
    	else if(str == "UNLIMITED_VOID") // UNLIMITED_VOID
     	{   	
    			r->UNLIMITED_VOID();
    	}
    	else if(str == "DOMAIN_EXPANSION") // DOMAIN_EXPANSION
    	{
    			r->DOMAIN_EXPANSION();
    	}
    	else // LIGHT <NUM>
    	{
                ss >> num;
    			r->LIGHT(stoi(num));
    	}
    }
	// r->print_list(1); cout << endl;
	// r->print_queue();
	// r->print_cusOrder();
}

int main(int argc, char* argv[]) {
	//if (argc < 2)
    //	return 1;
	//  string fileName = argv[1];

	clock_t start = clock();
	for(int i = 9; i <= 9; i ++) {
		cout << endl << "\tTEST CASE " << i << endl;
		imp_res* r = new imp_res();
		string fileName = "";
		fileName += "input1/test" + to_string(i) +".txt";
		// fileName += "input2/input" + to_string(i) + ".txt";
		// fileName = "test.txt";
    	simulate(fileName, r);
  		delete r;
	}
	clock_t end = clock();
	double duration = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Program run time " << duration << " secs" << endl;
	// cout << u8"đây là tiếng việt\n";
	return 0;
}

