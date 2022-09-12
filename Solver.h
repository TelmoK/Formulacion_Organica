#include "Matrix.h"
#include <algorithm>

class Solver{
	Matrix matrix;
	std::vector<MatrixElement*> numExtremos;
	
	public:
		Solver(Matrix);
		std::string Solve();
};

Solver::Solver(Matrix mtx){
	matrix = mtx;
	for(MatrixElement* e : matrix.allCarbonos){
		if(e->vecinos.size() == 1)
			this->numExtremos.push_back(e);
	}
}

std::string Solver::Solve(){
	int y = 0;
	std::vector< std::vector<MatrixElement*> > recorridos;
	
	for(MatrixElement* extremoActual : numExtremos){
		
		std::vector<MatrixElement*> recorridoActual;
		std::vector<MatrixElement*> checkedCarbonos;
		
		recorridoActual.push_back(extremoActual);
		checkedCarbonos.push_back(extremoActual);
		MatrixElement* carbonoActual = extremoActual;
		
		while(checkedCarbonos.size() != this->matrix.allCarbonos.size()){
				
			bool quedanConexiones = false;
			for(MatrixElement* carbono : carbonoActual->vecinos){
				
				if(std::find(checkedCarbonos.begin(), checkedCarbonos.end(), carbono) == checkedCarbonos.end()){//si carbono no esta en checked
					recorridoActual.push_back(carbono);
					checkedCarbonos.push_back(carbono);
					carbonoActual = carbono; 
					
					quedanConexiones = true;
				}
			}
	/*		bool quedanConexiones = false;
			for(MatrixElement* carbono : carbonoActual->vecinos){
				
				if(std::find(checkedCarbonos.begin(), checkedCarbonos.end(), carbono) == checkedCarbonos.end()){//si carbono no esta en checked
					recorridoActual.push_back(carbono);
					checkedCarbonos.push_back(carbono);
					carbonoActual = carbono;
					
					quedanConexiones = true;
				}
			}
			
			if(quedanConexiones == false){
				
				recorridos.push_back(recorridoActual);
				
				//mientras no haya vecinos libres
				bool vecinosLibres = false;
				while(vecinosLibres == false){
				
					carbonoActual = recorridoActual[ recorridoActual.size()-2 ];
					recorridoActual.pop_back();
					for(MatrixElement* e : carbonoActual->vecinos)
						if(std::find(checkedCarbonos.begin(), checkedCarbonos.end(), e) == checkedCarbonos.end())
							vecinosLibres = true;
				}	
			}*/
		}
		
		int i = 0;
		for(std::vector<MatrixElement*> rec : recorridos){
			for(MatrixElement* e : rec){
				std::cout << e << std::endl;
			}
			std::cout << i << "--------------\n";
			i++;
		}
		std::cout << "-----------------------------"<<y<<"\n";
		y++;
	}
	return "";
}
