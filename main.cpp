#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>

using namespace std;

struct node{
    int id; //Id del nodo
    float price =0; //El precio
    float pfail=0; //Probabilidad de fallo
    int isRouter = -1; //SI es un 1 es un router, si no es un cliente
};

void printAdjList(vector<list<pair<int,int>>> adjacencyList) {
// Imprime por pantalla la lista de adyacencia
    for (int i = 0; i < adjacencyList.size(); ++i) {
        printf("adjacencyList[%d] ", i);

        list<pair<int, int> >::iterator itr = adjacencyList[i].begin();

        while (itr != adjacencyList[i].end()) {
            printf(" -> %d(%d)", (*itr).first, (*itr).second);
            ++itr;
        }
        printf("\n");
    }
}

//Función que crea un vector de nodos
vector<node> createNodesVector(int numNodes) {
    vector<node> nodes;
    for (int i = 0; i<numNodes;i++) {
        node n;
        n.id=i;
        nodes.push_back(n);
    }
    return nodes;
}



int main() {
    ifstream infile;
    infile.open("/home/usuario/Escritorio/Clase/TOC/Proyecto/Workspace/in.txt");
    int totalNodes; //Número total de nodes
    int numC; //Número total de clientes
    int numE; //Número de aristas
    int budget; //Presupuesto
    int numModels; //Número de modelos

    string line; //Cada línea del fichero

    //leer el número total de nodos
    getline(infile, line);
    istringstream iss(line);
    iss >>totalNodes;
    cout <<"Número de nodos " <<totalNodes<<endl;

    //Se crea el vector de nodos
    vector<node> nodes = createNodesVector(totalNodes);

    // Adjacency List is a vector of list.
    // Where each element is a pair<int, int>
    // pair.first -> the edge's destination
    // pair.second -> edge's weight
    //TotalNodes son los vértices
    vector<list<pair<int, int>>> adjacencyList(totalNodes);


    //leer el número total de clientes
    getline(infile, line);
    istringstream iss2(line);
    iss2 >> numC;

    cout<<"Número de clientes "<<numC<<endl;

    //Para cada cliente, se leen las ids
    getline(infile, line);
    istringstream iss3(line);
    int n;
    while (iss3 >> n) {
        nodes[n].isRouter = 0;
    }

    //Leer el número de aristas
    getline(infile, line);
    istringstream iss4(line);
    iss4 >> numE;
    cout<<"Número aristas "<<numE<<endl;

    //Leer el grafo
    for (int i = 0; i<numE; i++)
    {
        getline(infile, line);
        istringstream iss(line);
        int v1,v2;
        iss >> v1;
        iss >> v2;
        adjacencyList[v1].push_back(make_pair(v2, 1));
    }

    //leer el presupuesto
    getline(infile, line);
    istringstream iss5(line);
    iss5 >> budget;
    cout<<"Presupuesto "<<budget<<endl;

    //leer el número total de modelos
    getline(infile, line);
    istringstream iss6(line);
    iss6 >> numModels;
    cout<<"número modelos " <<numModels<<endl;

    //Leer precio y probabilidad de fallo
    for (int i = 0; i<numModels; i++)
    {
        getline(infile, line);
        istringstream iss(line);
        int model; //La id del router
        float price; //El precio
        float pfail; //Prob fallo
        iss >>model;
        iss >>price;
        iss >>pfail;
        int id;
        while (iss >> id) {
            nodes[id].isRouter = model;
            nodes[id].price = price;
            nodes[id].pfail = pfail;
        }
    }


    cout<<"Lista de adyacencia"<<endl;
    printAdjList(adjacencyList);

    cout<<"Vector de nodos"<<endl;
    for (int i = 0; i<nodes.size();i++){
        cout<<"IdCliente "<<nodes[i].id<<" ";
        cout<<"Precio "<<nodes[i].price<<" ";
        cout<<"Pfallo "<<nodes[i].pfail<<" ";
        cout<<"EsRouter "<<nodes[i].isRouter<<endl;
    }
    infile.close();
}
