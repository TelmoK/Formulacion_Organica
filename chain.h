#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include "carbono.h"


class CChain{
	public:
	std::vector<Carbono*> chain;
	void CreateChain();
	void ShowChain();
};

void CChain::CreateChain(){
	srand(time(NULL));
	int n = 4 + rand() % 6;
	
	
	for(int i = 0; i < n; i++){//creando un máximo de 10 carbonos
		Carbono* carbono = new Carbono();
		//std::cout << n;
		int radical = rand() % 4;
		int nCarbonos = 4 + rand() % 2;
		
	//	if(i > 0 && chain[(i-2)]->ramas.size() != 0){//decidiendo si el carbono se ramifica
			carbono->nCarbonosRama = nCarbonos;
			
			switch(radical){
				case 0:
					carbono->radical = Carbono::Radicales::non;std::cout << 0;
					carbono->nCarbonosRama = 0;
					break;
				case 1:
					carbono->radical = Carbono::Radicales::iso;std::cout << 1;
					break;
				case 2:
					carbono->radical = Carbono::Radicales::sec;std::cout << 2;
					break;
				case 3:
					carbono->radical = Carbono::Radicales::terc;std::cout << 3;
					break;
				case 4:
					carbono->radical = Carbono::Radicales::neo;std::cout << 4;
					break;
			}
	//	}
		
		chain.push_back(carbono);
	}
	
}

void CChain::ShowChain(){
	int sizeX, sizeY;
	for(int i = 0; i < chain.size(); i++){
		if(i == 0){
		//	this->chain[i]->radi
		}
	}
}
