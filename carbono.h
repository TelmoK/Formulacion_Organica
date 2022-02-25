#include <vector>

class Carbono{
	public:
		std::vector<Carbono*> ramas;
		int nCarbonosRama;
		enum Radicales {non, iso, sec, terc, neo};
		Radicales radical;
};
