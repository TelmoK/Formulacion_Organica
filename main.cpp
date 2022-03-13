#include <iostream>
#include <vector>
#include "Matrix.h"

int main(){
	try{
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
	}
	catch(...){
		std::cout << "\nAlgo ha ido mal";
	}
	/*std::cout << std::endl;
	for(Carbono *c: ch.chain){
		std::cout << "Tipo de radical " << c->radical<<std::endl;
		std::cout << "Numero de carbonos " << c->nCarbonosRama<<std::endl;
		std::cout << "--------------\n";
	}*/
}
