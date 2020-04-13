#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <stack>

using namespace std;

#include "dijkstra.h"

vector<int> vecD;
vector<int> vecT;
vector<int> vecI;
vector<int> vecPere;

/****************************************/
/* Objectif : Constructeur avec comme argument
le nom du fichier contenant le graphe.
Il doit :
-> ouvrir le fichier filename
-> initialiser, avec son contenu, les attributs "n", "m" et "L",
/****************************************/
graphe::graphe(char *filename) {
    ifstream file(filename);

    file >> n;
    file >> m;

    T = new int[n];
    I = new int[n];
    d = new int[n];
    pere = new int[n];

    int i, j, k, l;

    for (i = 0; i < n; i++) {
        vector<sommetadjacent> vect;
        L.push_back(vect);
    }

    for (i = 0; i < m; i++) {
        file >> j;
        file >> k;
        file >> l;
        L[j].push_back(make_pair(k, l));
        L[k].push_back(make_pair(j, l));
    }

    file.close();
}


/****************************************/
/* Objectif : Affichage des arêtes et longueurs
/****************************************/
void graphe::donnees() {
    cout << "arête : " << "longueur" << endl;
    for (int i = 0; i < L.size(); i++)
        for (int j = 0; j < L[i].size(); j++)
            if (i < L[i][j].first)
                cout << "(" << i << "," << L[i][j].first << ")" << ": " << L[i][j].second << endl;
}

/****************************************/
/* Objectif : Affichage des valeurs des plus courts
chemins trouvés avec l'algorithme de dijkstra avec tas
/****************************************/
void graphe::resultats(int s) {
    cout << "La valeur du plus court chemin de " << s << " à : " << endl;
    for (int i = 0; i < n; i++)
        cout << "-> " << i << " est égale à " << d[i] << endl;
}


/****************************************/
/* Objectif : Calcul de tous les plus courts de s aux 
autres sommets. A la fin de la méthode :
-> le tableau d doit contenir la valeur des plus courts chemins
/****************************************/
void graphe::dijkstra(int s) {
    vector<int> vecDp(n);
    vector<int> vecTp(n - 1);
    vector<int> vecIp(n);
    vector<int> vecPerep(n);
    vecD = vecDp;
    vecT = vecTp;
    vecI = vecIp;
    vecPere = vecPerep;
    d[0] = 0;
    //initialisation de I, pere et d
    for (int i = 0; i <= n; i++) {
        I[i] = i - 1;   //si I[i] = -1, i n'est pas dans le tas
        pere[i] = -1;
        if (i >= 1) { d[i] = infini; }
    }
    //initialisation du tas
    for (int i = 0; i < n; i++) {
        T[i] = i + 1;
    }
    debugVect(vecD, vecT, vecI, vecPere);
    int j = 0;
    for (int l = 1; l < n; l++) {
        int size = sizeof(T);
        if(l>1){ size = size - 1; }
        else{ size = size - 1 - l; }
        vector<int> vecteurVoisin = voisin(j);
        for (auto i : vecteurVoisin) { //i appartient à successeur de j
            if (I[i] >= 0) {
                int cji = getCJI(i, j);
                if (d[j] + cji < d[i]) {
                    d[i] = d[j] + cji;
                    pere[i] = j;
                    //reoganisation de T a partir de I(i)
                    reorganiser(T,0, size);
                    debugVect(vecD, vecT, vecI, vecPere);
                }
            }
        }
        //recherche dans T de l'indice j de plus petite valeur d(i)
        j = supprimer(T, size - l);
        //suppression de l'indice j de T
        debugVect(vecD, vecT, vecI, vecPere);

    }
}

/*trouve les voisins de j*/
vector<int> graphe::voisin(int j) {
    vector<int> v;
    for (auto x : L[j]) {
        v.push_back(x.first);
    }
    return v;
}

/*avoir cij*/
int graphe::getCJI(int i, int j) {
    int dist = 0;
    for (auto x : L[j]) {
        if (i == x.first) {
            dist = x.second;
        }
    }
    return dist;
}

void graphe::debugVect(vector<int> &vecD, vector<int> &vecT, vector<int> &vecI, vector<int> &vecPere) {
    for (int i = 0; i < n; i++) {
        vecD[i] = d[i];
    }
    for (int i = 0; i < n - 1; i++) {
        vecT[i] = T[i];
    }
    for (int i = 0; i < n; i++) {
        vecI[i] = I[i];
    }
    for (int i = 0; i < n; i++) {
        vecPere[i] = pere[i];
    }
}

/*echange T[i] et T[j]*/
void graphe::echanger(int *x, int i, int j) {
    int tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
}

/*reorganise le tas*/
void graphe::reorganiser(int *T, int j, int n) {
    int i = j;
    while (i <= n / 2 and n>0) {
        int min = 0;
        if (i == 0) {
            if (d[T[1]] < d[T[2]]) { min = 1; }
            else { min = 2; }
        } else {
            if (2 * i + 1 < n - 2) {
                if (d[T[2 * i]] <= d[T[2 * i + 1]]) { min = 2 * i; }
                else { min = 2 * i + 1; }
            } else { break; }
        }
        int dti = d[T[i]];
        int dtmin = d[T[min]];
        int ti = T[i];
        int tmin = T[min];
        if (d[T[i]] > d[T[min]]) {
            //echanger(I,T[i],T[min]);
            I[T[i]] = min;
            I[T[min]] = i;
            echanger(T,i,min);
            i = min;
        } else { i = n; }
    }
}

/*supprimer une élément du Tas*/
int graphe::supprimer(int *T, int n) {
    int min = 0;
    if(n>=0) {
        min = T[0];
        T[0] = T[n];    //on remonte le dernier element au sommet
        I[min] = -1;
        debugVect(vecD, vecT, vecI, vecPere);
        reorganiser(T, 0, n);
        debugVect(vecD, vecT, vecI, vecPere);
    }
    return min;
}


