#include <iostream>
#include <utility>
#include <vector>


using namespace std;

#include "dijkstra.h"

int main(int argc,char** argv)
{
	if(argc < 2)
		cout << "Nombre d'arguments insuffisants" << endl;
	else{
		int s = 0;

		graphe obj(argv[1]);
		cout << "Le graphe est : " << endl;
		obj.donnees();
		cout << endl;
		obj.dijkstra(s);
		obj.resultats(s);
	}

	return(1);
}
