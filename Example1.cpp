#include <iostream>
#include <vector>
#include <conio.h>

#include "Solver.h"


int main(){

		CChain ch;
		
		ch.CreateChain();
		ch.OrderChain();
		Matrix mtx(ch);
		mtx.CreateMatrix();
		mtx.SetMatrix();
		
		std::cout << "\n_____________________________\n";
		
		char c = getch();
		if(c == '.')
			system("CLS");
	main();
}
