#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PBSTR "------------------------------------------------------------"
#define PBWIDTH 60

using namespace std;

Graph *leitura(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    //Pegando a ordem do grafo
    input_file >> order;

    cout << "order: " << order << endl;
    cout << "directed: " << directed << endl;
    cout << "weightedEdge: " << weightedEdge << endl
         << "weightedNode: " << weightedNode << endl;

    //Criando objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo

    if (!graph->getWeightedEdge() && !graph->getWeightedNode())
    { // Primeiro caso: aresta sem peso e sem pesos no nó

        while (input_file >> idNodeSource >> idNodeTarget)
        {
            cout << "IdNodeSource: " << idNodeSource << " -- "
                 << "idNodeTarget: " << idNodeTarget << endl;
            graph->insertEdge(idNodeSource, idNodeTarget, 0);
        }
    }
    else if (graph->getWeightedEdge() && !graph->getWeightedNode())
    { // Segundo caso: aresta com peso e sem peso nos nó

        float edgeWeight;
        while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
        {
            cout << "IdNodeSource: " << idNodeSource << " - "
                 << "idNodeTarget: " << idNodeTarget << endl;
            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
        }
    }
    else if (graph->getWeightedNode() && !graph->getWeightedEdge())
    { // Terceiro caso: aresta sem peso e com peso no nó

        float nodeSourceWeight, nodeTargetWeight;

        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, 0);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }
    else if (graph->getWeightedNode() && graph->getWeightedEdge())
    { // Quarto caso: aresta com peso e nó com peso

        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }

    return graph;
}
Graph *leituraTxt(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{
    int order;
    int idNodeSource;
    int idNodeTarget;

    input_file >> order;
    //Criando objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    if (!graph->getWeightedEdge() && !graph->getWeightedNode())
    {
        while (input_file >> idNodeSource >> idNodeTarget)
        {
            graph->insertEdge(idNodeSource, idNodeTarget, 0);
        }
    }
    else if (graph->getWeightedEdge() && !graph->getWeightedNode())
    {
        float edgeWeight;

        while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
        {
            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
        }
    }
    else if (graph->getWeightedNode() && !graph->getWeightedEdge())
    {
        float nodeSourceWeight, nodeTargetWeight;

        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {
            graph->insertEdge(idNodeSource, idNodeTarget, 0);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }
    else if (graph->getWeightedNode() && graph->getWeightedEdge())
    {
        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {
            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }
    return graph;
}
void printProgress(double percentage)
{
    int val = (int)(percentage * 100);
    int lpad = (int)(percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}
Graph *leituraVariacao(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{
    int numberOfGroups;
    int numberOfNodes;

    std::cout << "Enter the number of groups: ";
    std::cin >> numberOfGroups;

    std::cout << "Enter the number of nodes: ";
    std::cin >> numberOfNodes;

    //Criando objeto grafo
    Graph *graph = new Graph(numberOfNodes, directed, weightedEdge, weightedNode);
    graph->setNumberGroups(numberOfGroups);

    // Count number of edges in file
    int numEdges = 0;
    std::string unused;
    while (getline(input_file, unused))
    {
        ++numEdges;
    }

    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    numEdges -= (1 + numberOfNodes);

    // Insert nodes
    int groupId;
    for (int i = 0; i < numberOfNodes; i++)
    {
        input_file >> groupId;
        graph->insertNode(i, 0, groupId);
    }

    // Insert edges
    int nodeId;
    int targetId;
    float edgeWeight;

    int counter = 0;
    while (input_file >> nodeId >> targetId >> edgeWeight)
    {
        float progress = (float(counter) * 100) / float(numEdges);
        printProgress(progress / 100);
        graph->insertEdge(nodeId, targetId, edgeWeight);
        counter++;
    }
    cout << endl;
    return graph;
}

Graph *leituraInstancia(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;
    int numEdges;

    //Pegando a ordem do grafo
    input_file >> order >> numEdges;

    //Criando objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo
    while (input_file >> idNodeSource >> idNodeTarget)
    {

        graph->insertEdge(idNodeSource, idNodeTarget, 0);
    }

    return graph;
}

Graph *leitura2(string &input_file_name, ifstream &input_file,
                int directed, int weightedEdge, int weightedNode)
{
    // Get file extension
    string fileExtension = input_file_name.substr(input_file_name.find_first_of(".") + 1);
    cout << input_file_name << "\n";
    cout << fileExtension << "\n";

    if (fileExtension == "txt")
    {
        return leituraTxt(input_file, directed, weightedEdge, weightedNode);
    }
    else
    {
        return leituraVariacao(input_file, directed, weightedEdge, weightedNode);
    }
}

int menu()
{
    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Fecho Transitivo Direto" << endl;
    cout << "[2] Fecho Transitivo Indireto" << endl;
    cout << "[3] Caminho Minimo entre dois vertices - Dijkstra" << endl;
    cout << "[4] Caminho Minimo entre dois vertices - Floyd" << endl;
    cout << "[5] AGM sobre subgrafo vertice induzido por X usando algoritmo de Prim" << endl;
    cout << "[6] AGM sobre subgrafo vertice induzido por X usando algoritmo de Kruskal" << endl;
    cout << "[7] Caminhamento Profundidade destacando as Arestas de retorno" << endl;
    cout << "[8] Ordenacao topologica " << endl;
    cout << "[9] Subgrafo induzido por um conjunto de vertices X" << endl;
    cout << "[10] Imprime Grafo" << endl;
    cout << "[11] Algoritmo Guloso" << endl;
    cout << "[12] Algoritmo Guloso Randomizado " << endl;
    cout << "[13] Algoritmo Guloso Randomizado Reativo" << endl;
    cout << "[0] Sair" << endl;

    cout << "\nSua escolha: ";
    cin >> selecao;

    return selecao;
}

void selecionar(int selecao, Graph *graph, ofstream &output_file)
{

    switch (selecao)
    {
    case 1: // Fecho Transitivo Direto;
    {
        int v;

        cout << "Digite o id do nó: ";
        cin >> v;

        cout << "Fecho transitivo direto: ";
        graph->fechoTransitivoDireto(v, output_file);
        cout << endl;

        break;
    }
    case 2: // Fecho Transitivo Indireto;
    {
        int v;

        cout << "Digite o id do nó: ";
        cin >> v;

        cout << "Fecho transitivo indireto: ";
        graph->fechoTransitivoIndireto(v, output_file);
        cout << endl;
        break;
    }
    case 3: //Caminho mínimo entre dois vértices usando Dijkstra;
    {
        int orig, dest;
        cout << "Insira no origem: ";
        cin >> orig;
        cout << "Insira no destino: ";
        cin >> dest;
        graph->dijkstra(orig, dest, output_file);
        break;
    }
    case 4: //Caminho mínimo entre dois vértices usando Floyd;
    {
        int orig, dest;
        cout << "Insira no origem: ";
        cin >> orig;
        cout << "Insira no destino: ";
        cin >> dest;
        graph->Floyd(orig, dest, output_file);
        break;
    }
    //AGM Prim;
    case 5:
    {
        int tam;
        cout << "Digite o tamanho do conjunto de vertices: ";
        cin >> tam;
        int cont = 0;
        int *conjunto = new int[tam];
        cout << "Digite os IDs dos vertices que irao compor esse conjunto: " << endl;
        while (cont < tam)
        {
            cout << "ID " << cont << " : " << endl;
            cin >> conjunto[cont];
            cont++;
        }

        graph->primMST(graph->subGrafoInduzido(conjunto, tam, output_file), output_file);
        break;
    }
    case 6: //AGM - Kruscal;
    {
        int tam;
        cout << "Digite o tamanho do conjunto de vertices: ";
        cin >> tam;
        int cont = 0;
        int *conjunto = new int[tam];
        cout << "Digite os IDs dos vertices que irao compor esse conjunto: ";
        while (cont < tam)
        {
            cout << "Vertice " << cont << " : " << endl;
            cin >> conjunto[cont];
            cont++;
        }

        graph->kruskal(graph->subGrafoInduzido(conjunto, tam, output_file), output_file);
        break;
    }
    case 7: //Caminhamento em Profundidade;
    {
        int x = 0;
        cout << "Insira id do no de partida: ";
        cin >> x;
        graph->caminhamentoProfundidade(x, output_file);
        break;
    }
    case 8: //Ordenação Topologica;
    {
        graph->ordenacaoTopologica(output_file);
        break;
    }

    case 9: //Subgrafo induzido por um conjunto de vértices X;
    {
        int tam;
        cout << "Digite o tamanho do conjunto de vértices: ";
        cin >> tam;
        int cont = 0;
        int *conjunto = new int[tam];
        cout << "Digite os IDs dos vértices que irão compor esse conjunto: ";
        while (cont < tam)
        {
            cin >> conjunto[cont];
            cont++;
        }
        graph->subGrafoInduzido(conjunto, tam, output_file);
        break;
    }
    case 10:
    {
        graph->imprimeGrafo();
        break;
    }
    case 11: //Guloso
    {
        cout << "Nao implementado" << endl;
        break;
    }
    case 12: //Guloso Randomizado
    {
        cout << "Nao implementado" << endl;
        break;
    }
    case 13: //Guloso Randomizado Reativo
    {
        cout << "Nao implementado" << endl;
        break;
    }
    default:
    {
        cout << " Error!!! invalid option!!" << endl;
        break;
    }
    }
}

int mainMenu(ofstream &output_file, Graph *graph)
{
    int selecao = 1;
    while (selecao != 0)
    {
        system("clear");
        selecao = menu();

        if (output_file.is_open())
            selecionar(selecao, graph, output_file);
        else
            cout << "Unable to open the output_file" << endl;

        output_file << endl;
    }
    return 0;
}

int main(int argc, char const *argv[])
{

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6)
    {
        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if (input_file_name.find("v") <= input_file_name.size())
    {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Executando " << program_name << " com instancia " << instance << " ... " << endl;
    }

    // Criando a pasta para armazenar os resultados
    mkdir("tests");

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    // Criando grafo da leitura do arquivo
    Graph *graph;

    // Verificando se conseguiu abrir o arquivo de entrada
    if (input_file.is_open())
    {

        //graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        // graph.print();
        graph = leitura2(input_file_name, input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        cout << "Order: " << graph->getOrder() << "\n";
        // Chamando main menu
        mainMenu(output_file, graph);
    }
    else
        cout << "Não foi possível abrir o arquivo de entrada! " << argv[1];

    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}
