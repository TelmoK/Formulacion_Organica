#include "chain.h"
#include "MatrixElement.h"

class Matrix{
	MatrixElement** matrix;
	int carbono1X, carbono1Y;
	CChain chain;
	int matrixHeigth, matrixWidth;
	
	public:
		Matrix(CChain ch): chain(ch){}
		Matrix(){}
		void CreateMatrix();
		void SetMatrix();
		std::vector<MatrixElement*> allCarbonos;
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
	
	int leftOutstanding, rightOutstanding;
	leftOutstanding = (chain.mainChain[0]->SubbranchType.find("-+") != std::string::npos) ?  1 : 0;
	rightOutstanding = (chain.mainChain[ chain.mainChain.size()-1 ]->SubbranchType.find("+") != std::string::npos) ? 1 : 0;
	
	this->matrixWidth = (chain.mainChain.size() + leftOutstanding + rightOutstanding)*2 - 1;
	this->matrixHeigth = (maxUpHeigth + maxDownHeigth + chainPrincipHeigth)*2 - 1;
	
	
	this->matrix = new MatrixElement*[matrixHeigth];
	for(int i = 0; i < matrixHeigth; i++)
		this->matrix[i] = new MatrixElement[matrixWidth];
	
	this->carbono1X = (leftOutstanding == 0) ? 0 : 2;
	this->carbono1Y = (maxUpHeigth + chainPrincipHeigth)*2 - 2;
	
	
	//.....................................
/*	std::cout << "matrix[" << matrixHeigth << "][" << matrixWidth << "]\n\n";
	std::cout << "y "<<carbono1Y << "  x " << carbono1X << "\n\n";
	for(int i = 0; i < matrixHeigth; i ++){
		for(int j = 0; j < matrixWidth; j++){
			std::cout << "#" << " ";
		}
		std::cout << std::endl;
	}*/
}

void Matrix::SetMatrix(){

	for(int i = 0; i < chain.mainChain.size(); i++){
	
		for(int j = (-1); j < chain.mainChain[i]->Branch_Heigth; j++){//crear ramificaciones
		
			if(chain.mainChain[i]->SubbranchType.find("up") == std::string::npos)//si la rama está arriba
			{
				this->matrix[carbono1Y + 2*j+2][(carbono1X + (2*i))].setMatrixElement("C");
				
				if(j != chain.mainChain[i]->Branch_Heigth-1) this->matrix[carbono1Y + 2*j+3][carbono1X + 2*i].setMatrixElement("E");
			}
			else{
				this->matrix[carbono1Y - 2*j-2][carbono1X + 2*i].setMatrixElement("C");
				if(j != chain.mainChain[i]->Branch_Heigth-1) this->matrix[carbono1Y - 2*j-3][carbono1X + 2*i].setMatrixElement("E");
			}
		}
		
		if(chain.mainChain[i]->Branch_Heigth == 0)
		{
			this->matrix[carbono1Y][carbono1X+ 2*i].setMatrixElement("C");
		}
		else{// Subrramas
		
			if(chain.mainChain[i]->SubbranchType == "-+"){
				
				this->matrix[carbono1Y + chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i + 1].setMatrixElement("E");
				this->matrix[carbono1Y + chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i + 2].setMatrixElement("C");
				
				this->matrix[carbono1Y + chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i - 1].setMatrixElement("E");
				this->matrix[carbono1Y + chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i - 2].setMatrixElement("C");
			}
			else if(chain.mainChain[i]->SubbranchType == "-+up"){
			
				this->matrix[carbono1Y - chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i + 1].setMatrixElement("E");
				this->matrix[carbono1Y - chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i + 2].setMatrixElement("C");
				
				this->matrix[carbono1Y - chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i - 1].setMatrixElement("E");
				this->matrix[carbono1Y - chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i - 2].setMatrixElement("C");
			}
			else if(chain.mainChain[i]->SubbranchType == "+"){
			
				this->matrix[carbono1Y + chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i + 1].setMatrixElement("E");
				this->matrix[carbono1Y + chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i + 2].setMatrixElement("C");
			}
			else if(chain.mainChain[i]->SubbranchType == "+up"){
				
				this->matrix[carbono1Y - chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i + 1].setMatrixElement("E");
				this->matrix[carbono1Y - chain.mainChain[i]->Subbranch_Position*2 ][ carbono1X + 2*i + 2].setMatrixElement("C");
			}
		}
		
		if(i != chain.mainChain.size() - 1){//enlaces de la cadena principal
			this->matrix[carbono1Y][carbono1X + 2*i + 1].setMatrixElement("E");
		}

	}


	for(int i = 0; i < this->matrixHeigth; i ++){
		for(int j = 0; j < this->matrixWidth; j++){
			if(this->matrix[i][j].type == "C")
				std::cout << "C" << " ";
			else if(this->matrix[i][j].type == "E")
				std::cout << "-" << " ";
			else
				std::cout << " " << " ";
		}
		std::cout << std::endl;
	}
	//enlazando los hidrocarburos
	for(int i = 0; i < this->matrixHeigth; i ++){
		for(int j = 0; j < this->matrixWidth; j++){
			
			if(this->matrix[i][j].type == "C")
			{
				if(j < (matrixWidth-1))
					if(this->matrix[ i ][j+1].type == "E") this->matrix[i][j].vecinos.push_back(&this->matrix[ i ][j+2]);
				
				if(j > 1)
					if(this->matrix[ i ][j-1].type == "E") this->matrix[i][j].vecinos.push_back(&this->matrix[ i ][j-2]);
				
				if(i > 1)
					if(this->matrix[i-1][ j ].type == "E") this->matrix[i][j].vecinos.push_back(&this->matrix[i-2][ j ]);
					
				if(i < (matrixHeigth-1))
					if(this->matrix[i+1][j].type == "E") this->matrix[i][j].vecinos.push_back(&this->matrix[i+2][ j ]);
				
				allCarbonos.push_back(&this->matrix[i][j]);
			}
		}
	}
}
