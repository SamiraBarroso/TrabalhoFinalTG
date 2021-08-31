/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <fstream>
#include <stack>
#include <list>
#include <vector>
#include "ListaEncad.h"

using namespace std;

struct Par
{
    Node *u, *v;
    float weight;

    // sobrescrita do operador "<"
    bool operator<(const Par &aresta2) const
    {
        return (weight < aresta2.weight);
    }
};

class Graph
{

    //Atributes
private:
    int order;
    int number_edges;
    bool directed;
    bool weighted_edge;
    bool weighted_node;
    Node *first_node;
    Node *last_node;
    int nodesCount;
    int number_Groups;

    int cont; //variavel para preencher a lista pares

    vector<Par> arestas; // vetor de arestas para o algoritmo de Kruskal

    //list<Node> nodesList; //lista de nos do grafo
    ListaEncad *nodesList;

    list<pair<int, int>> *pares;

public:
    //Constructor
    Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
    //Destructor
    ~Graph();
    //Getters
    int getOrder();
    int getNumberEdges();
    bool getDirected();
    bool getWeightedEdge();
    bool getWeightedNode();
    Node *getFirstNode();
    Node *getLastNode();
    int getNodeCount();

    //Other methods
    void insertNode(int id, float weight, int groupId);
    void insertEdge(int id, int target_id, float weight);
    void removeNode(int id);
    bool searchNode(int id);
    Node *getNode(int id);
    Edge *getEdgeBetween(int id, int targetId);
    void imprimeGrafo();
    void removeAllEdges(int id);
    bool hasEdgeBetween(int origem, int destino);
    int grauGrafo();
    void setNumberGroups(int n);

    //methods phase1

    //Fechos
    bool auxCiclo(int origem, bool visitados[], bool *aux);
    bool ciclo();
    void fechoTransitivoDireto(int idNode, ofstream &saida);
    void fechoTransitivoIndireto(int idNode, ofstream &saida);

    //Ordenação Topologica
    void ordenacaoTopologica(ofstream &saida);
    int getGrauEntrada(int idNode);

    //void breadthFirstSearch(ofstream &output_file);
    //Busca Profundidade
    void caminhamentoProfundidade(int x, ofstream &saida);
    void auxBuscaEmProfundidade(int x, bool *verificavisitado, ofstream &saida, string nodesSeparator);

    //Graph *getVertexInduced(int *listIdNodes);
    //Subgrafo induzido
    Graph *subGrafoInduzido(int *vet, int tam, ofstream &saida);
    int retornaIndice(int *vet, int tam, int val);

    //Graph *agmKuskal();
    //Algoritmo de Kruskal
    void swap(vector<Edge *> arr, int a, int b);
    Edge **sortsEdgeWeights(); //retorna vetor com as arestas ordenadas
    void kruskal(Graph *subgrafo, ofstream &saida);
    int buscar(int subarvores[], int i);
    void unir(int subarvores[], int u, int v);

    //Graph *agmPrim();
    //PRIM
    void primMST(Graph *subgrafo, ofstream &saida);
    int auxPrim(int *custo, int *prox, int n);

    //float floydMarshall(int idSource, int idTarget);
    //Floyd
    void Floyd(int origem, int destino, ofstream &saida);
    void printPath(int **path, int v, int u, vector<int> &vet);

    //float dijkstra(int idSource, int idTarget);
    //Dijkstra
    void dijkstra(int orig, int dest, ofstream &saida);

    //methods phase1
    float greed(ofstream &saida);
    float greedRandom();
    float greedRactiveRandom();

private:
    //Auxiliar methods
};

#endif // GRAPH_H_INCLUDED
