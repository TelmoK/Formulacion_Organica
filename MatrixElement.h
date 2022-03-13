#include <vector>
class MatrixElement{
	public:
		std::string type;// C para carbono y E para enlace
		std::vector<MatrixElement*> vecinos;
		MatrixElement(){}
		MatrixElement(std::string s): type(s){}
};
