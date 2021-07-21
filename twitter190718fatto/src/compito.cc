/*
 * Il main nel file compito.cc deve contenere il codice per l’acquisizione del grafo orientato
 * contenuto nel file graph quindi richiamare la procedura stampa(graph)
 * che stampa gli archi del grafo.
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#include "grafi.h"
#include "nodo.h"

void add(graph& g, int u, int v, float w, bool o){
    if(o)
        add_arc(g, u, v, w);
    else
        add_edge(g, u, v, w);
}

graph graphBuild(ifstream& g, bool orientato, bool pesato){
    int n;
    g>>n;
    graph G = new_graph(n);
    int v1,v2;

    if(pesato){
        float w;
        while(g>>v1>>v2>>w)
            add(G,v1,v2,w,orientato);
    }
    else {

        while (g >> v1 >> v2)
            add(G, v1, v2,1.0, orientato);
    }
    return G;
}

void stampaGrafo(graph G){
    adj_list temp;
    for(int i = 1; i <= get_dim(G); i++){
        temp = get_adjlist(G,i);
        cout<<i;
        while(temp){
            cout<<"-->"<<get_adjnode(temp)<<" ";
            temp = get_nextadj(temp);
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    cout<<endl;
}

// tweetter va da 0 a n-1 mentre G va da 1 a n
void stampaRelazioni(graph G, node* tweetter){
	adj_list temp;
	for(int i = 1; i <= get_dim(G); i++){
		temp = get_adjlist(G,i);
	    while(temp){

	    	cout<<tweetter[i-1].cont;

	    	if(tweetter[i-1].tipo == 'U' && tweetter[temp->node].tipo == 'U')
	    		cout<<" FOLLOW "<<tweetter[temp->node].cont<<endl;
	    	if(tweetter[i-1].tipo == 'T' && tweetter[temp->node].tipo == 'U')
	    		cout<<" OWNER "<<tweetter[temp->node].cont<<endl;
	    	if(tweetter[i-1].tipo == 'U' && tweetter[temp->node].tipo == 'T')
	    		cout<<" LIKE "<<tweetter[temp->node].cont<<endl;
	        temp = get_nextadj(temp);
	    }
	}
}

/*
 * funzione int* totalLike(graph,node*) che restituisce un vettore dinamico V
 * della dimensione corrispondente al numero di nodi.
 * Per ogni nodo con identificativo i, V[i-1] contiene il numero totale di like
 * ricevuti per i suoi tweet se il nodo è di tipo utente, V[i-1]=0 altrimenti.
 */
void totLike(graph G, node* n){
	int like[G.dim], popular[G.dim], max = 0;

	for(int i = 0; i < G.dim; i++){
		like[i] = 0;
		popular[i] = 0;
	}

	adj_list temp;
	for(int i = 1; i <= get_dim(G); i++){
		temp = get_adjlist(G,i);

		while(temp){
			if(n[i-1].tipo == 'U' && n[temp->node].tipo == 'T')
				like[temp->node]++;
			temp = get_nextadj(temp);
		}
	}

	for(int i = 1; i <= get_dim(G); i++){
		temp = get_adjlist(G,i);

		while(temp){
			if(n[i-1].tipo == 'T' && n[temp->node].tipo == 'U')
				popular[temp->node] += like[i-1];
			temp = get_nextadj(temp);
		}
	}

	cout<<"Gli utenti popolari sono: ";
	for(int i = 0; i < G.dim; i++){
		if(popular[i] >= max) max = popular[i];
		else popular[i] = 0;

		if(popular[i] != 0)
			cout<<n[i].cont<<"\t";
	}
}


int main(int argc, char* argv[]) {
/*	PUNTO 1	*/
	if(argc<3) {
		cout << "Gli argomenti inseriti non sono sufficienti!" << endl;
		exit(0);
	}

	ifstream g;
	g.open(argv[1]);
	int orientato = atoi(argv[2]);
	int pesato = atoi(argv[3]);

	graph G = graphBuild(g,orientato,pesato);

	cout<<"Il grafo ha dimensione: "<<get_dim(G)<<endl;
	stampaGrafo(G);

/*	PUNTO 2	*/
	node* n = new node[get_dim(G)];
	ifstream node;
	node.open("node");

	for(int i = 0; i < get_dim(G); i++){
		node.getline(n[i].cont, 81);
		node>>n[i].tipo;

		node.ignore();
	}

	stampaRelazioni(G, n);
	cout<<endl<<endl;

/*	PUNTO 3	*/
	totLike(G, n);

	cout<<endl<<"Success!"<<endl;
	return 0;
}


