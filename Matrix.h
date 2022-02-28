#include "chain.h"
#include "MatrixElement.h"

class Matrix{
	MatrixElement* matrix;
	int carbono1X, carbono1Y;
	CChain chain;
	public:
		Matrix();
		void CreateMatrix();
		void SetMatrix();
};

Matrix::Matrix(){
	int maxUpHeigth, maxDownHeigth;
	int chainPrincipHeigth = 1;
	
	for(Carbono* CH : chain->mainChain){
		
		if(CH->SubbranchType.find("up") != std::string::npos && CH->Branch_Heigth > maxUpHeigth){
			maxUpHeigth = CH->Branch_Heigth;
		}
		else if(CH->SubbranchType.find("up") == std::string::npos && CH->Branch_Heigth > maxDownHeigth){
			maxDownHeigth = CH->Branch_Heigth;
		}
	}

	
	int leftOutstanding, rightOutstanding;
	leftOutstanding = (chain->mainChain[0]->SubbranchType.find("-+") != std::string::npos) ?  1 : 0;	
	rightOutstanding = (chain->mainChain[ chain->mainChain.size()-1 ]->SubbranchType.find("-+") != std::string::npos) ? 1 : 0;
	
	int matrixWidth = (chain->mainChain.size() + leftOutstanding + rightOutstanding)*2 - 1;
	int matrixHeigth = (maxUpHeigth + maxDownHeigth + chainPrincipHeigth)*2 - 1;
	
	
	this->matrix = new MatrixElement[matrixWidth][matrixHeigth];
	this->carbono1X = leftOutstanding + 1;
	this->carbono1Y = (maxUpHeigth + chainPrincipHeigth)*2 - 2;
	
//	std::cout << "matrix[" << matrixWidth << "][" << matrixHeigth << "]\n\n";
}

void Matrix::SetMatrix(){
	
}
