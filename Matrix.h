#include "chain.h"
#include "MatrixElement.h"

class Matrix{
	MatrixElement** matrix;
	int carbono1X, carbono1Y;
	CChain chain;
	public:
		Matrix(CChain ch): chain(ch){}
		void CreateMatrix();
		void SetMatrix();
		int matrixHeigth, matrixWidth;
};

void Matrix::CreateMatrix(){
	int maxUpHeigth = 0;
	int maxDownHeigth = 0;
	int chainPrincipHeigth = 1;
	
	//midiendo la cadena orgánica
	for(Carbono* CH : chain.mainChain){
		
		if(CH->SubbranchType.find("up") != std::string::npos && CH->Branch_Heigth > maxUpHeigth){
			maxUpHeigth = CH->Branch_Heigth;
		}
		else if(CH->SubbranchType.find("up") == std::string::npos && CH->Branch_Heigth > maxDownHeigth){
			maxDownHeigth = CH->Branch_Heigth;
		}
	}
std::cout << maxUpHeigth << " " << maxDownHeigth << std::endl;//............................
	
	int leftOutstanding, rightOutstanding;
	leftOutstanding = (chain.mainChain[0]->SubbranchType.find("-+") != std::string::npos) ?  1 : 0;	
	rightOutstanding = (chain.mainChain[ chain.mainChain.size()-1 ]->SubbranchType.find("-+") != std::string::npos) ? 1 : 0;
	
	this->matrixWidth = (chain.mainChain.size() + leftOutstanding + rightOutstanding)*2 - 1;
	this->matrixHeigth = (maxUpHeigth + maxDownHeigth + chainPrincipHeigth)*2 - 1;
	
	
	this->matrix = new MatrixElement*[matrixWidth];
	for(int i = 0; i < matrixWidth; i++)
		this->matrix[i] = new MatrixElement[matrixHeigth];
	
	this->carbono1X = (leftOutstanding == 0) ? 0 : 2;
	this->carbono1Y = (maxUpHeigth + chainPrincipHeigth)*2 - 2;
	
	
	//.....................................
	std::cout << "matrix[" << matrixHeigth << "][" << matrixWidth << "]\n\n";
	for(int i = 0; i < matrixHeigth; i ++){
		for(int j = 0; j < matrixWidth; j++){
			std::cout << "#" << " ";
		}
		std::cout << std::endl;
	}
}

void Matrix::SetMatrix(){
	
	for(int i = 0; i < chain.mainChain.size(); i++){
	//	printf("i");
		for(int j = (-1); j < chain.mainChain[i]->Branch_Heigth; j++){
		//	printf("j");
			if(chain.mainChain[i]->SubbranchType.find("up") == std::string::npos)// si la rama no está arriba
			{
				this->matrix[carbono1Y + 2*j+2][carbono1X + 2*i] = MatrixElement("C");
				if(j != chain.mainChain[i]->Branch_Heigth-1) this->matrix[carbono1Y + 2*j+3][carbono1X + 2*i] = MatrixElement("E");
			}
			else{
				this->matrix[carbono1Y - 2*j-2][carbono1X + 2*i] = MatrixElement("C");
				if(j != chain.mainChain[i]->Branch_Heigth-1) this->matrix[carbono1Y - 2*j-3][carbono1X + 2*i] = MatrixElement("E");
			}
	//		printf("p");
		}
		if(chain.mainChain[i]->Branch_Heigth == 0){
			this->matrix[carbono1Y][carbono1X + 2*i] = MatrixElement("C");
//			printf("0");
		}
		
	//	printf("a");
		if(i != chain.mainChain.size() - 1)
			this->matrix[carbono1Y][carbono1X + 2*i+1] = MatrixElement("E");
	}
	printf(" end");
	std::cout << "\n-----------x--------------\n";
	std::cout << "y "<<carbono1Y << "  x " << carbono1X << "\n";
	
	for(int i = 0; i < this->matrixHeigth; i++){
		for(int j = 0; j < this->matrixWidth; j++){
			std::cout << this->matrix[i][j].type << " ";
			if(this->matrix[i][j].type == ""){
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
/*	for(int i = 0; i < this->matrixHeigth; i ++){
		for(int j = 0; j < this->matrixWidth; j++){
			if(this->matrix[i][j].type == "C")
				std::cout << "C" << " ";
			else if(this->matrix[i][j].type == "E")
				std::cout << "-" << " ";
			else
				std::cout << " " << " ";
		//	std::cout << "#" << " ";
		}
		std::cout << std::endl;
	}*/
}
