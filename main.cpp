#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>

using namespace std;

struct node{
    int id;             // id del nodo
    bool isRouter = true;  // -1 por defecto, 0 si es un cliente, 1..n si es un router
};

struct modelo{
    int id;             // id del nodo
    float price =0;     // precio del router
    float pfail=0;      // probabilidad de fallo del router
};


struct estado{
    vector<int> solucion;
    double f;
};



// Calcular solucion inicial (Greedy)



// Generar vecinos


// Simulated annealing



// visualizar la lista de adyacencia
void printAdjList(vector< list< pair <int,int> > > adjList) {
    for (int i = 0; i < adjList.size(); ++i) {
        cout << "nodo: "<< i;

        list<pair<int, int> >::iterator itr = adjList[i].begin();

        while (itr != adjList[i].end()) {
            cout <<" -> "<< (*itr).first << "(" <<(*itr).second << ")";
            ++itr;
        }
        cout << endl;
    }
}

// función que crea un vector de nodos
vector<node> createNodesVector(int numNodes){
    vector<node> nodes;
    for (int i = 0; i<numNodes;i++){
        node n;
        n.id=i;
        nodes.push_back(n);
    }
    return nodes;
}

int main(int argc, char *argv[]){
    ifstream infile;
    infile.open(argv[1]);
    int totalNodes; // número total de nodos
    int numC;       // número total de clientes
    int numE;       // número de aristas
    int budget;     // presupuesto total
    int numModels;  // tipos de modelos de routers


    string line;    // cada línea del fichero

    // leer el número total de nodos
    getline(infile, line);
    istringstream iss(line);
    iss >>totalNodes;
    cout <<"Número de nodos: " <<totalNodes<<endl;

    // se crea el vector de nodos
    vector<node> nodes = createNodesVector(totalNodes);

    /* La lista de adyacencia es un vector de listas cada elemento es un pair<int, int>
     * donde pair.first -> destino de la arista | pair.second -> peso de la arista */
    // TotalNodes son los vértices
    vector< list< pair <int, int> > > adjacencyList(totalNodes);

    // leer número total de clientes
    getline(infile, line);
    istringstream iss2(line);
    iss2 >> numC;
    cout<<"Número de clientes: "<<numC<<endl;

    // se leen las ids para cada cliente
    getline(infile, line);
    istringstream iss3(line);
    int n;
    while (iss3 >> n) {
        nodes[n].isRouter = false;  // si es cliente se le asigna un 0
    }

    // leer el número de aristas
    getline(infile, line);
    istringstream iss4(line);
    iss4 >> numE;
    cout<<"Número de aristas: "<<numE<<endl;

    // se lee el grafo
    for (int i = 0; i<numE; i++){
        getline(infile, line);
        istringstream iss(line);
        int v1,v2;
        iss >> v1;
        iss >> v2;
        adjacencyList[v1].push_back(make_pair(v2, 1));
        adjacencyList[v2].push_back(make_pair(v1, 1));
    }

    // leer el presupuesto
    getline(infile, line);
    istringstream iss5(line);
    iss5 >> budget;
    cout<<"Presupuesto total: "<<budget<<endl;

    // leer el número total de modelos (tipos de router)
    getline(infile, line);
    istringstream iss6(line);
    iss6 >> numModels;
    cout<<"Tipos de router: " <<numModels<<endl<<endl;

    vector<modelo> modelos(numModels); //Modelos del router
    //Leer precio y probabilidad de fallo
    for (int i = 0; i<numModels; i++){
        getline(infile, line);
        istringstream iss(line);
        iss >>modelos[i].id;
        iss >>modelos[i].price;
        iss >>modelos[i].pfail;
    }

    infile.close(); // cierra fichero

    // se muestra el grafo completo (lista de adyacencia)
    cout<<"Grafo"<<endl;
    printAdjList(adjacencyList);
    cout << endl;

    // se muestra la información de cada uno de los nodos del grafo
    cout<<"Información de los nodos"<<endl;
    for (int i = 0; i<nodes.size();i++){
        cout<<"Nodo "<<nodes[i].id<<" --> ";
        if (nodes[i].isRouter == false)
            cout << "Es un cliente"<<endl;
        else {
            cout << "Es un router "<<endl;
        }
    }

    for (int i = 0; i<modelos.size();i++){
        cout<<"Modelo número: "<<modelos[i].id<<endl;
        cout<<"Precio: "<<modelos[i].price<<endl;
        cout<<"Probabilidad de fallo: "<<modelos[i].pfail<<endl;
    }

    return 0;
}