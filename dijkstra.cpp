#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <stack>

using namespace std;

#include "dijkstra.h"

/****************************************/
/* Objectif : Constructeur avec comme argument
le nom du fichier contenant le graphe.
Il doit :
-> ouvrir le fichier filename
-> initialiser, avec son contenu, les attributs "n", "m" et "L",
/****************************************/
graphe::graphe(char* filename){
    ifstream file(filename);

    file >> n;
    file >> m;

    T = new int[n];
    I = new int[n];
    d = new int[n];
    pere = new int[n];

    int i,j,k,l;

    for(i = 0 ; i < n; i++){
        vector<sommetadjacent> vect;
        L.push_back(vect);
    }

    for(i = 0 ; i < m; i++){
        file >> j;
        file >> k;
        file >> l;
        L[j].push_back(make_pair(k,l));
        L[k].push_back(make_pair(j,l));
    }

    file.close();
}


/****************************************/
/* Objectif : Affichage des arêtes et longueurs
/****************************************/
void graphe::donnees(){
	cout << "arête : " << "longueur" << endl;
	for(int i = 0; i < L.size(); i++)
		for(int j = 0; j < L[i].size(); j++)
			if(i < L[i][j].first)
				cout << "(" << i << "," << L[i][j].first << ")" << ": " << L[i][j].second << endl;
}

/****************************************/
/* Objectif : Affichage des valeurs des plus courts
chemins trouvés avec l'algorithme de dijkstra avec tas
/****************************************/
void graphe::resultats(int s){
	cout << "La valeur du plus court chemin de " << s << " à : " << endl ;
	for(int i = 0; i < n; i++)
		cout << "-> " <<  i << " est égale à " << d[i] << endl;
}


/****************************************/
/* Objectif : Calcul de tous les plus courts de s aux 
autres sommets. A la fin de la méthode :
-> le tableau d doit contenir la valeur des plus courts chemins
/****************************************/
void graphe::dijkstra(int s) {
    vector<int> vecD(n);
    vector<int> vecT(n - 1);
    vector<int> vecI(n);
    d[0] = 0;
    //initialisation de I, pere et d
    for(int i=0 ; i<=n ; i++) {
        I[i] = i - 1;   //si I[i] = -1, i n'est pas dans le tas
        pere[i] = 0;
        if(i>=1){ d[i] = infini; }
    }
    //initialisation du tas
    for(int i=0; i <n; i++) {
        T[i] = i + 1;
    }
    debugVect(vecD,vecT,vecI);
    int j = 0;
    for(int l = 1 ; l<n ; l++){
        vector<int> vecteurVoisin = voisin(j);
        for(auto i : vecteurVoisin){ //i appartient à successeur de j
            if(I[i] >= 0) {
                int cji = getCJI(i,j);
                cout << cji << endl;
                if (d[j] + cji < d[i]) {
                    d[i] = d[j] + cji;
                    pere[i] = j;
                    //reoganisation de T a partir de I(i)
                    reorganiser(T, I[i], n);
                    debugVect(vecD,vecT,vecI);
                }
            }
        }
        //recherche dans T de l'indice j de plus petite valeur d(i)
        j = T[1];
        //suppression de l'indice j de T
        supprimer(T,n);
    }
}

/*trouve les voisins de j*/
vector<int> graphe::voisin(int j) {
    vector<int> v;
    for(auto x : L[j]){
        v.push_back(x.first);
    }
    return v;
}

/*avoir cij*/
int graphe::getCJI(int i, int j){
    int dist = 0;
    for(auto x : L[j]){
        if(i == x.first){
            dist = x.second;
        }
    }
    return dist;
}

void graphe::debugVect(vector<int> &vecD, vector<int> &vecT, vector<int> &vecI) {
    for (int i = 0; i < n; i++) {
        vecD[i] = d[i];
    }
    for (int i = 0; i < n - 1; i++) {
        vecT[i] = T[i];
    }
    for (int i = 0; i < n; i++) {
        vecI[i] = I[i];
    }
}

/*echange T[i] et T[j]*/
void graphe::echanger(int *T, int i, int j){
    int tmp = infini;
    T[tmp] = T[i];
    T[i] = T[j];
    T[j] = T[tmp];
}

/*reorganise le tas*/
void graphe::reorganiser(int *T, int j, int n){
    int i = j;
    while(i<=n/2){
        int min = 0;
        if(d[T[2*i]] <= d[T[2*i+1]]){ min = 2*i;}
        else{ min = 2*i+1; }
        if(d[T[i]] > d[T[min]]){
            echanger(T,i,min);
            i = min;
        }else{ i = n; }
    }
}

/*supprimer une élément du Tas*/
int graphe::supprimer(int *T, int n){
    int min = T[1];
    T[1] = T[n];
    n = n-1;
    reorganiser(T,1,n);
    return min;
}

/*tri du tas*/
void graphe::triTas(int *T, int n){
    for(int k = n/2 ; k > 1 ; k--){ reorganiser(T,k,n); }
    int k = n;
    while(k>1){
        int min = supprimer(T,k);
        k = k-1;
        T[k+1] = min;
    }
}

