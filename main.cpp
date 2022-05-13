#include <iostream>
#include <vector>
//#include "Matrix.h"
#include "Solver.h"


int main(){

		CChain ch;
		
		ch.CreateChain();
		std::cout << "-------------------------\n\n";
		ch.OrderChain();
		for(Carbono* c : ch.mainChain){
			t(c);
		}
		std::cout << "-----------------------------\n\n";
		Matrix mtx(ch);
		mtx.CreateMatrix();
		mtx.SetMatrix();
	
		Solver slv(mtx);
		slv.Solve();
	/*	
		int numCh = 0;
		for(MatrixElement* e : mtx.allCarbonos){
			std::cout << "["<< (numCh+1) <<"] " << e << " sons: ";
			for(MatrixElement* v: e->vecinos)
				std::cout << v << " ";
			std::cout << std::endl;
			numCh++;
		}
		std::cout << "\nNumber of CHs: " << numCh << "\n";*/
		std::cout << "dfghjk";
}
