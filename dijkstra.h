/************************************************************************/
/* Auteur : S. Gueye						                        	*/
/* TP : Plus court chemin : Algorithme de dijkstra avec tas O(mlog(n))	*/
/* Date dernière maj : 29/03/2020					                    */
/************************************************************************/

const int infini = 1e+5;
typedef pair<int,int> sommetadjacent; 
/* un sommet adjacent j, à un noeud i, est une paire (j, longueur de l'arête (i,j)) */
typedef vector< vector<sommetadjacent> > listeadjacence;
/*
Une liste d'adjacence est une structure de données permettant de représenter un graphe simple de façon plus économique qu'une 
matrice d'adjacence.
Supposons que L soit de type listeadjacence comme l'est l'attribut ci-dessous de la classe graphe.
L est un "vecteur" indicé par les numéros i = 0,1,2,...,n-1 des sommets. 
Pour chaque i, L[i] contient la liste des sommets adjacents à i. 
Si le sommet j est adjacent à i, et que la longueur de l'arete (i,j) est 10 (par exemple) alors L[i] contiendra le couple (j,10)
*/
/* Le fonctionnement de ces deux classes génériques est expliqué ici :  http://www.cplusplus.com */

class graphe{
	int n; 			    // Nombre de noeuds du graphe
	int m;			    // Nombre d'arêtes du graphe
	listeadjacence L; 	// Liste d'adjacence du graphe 
	int *T; 		    // Tas contenant initialement les éléments 1,2,...,(n-1)
	int *I;			    // Tableau donnant pour chaque noeud i= 0,1,3,...,(n-1), l’indice de sa position dans T.
				        // I(i) = -1 signifiera que i n’est pas dans T.
	int *d;			    // Tableau des valeurs des plus courts chemins à partir de s. d[i] est la valeur du plus chemin de s à i
	int *pere;	    	// Tableau donnant pour chaque sommet i le prédécesseur de i (pere(i)) dans le plus court chemin de s à i
public : 
	graphe(char* filename);
	void donnees();
	void resultats(int s);
	void dijkstra(int s);

	void reorganiser(int *T, int j, int n);
	int supprimer(int *T, int n);
	void triTas(int *T, int n);
	int getCJI(int i, int j);
	void echanger(int *T, int i, int j);
	vector<int> voisin(int j);

	void debugVect(vector<int> &vecD, vector<int> &vecT, vector<int> &vecI);
};
