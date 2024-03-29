#include <ctime>
#include <stdlib.h>
#include <stdio.h>

#include "carbono.h"

class CChain{
	public:
	std::vector<Carbono*> mainChain;
	
	void CreateChain();
	void OrderChain();
};

void CChain::CreateChain(){
	int prov_nonRama = 50;
	int prov_tipoRamaX = (100 - prov_nonRama) / 4;//misma probabilidad entre el reto de tipos de rama (iso, neo, terc, sec)
	
	srand(time(NULL));
	int nunCanrbonos = 4 + rand() % 6;
	
	for(int i = 0; i < nunCanrbonos; i++){//creando un m�ximo de 10 carbonos y un m�nimo de 4
		Carbono* CH = new Carbono();
		
		CH->Branch_Heigth = 3 + rand() % 2;
		
		int subbranch_Heigth = rand() % 100;
		
		if(subbranch_Heigth >= 0 && subbranch_Heigth < prov_nonRama){//sin ramificaci�n
			CH->Branch_Heigth = 0;
			CH->Subbranch_Position = 0;
			CH->SubbranchType = " "; 
		}
		else if(subbranch_Heigth >= prov_nonRama && subbranch_Heigth < (prov_nonRama + prov_tipoRamaX)){//rama tipo iso
			CH->Subbranch_Position = CH->Branch_Heigth;
			CH->SubbranchType = "-+";
		}
		else if(subbranch_Heigth >= (prov_nonRama + prov_tipoRamaX) && subbranch_Heigth < (prov_nonRama + prov_tipoRamaX*2)){//rama tipo sec
			CH->Subbranch_Position = 1;
			CH->SubbranchType = "+";
		}
		else if(subbranch_Heigth >= (prov_nonRama + prov_tipoRamaX*2) && subbranch_Heigth < (prov_nonRama + prov_tipoRamaX*3)){//rama terc
			CH->Subbranch_Position = 1;
			CH->SubbranchType = "-+";
		}
		else if(subbranch_Heigth >= (prov_nonRama + prov_tipoRamaX*3) && subbranch_Heigth < (prov_nonRama + prov_tipoRamaX*4)){//rama neo
			CH->Subbranch_Position = CH->Branch_Heigth - 1;
			CH->SubbranchType = "-+";
		}
		
		this->mainChain.push_back( CH );
	}
	
}

void CChain::OrderChain(){
	for(int i = 0; i < this->mainChain.size(); i++){
		
		if(i == 1 && this->mainChain[i]->SubbranchType != " "){
			
			if ((this->mainChain[0]->SubbranchType == "+" || this->mainChain[0]->SubbranchType == "-+")
					&& (this->mainChain[0]->Subbranch_Position <= this->mainChain[i]->Branch_Heigth || this->mainChain[i]->SubbranchType == "-+")){
			
				this->mainChain[i]->SubbranchType += "up";
			}
		}
		else if(i > 1){
			
			//colisi�n con anteanterior rama
			if(this->mainChain[i]->SubbranchType == "-+" && (this->mainChain[i-2]->SubbranchType == "+" || this->mainChain[i-2]->SubbranchType == "-+")
					&& (this->mainChain[i]->Subbranch_Position == this->mainChain[i-2]->Subbranch_Position)){
				this->mainChain[i]->SubbranchType += "up";
			}
			
			//colisi�n con anterior rama
			if ((this->mainChain[i-1]->SubbranchType == "+" || this->mainChain[i-1]->SubbranchType == "-+")
					&& (this->mainChain[i-1]->Subbranch_Position <= this->mainChain[i]->Branch_Heigth || this->mainChain[i]->SubbranchType == "-+")){
				this->mainChain[i]->SubbranchType += "up";
			}
			
			//eliminar en caso de colisi�n por arriba o abajo de la cadena principal
			if((this->mainChain[i-1]->SubbranchType == "+up" || this->mainChain[i-1]->SubbranchType == "-+up")
					&& (this->mainChain[i-1]->Subbranch_Position <= this->mainChain[i]->Branch_Heigth && this->mainChain[i]->SubbranchType == "-+up")){
				this->mainChain[i]->SubbranchType = " ";
				this->mainChain[i]->Branch_Heigth = 0;
				this->mainChain[i]->Subbranch_Position = 0;
			}
		}
		
	}
}
