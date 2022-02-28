#include <ctime>
#include <stdlib.h>
#include <stdio.h>

#include "carbono.h"
void t(Carbono* CH){
	std::cout << CH->Branch_Heigth << " CHs " << CH->SubbranchType << " in "<<CH->Subbranch_Position <<std::endl;
}
class CChain{
	public:
	std::vector<Carbono*> mainChain;
	
	void CreateChain();
	void OrderChain();
//	void CreateMatrix();
};

void CChain::CreateChain(){
	int prov_nonRama = 50;
	int prov_tipoRamaX = (100 - prov_nonRama) / 4;//misma probabilidad entre el reto de tipos de rama (iso, neo, terc, sec)
	
	srand(time(NULL));
	int nunCanrbonos = 4 + rand() % 6;
	
	for(int i = 0; i < nunCanrbonos; i++){//creando un máximo de 10 carbonos y un mínimo de 4
		Carbono* CH = new Carbono();
		
		CH->Branch_Heigth = 3 + rand() % 2;
		
		int subbranch_Heigth = rand() % 100;
		
		if(subbranch_Heigth >= 0 && subbranch_Heigth < prov_nonRama){//sin ramificación
			CH->Branch_Heigth = 0;
			CH->Subbranch_Position = 0;
			CH->SubbranchType = " "; t(CH);
		}
		else if(subbranch_Heigth >= prov_nonRama && subbranch_Heigth < (prov_nonRama + prov_tipoRamaX)){//rama tipo iso
			CH->Subbranch_Position = CH->Branch_Heigth;
			CH->SubbranchType = "-+";t(CH);
		}
		else if(subbranch_Heigth >= (prov_nonRama + prov_tipoRamaX) && subbranch_Heigth < (prov_nonRama + prov_tipoRamaX*2)){//rama tipo sec
			CH->Subbranch_Position = 1;
			CH->SubbranchType = "+";t(CH);
		}
		else if(subbranch_Heigth >= (prov_nonRama + prov_tipoRamaX*2) && subbranch_Heigth < (prov_nonRama + prov_tipoRamaX*3)){//rama terc
			CH->Subbranch_Position = 1;
			CH->SubbranchType = "-+";t(CH);
		}
		else if(subbranch_Heigth >= (prov_nonRama + prov_tipoRamaX*3) && subbranch_Heigth < (prov_nonRama + prov_tipoRamaX*4)){//rama neo
			CH->Subbranch_Position = CH->Branch_Heigth - 1;
			CH->SubbranchType = "-+";t(CH);
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
			
			//colisión con anteanterior rama
			if(this->mainChain[i]->SubbranchType == "-+" && (this->mainChain[i-2]->SubbranchType == "+" || this->mainChain[i-2]->SubbranchType == "-+")
					&& (this->mainChain[i]->Subbranch_Position == this->mainChain[i-2]->Subbranch_Position)){
					//	std::cout << "porque anteanterior colisiona (1)\n";
				this->mainChain[i]->SubbranchType += "up";
			}
			
			//colisión con anterior rama
			if ((this->mainChain[i-1]->SubbranchType == "+" || this->mainChain[i-1]->SubbranchType == "-+")
					&& (this->mainChain[i-1]->Subbranch_Position <= this->mainChain[i]->Branch_Heigth || this->mainChain[i]->SubbranchType == "-+")){
					//	std::cout<<"porque anterior colisiona (2)\n";
				this->mainChain[i]->SubbranchType += "up";
			}
			
			//eliminar en caso de colisión por arriba o abajo de la cadena principal
			if((this->mainChain[i-1]->SubbranchType == "+up" || this->mainChain[i-1]->SubbranchType == "-+up")
					&& (this->mainChain[i-1]->Subbranch_Position <= this->mainChain[i]->Branch_Heigth && this->mainChain[i]->SubbranchType == "-+up")){
					//	std::cout << "porque anteanterior y el anterior colisiona (3)\n";
				this->mainChain[i]->SubbranchType = " ";
				this->mainChain[i]->Branch_Heigth = 0;
				this->mainChain[i]->Subbranch_Position = 0;
			}
		}
		
	}
}
/*
void CChain::CreateMatrix(){
	int maxUpHeigth, maxDownHeigth;
	int chainPrincipHeigth = 1;
	
	for(Carbono* CH : this->mainChain){
		
		if(CH->SubbranchType.find("up") != std::string::npos && CH->Branch_Heigth > maxUpHeigth){
			maxUpHeigth = CH->Branch_Heigth;
		}
		else if(CH->SubbranchType.find("up") == std::string::npos && CH->Branch_Heigth > maxDownHeigth){
			maxDownHeigth = CH->Branch_Heigth;
		}
	}
	
	int matrixHeigth = (maxUpHeigth + maxDownHeigth + chainPrincipHeigth)*2 - 1;
	
	int leftOutstanding, rightOutstanding;
	leftOutstanding = (this->mainChain[0]->SubbranchType.find("-+") != std::string::npos) ?  1 : 0;	
	rightOutstanding = (this->mainChain[ this->mainChain.size()-1 ]->SubbranchType.find("-+") != std::string::npos) ? 1 : 0;
	
	int matrixWidth = (this->mainChain.size() + leftOutstanding + rightOutstanding)*2 - 1;
	
	
	MatrixElement* matrix[matrixWidth][matrixHeigth];
	
	std::cout << "matrix[" << matrixWidth << "][" << matrixHeigth << "]\n\n";
	std::string matrix[matrixWidth][matrixHeigth];
	for(int i = 0; i < matrixHeigth; i++){
		for(int j = 0; j < matrixWidth; j++){
			std::cout << "#";
		}
		std::cout << std::endl;
	}
}*/
