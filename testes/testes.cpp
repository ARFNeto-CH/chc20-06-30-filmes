#include <algorithm>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
using namespace std;

struct Numerador
{
	int atual;
	Numerador() { atual = -1; } // construtor padrao
	explicit Numerador(int N) : atual(N - 1) {}; // novo inicio
	int operator()() { return ++atual; };
};

Numerador num(1); // inicio da contagem na saida

int main(int argc, char** argv)
{	int N = 5000;
	string saida = "filmes.txt";
	if (argc > 1) N = atoi(argv[1]);
	if (argc > 2) saida = argv[2];
	vector<int> base(N);
	generate(base.begin(), base.end(), num);
	random_shuffle(base.begin(), base.end());
	vector<string> lista;
	transform(
		base.begin(), base.end(), inserter(lista, lista.begin()),
		[](int N)
		{	stringstream s;
			s << "Filme " << setfill('0') << setw(4) << N;
			return s.str();
		}
	);
	ofstream os{ saida }; // o arquivo a criar
	ostream_iterator<string> iter{ os, "\n" };
	std::copy(lista.begin(), lista.end(), iter);
	return 0;
};
// fim
