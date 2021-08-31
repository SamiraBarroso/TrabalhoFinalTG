#include <iostream>
#include "Graph.h"
#include <vector>
#include <algorithm> // sort
#include <string.h>  // memset
#include <string>
#include <queue>
#include <time.h>
// #include <bits/stdc++.h>
#define INF 9999
using namespace std;
/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/
//typedef pair<int, int> Pair;

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
    this->nodesCount = 0;
    number_Groups = 0;

    nodesList = new ListaEncad();
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{
    return this->order;
}

int Graph::getNumberEdges()
{
    return this->number_edges;
}

//Function that verifies if the graph is directed
bool Graph::getDirected()
{
    return this->directed;
}

//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{
    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{
    return this->weighted_node;
}

Node *Graph::getFirstNode()
{
    return this->first_node;
}

Node *Graph::getLastNode()
{
    return this->last_node;
}
int Graph::getNodeCount()
{
    return this->nodesCount;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/

void Graph::insertNode(int id, float weight, int groupId)
{
    Node *newNode = new Node(id);
    nodesCount++;
    nodesList->insereFinal(newNode);

    if (this->weighted_node)
    {
        newNode->setWeight(weight);
    }
    if (groupId != -1)
    {
        newNode->setGroupId(groupId);
    }
    if (this->first_node != nullptr)
    {
        this->last_node->setNextNode(newNode);
        this->last_node = newNode;
    }
    else
    {
        this->first_node = newNode;
        this->last_node = newNode;
    }
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    if (!this->searchNode(id))
    {
        this->insertNode(id, 0, -1);
    }

    if (!this->searchNode(target_id))
    {
        this->insertNode(target_id, 0, -1);
    }

    if (this->directed)
    {
        Node *node = this->getNode(id);
        if (!node->hasEdgeBetween(target_id))
        {
            Par par;
            par.u = node;
            Node *targetNode = this->getNode(target_id);
            par.v = targetNode;
            par.weight = weight;
            arestas.push_back(par);

            node->insertEdge(target_id, weight, node->getId());
            Edge edgeaux(target_id, id, weight);
            arestasVet.push_back(edgeaux);

            number_edges++;
        }
    }
    else
    {
        Node *node = this->getNode(id);
        Node *targetNode = this->getNode(target_id);

        if (!node->hasEdgeBetween(target_id))
        {
            Par par;
            par.u = node;
            par.v = targetNode;
            par.weight = weight;
            arestas.push_back(par);
            node->insertEdge(target_id, weight, node->getId());

            Edge edgeaux(target_id, id, weight);
            this->arestasVet.push_back(edgeaux);

            number_edges++;
        }

        if (!targetNode->hasEdgeBetween(id))
        {
            Par par;
            par.u = node;
            par.v = targetNode;
            par.weight = weight;
            arestas.push_back(par);
            targetNode->insertEdge(id, weight, target_id);

            Edge edgeaux(target_id, id, weight);
            this->arestasVet.push_back(edgeaux);

            number_edges++;
        }
    }
}

void Graph::removeNode(int id)
{
    //cria um ponteiro para o node desejado
    Node *node = getNode(id);

    //retorna caso nao exista o node desejado
    if (node == nullptr)
        return;
    else if (node == first_node) //se o node eh o primeiro, apenas faz o proximo ser o primeiro
        first_node = node->getNextNode();
    else
    {
        //caso seja um node do meio ou o ultimo, cria um ponteiro auxiliar
        Node *aux = first_node;

        //encontra o node anterior ao node desejado
        while (aux->getNextNode() != node)
            aux = aux->getNextNode();

        //se o no desejado for o ultimo, atualiza o ultimo para o anterior
        if (node == last_node)
            last_node = aux;

        //seta o proximo de anterior para o proximo do desejado
        aux->setNextNode(node->getNextNode());
    }

    //deleta o node desejado
    delete node;
}

bool Graph::searchNode(int id)
{
    if (this->first_node != nullptr)
    {
        Node *aux = this->first_node;

        while (aux != nullptr)
        {
            if (aux->getId() == id)
            {
                return true;
            }

            aux = aux->getNextNode();
        }
    }
    return false;
}

Node *Graph::getNode(int id)
{
    if (this->first_node != nullptr)
    {
        Node *aux = this->first_node;

        while (aux != nullptr)
        {
            if (aux->getId() == id)
            {
                return aux;
            }

            aux = aux->getNextNode();
        }
    }
    return nullptr;
}

void Graph::imprimeGrafo()
{
    if (this->first_node != nullptr)
    {
        Node *aux = this->first_node;

        while (aux != nullptr)
        {
            if (getWeightedNode())
            {
                cout << aux->getId() << "(" << aux->getWeight() << "):";
            }
            else
            {
                cout << aux->getId() << ":";
            }
            Edge *auxEdge = aux->getFirstEdge();
            while (auxEdge != NULL)
            {
                if (getWeightedEdge())
                {
                    cout << " -> edge: " << auxEdge->getTargetId() << " (" << auxEdge->getWeight() << ")";
                }
                else
                {
                    std::cout << " -> edge: " << auxEdge->getTargetId();
                }
                auxEdge = auxEdge->getNextEdge();
            }
            cout << endl;

            aux = aux->getNextNode();
        }
        cout << endl;
    }
    else
    {
        cout << "Grafo vazio" << endl;
    }
}
void Graph::removeAllEdges(int id)
{
    Node *node = this->getNode(id);
    if (node != nullptr)
    {
        node->removeAllEdges();
    }
}

bool Graph::hasEdgeBetween(int origem, int destino)
{
    Node *node = this->first_node;
    while (node != nullptr)
    {
        Edge *edge = node->getFirstEdge();
        while (edge != nullptr)
        {
            if (node->getId() == origem && edge->getIdDestino() == destino)
            {
                return true;
            }
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }
    return false;
}
Edge *Graph::getEdgeBetween(int origem, int destino)
{
    Node *node = this->first_node;
    while (node != nullptr)
    {
        Edge *edge = node->getFirstEdge();
        while (edge != nullptr)
        {
            if (node->getId() == origem && edge->getTargetId() == destino)
            {
                return edge;
            }
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }
    return nullptr;
}

int Graph::grauGrafo()
{
    int i = 0;
    Node *node = this->first_node;
    while (node != nullptr)
    {
        Edge *edge = node->getFirstEdge();
        while (edge != nullptr)
        {
            i++;
            edge = edge->getNextEdge();
        }

        node = node->getNextNode();
    }
    return i;
}
void Graph::setNumberGroups(int n)
{
    number_Groups = n;
}

////////////////////////////////////////////////////FECHOS//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////FECHO TRANSITIVO DIRETO///////////////////////////////////////////////////////////////////////

bool Graph::auxCiclo(int origem, bool visitados[], bool *aux)
{
    if (!visitados[origem])
    {
        visitados[origem] = true;
        aux[origem] = true;
        Node *no = this->getNode(origem);
        for (Edge *aresta = no->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
        {
            if (!visitados[aresta->getIdDestino()] && auxCiclo(aresta->getIdDestino(), visitados, aux))
                return true;

            else if (aux[aresta->getIdDestino()])
                return true;
        }
    }
    aux[origem] = false;
    return false;
}

bool Graph::ciclo()
{
    // vetor para gerenciar o Nos visitados
    bool *visitados = new bool[this->order];
    bool *aux = new bool[this->order];

    // inicializando vetores
    for (int i = 0; i < this->order; i++)
    {
        visitados[i] = false;
        aux[i] = false;
    }

    for (int id_origem = 0; id_origem < this->order; id_origem++)
    {
        // Chamando funcao recursiva para verificar existencia ed ciclos
        if (this->auxCiclo(id_origem, visitados, aux))
            return true;
    }
    return false;
}

//Recebe como parametro um id de um vertice x do grafo, e mostra todos as arestas de um no y alcançavel
//por um caminho direcionado com origem em x
void Graph::fechoTransitivoDireto(int idNode, ofstream &saida)
{
    if (!this->getDirected())
    {
        cout << "Fecho Transitivo Direto impossivel: o grafo nao eh Direcionado." << endl;
        return;
    }
    // if (this->ciclo())
    // {
    //     cout << "Fecho Transitivo Direto impossivel: o grafo possui Ciclos. \n";
    //     return;
    // }

    bool *visitado = new bool[this->getOrder()]; //vetor para controlar nós visitados
    for (int i = 0; i < this->getOrder(); i++)   //seta todos as posicoes para nao visitado
        visitado[i] = false;

    visitado[idNode] = true;

    stack<int> pilha;
    pilha.push(idNode);

    string graphType;
    string nodesSeparator;

    graphType = "digraph";
    nodesSeparator = "->";

    saida << graphType << "Fecho Transitivo Direto {\n";

    while (!pilha.empty())
    {
        Node *no = this->getNode(pilha.top()); // Recupera o no do topo da pilha
        pilha.pop();                           // Remove topo da pilha

        // Laço para percorrer as arestas do no que estava no topo da pilha
        for (Edge *aresta = no->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
        {
            if (!visitado[aresta->getTargetId()]) //verifica se o no de destino da aresta ja foi visitado
            {
                visitado[aresta->getTargetId()] = true;
                cout << "\t" << no->getId() << " " << nodesSeparator << " " << aresta->getTargetId() << endl;
                saida << "\t" << no->getId() << " " << nodesSeparator << " " << aresta->getTargetId() << "\n";
                pilha.push(aresta->getTargetId());
            }
        }
    }
    saida << "}";
}

////////////////////////////////////////////////////FECHO TRANSITIVO INDIRETO///////////////////////////////////////////////////////////////////////

//Recebe como parametro um id de um vertice x do grafo, e mostra todos as arestas do no y que pode alcançar
//o no x por um caminho direcionado com origem em y
void Graph::fechoTransitivoIndireto(int idNode, ofstream &saida)
{
    if (!this->getDirected())
    {
        cout << "Fecho Transitivo Inireto impossivel: o grafo nao eh direcionado." << endl;
        return;
    }
    // if (this->ciclo())
    // {
    //     cout << "Fecho Transitivo Direto impossivel: o grafo possui Ciclos. \n";
    //     return;
    // }

    stack<int> pilha;
    pilha.push(idNode);

    string graphType;
    string nodesSeparator;

    graphType = "digraph";
    nodesSeparator = "->";

    saida << graphType << "Fecho Transitivo Direto {\n";

    // Ate esvaziar a pilha
    while (!pilha.empty())
    {
        int topo = pilha.top(); // Recupera o no do topo da pilha
        pilha.pop();            // Remove topo da pilha

        // Laço para percorrer o grafo
        for (Node *no = this->getFirstNode(); no != nullptr; no = no->getNextNode())
        {
            // Verifica exstencia de arestas
            if (no->hasEdgeBetween(topo))
            {
                cout << "\t" << no->getId() << " " << nodesSeparator << " " << topo << endl;
                saida << "\t" << no->getId() << " " << nodesSeparator << " " << topo << "\n";
                pilha.push(no->getId());
            }
        }
    }
    saida << "}";
}

////////////////////////////////////////////////////ORDENAÇÃO TOPOLÓGICA//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Graph::ordenacaoTopologica(ofstream &saida)
{
    cout << "\n Ordenacao topologica em Grafo Aciclico Direcionado \n"
         << endl;

    if (!this->getDirected())
    {
        cout << "Ordenacao Topologica impossivel: o grafo eh nao-direcionado." << endl;
        return;
    }
    // else if (this->ciclo())
    // {
    //     cout << "Ordenacao Topologica impossível: Grafo ciclico." << endl;
    //     return;
    // }
    else
    {
        list<int> ordenacaoTopologica;
        int n = nodesCount;

        int *grausEntrada = new int[n];
        for (int i = 0; i < n; i++)
        {
            grausEntrada[i] = this->getGrauEntrada(i + 1);
        }

        int cont = 0;

        while (cont < n)
        {
            for (int i = 0; i < n; i++)
            {
                if (grausEntrada[i] == 0)
                {
                    grausEntrada[i] = -1; //simboliza que o vertice já foi adicionado na lista
                    ordenacaoTopologica.push_back(i + 1);

                    Edge *auxEdge = this->getNode(i + 1)->getFirstEdge();
                    while (auxEdge != nullptr)
                    {
                        grausEntrada[auxEdge->getIdDestino() - 1]--; //remove o vertice adicionado da lista e diminui o grau de entrada dos outrosx
                        auxEdge = auxEdge->getNextEdge();
                    }
                    cont++;
                    break;
                }
            }
        }
        saida << "Ordenacao Topologica:\n";
        cout << "Ordenacao Topologica:\n";
        for (int x : ordenacaoTopologica)
        {
            {
                saida << x << "\n";
                cout << x << "\n";
            }
        }
        delete grausEntrada;
    }
}

int Graph::getGrauEntrada(int idNode)
{
    int grauEntrada = 0;

    //cout << "id: " << idNode;

    Node *node = first_node;
    while (node != nullptr)
    {
        Edge *edge = node->getFirstEdge();
        while (edge != nullptr)
        {
            if (edge->getIdDestino() == idNode)
            {
                grauEntrada++;
                break;
            }

            edge = edge->getNextEdge();
        }

        node = node->getNextNode();
    }
    //cout << "  grau: " << grauEntrada << endl;
    return grauEntrada;
}

////////////////////////////////////////////////////BUSCA PROFUNDIDADE//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Recebe como parametro o Id de um vertice e mostra o caminhamento em profundidade a partir desse Id
void Graph::caminhamentoProfundidade(int x, ofstream &saida)
{
    cout << "\n Iniciando Caminhamento Profundidade " << endl;

    bool *verificavisitado = new bool[this->order];
    //preenche o vetor com false
    for (int i = 0; i < this->order; i++)
    {
        verificavisitado[i] = false;
    }

    string graphType;
    string nodesSeparator;
    if (this->directed)
    {
        graphType = "digraph";
        nodesSeparator = "->";
    }
    else
    {
        graphType = "graph";
        nodesSeparator = "--";
    }
    saida << graphType << " BuscaProfundidade {\n";
    cout << endl;
    cout << graphType << " BuscaProfundidade {\n";

    auxBuscaEmProfundidade(x, verificavisitado, saida, nodesSeparator);

    saida << "}";
    cout << "}";
    cout << endl;
    delete verificavisitado;
}

//Funcao auxiliar para a Busca em Profundidade
//a função recebe como parâmetro o Id de um nó (x), um vetor de controle de vertices visitados, um arquivo
//para gravar o resultado e uma string de -> ou --
// e imprime o conjunto de arestas visitadas a partir do mesmo em um percurso em profundidade indicando,
//para cada uma, se trata-se ou não de uma aresta de retorno
void Graph::auxBuscaEmProfundidade(int x, bool *verificavisitado, ofstream &saida, string nodesSeparator)
{
    verificavisitado[x] = true;
    Node *noAux = getNode(x);

    for (Edge *arestaAux = noAux->getFirstEdge(); arestaAux != nullptr; arestaAux = arestaAux->getNextEdge())
    {
        if (verificavisitado[arestaAux->getIdDestino()] == false)
        { // nao é aresta de retorno
            saida << "\t" << noAux->getId() << " " << nodesSeparator << " " << arestaAux->getIdDestino() << "\n";
            auxBuscaEmProfundidade(arestaAux->getIdDestino(), verificavisitado, saida, nodesSeparator);
            cout << "\t" << noAux->getId() << " " << nodesSeparator << " " << arestaAux->getIdDestino() << "\n";
            auxBuscaEmProfundidade(arestaAux->getIdDestino(), verificavisitado, saida, nodesSeparator);
        }
        else
        { //é aresta de retorno
            saida << "\t" << noAux->getId() << " " << nodesSeparator << " " << arestaAux->getIdDestino() << " [style=dotted];\n";
            cout << "\t" << noAux->getId() << " " << nodesSeparator << " " << arestaAux->getIdDestino() << " [style=dotted];\n";
        }
    }
}

////////////////////////////////////////////////////SUBGRAFO INDUZIDO//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Metodo que gera um subgrafo vertice induzio
//Recebe como parametro um subconjunto de ids de vertices, o tamnaho desse subconjunto e um arquivo de saida
Graph *Graph::subGrafoInduzido(int *vet, int tam, ofstream &saida)
{
    cout << "\n Iniciando Subgrafo Induzido" << endl;

    int n = this->order;
    int *vetorVerificacao = new int[n];
    int *vertices = new int[n];
    Graph *subgrafo = new Graph(tam, this->directed, this->weighted_edge, this->weighted_node);
    Node *node = nodesList->getPrimeiro();

    string graphType;
    string nodesSeparator;
    if (this->directed)
    {
        graphType = "digraph";
        nodesSeparator = "->";
    }
    else
    {
        graphType = "graph";
        nodesSeparator = "--";
    }

    saida << graphType << " SubgrafoInduzido {\n";

    for (int i = 0; i < n; ++i)
    {
        vetorVerificacao[i] = 0;
        vertices[i] = node->getId();
        node = node->getNextNode();
    }

    for (int i = 0; i < tam; ++i)
    {
        if (!nodesList->busca(vet[i])) //verifica se o elemento do subconjunto de vertices esta no grafo original
        {
            cout << "Elemento nao pertence ao grafo. Não eh possivel gerar o subGrafo induzido." << endl;

            delete vetorVerificacao;
            delete vertices;
            return nullptr;
        }
        if (subgrafo->nodesList->busca(vet[i]) == false) //verifica se o elemento do subconjunto de vertices ja esta no subgrafo
        {
            subgrafo->insertNode(vet[i], 0, -1); //se nao estiver, insere no subgrafo
        }

        int ind = retornaIndice(vertices, n, vet[i]);
        if (vetorVerificacao[ind] == 0)
        {
            vetorVerificacao[ind] = 1;
        }
        else
        {
            cout << "Elementos repetidos no vetor." << endl;
            delete vetorVerificacao;
            delete vertices;
            return nullptr;
        }

        Node *v = nodesList->retornaVertice(vet[i]);
        Edge *edge;
        for (int j = 0; j < tam; j++)
        {
            if (vet[i] != vet[j])
            {
                bool aux = v->searchEdge(vet[j]);
                if (aux == true)
                {
                    if (subgrafo->hasEdgeBetween(vet[i], vet[j]) == false)
                    {
                        edge = v->getFirstEdge();
                        while (edge != nullptr)
                        {
                            if (edge->getIdDestino() == vet[j]) //
                            {
                                subgrafo->insertEdge(vet[i], vet[j], edge->getWeight());
                                saida << "\t" << vet[i] << " " << nodesSeparator << " " << vet[j] << "\n";
                            }
                            edge = edge->getNextEdge();
                        }
                    }
                }
            }
        }
    }

    saida << "}";

    subgrafo->imprimeGrafo();

    delete vetorVerificacao;
    delete vertices;

    return subgrafo;
}

int Graph::retornaIndice(int *vet, int tam, int val)
{
    for (int i = 0; i < tam; i++)
    {
        if (vet[i] == val)
            return i;
    }
    cout << "Indice nao encontrado!"
         << " val=" << val << endl;
    exit(1);
}

////////////////////////////////////////////////////ALGORITMO DE KRUSKAL/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///algoritmo de Kruskal que encontra a Árvore Geradora Mínima
//Recebe como parametros um subgrafo induzido por vertices e o arquivo de saida para gravar o resultado
void Graph::kruskal(Graph *subgrafo, ofstream &saida)
{
    cout << "\n Iniciando algoritmo de Kruskal" << endl;

    //vetor que armazena as arestas do grafo
    vector<Par> vetEdges;
    //ordena a lista com as arestas em ordem crescente
    sort(subgrafo->arestas.begin(), subgrafo->arestas.end());

    //Cria a subarvore, onde cada vertice sera uma arvore na floresta, ou seja, sera um no isolado
    int *subarvores = new int[subgrafo->getNodeCount()];

    // A função da biblioteca C memset(str, c, n) copia o caracter c (um unsigned char)
    //para os n primeiros caracteres da string apontada por str. (seta todo mundo para -1)
    memset(subarvores, -1, sizeof(int) * subgrafo->getNodeCount());

    for (int i = 0; i < subgrafo->arestas.size(); i++)
    {
        int u = buscar(subarvores, subgrafo->arestas[i].u->getId());
        int v = buscar(subarvores, subgrafo->arestas[i].v->getId());

        // se forem diferentes é porque não formam ciclo, ou seja, nao estao na mesma subarvore
        //entao podemos incluir a aresta no vetor, e depois marcar que as duas subarvores são uma
        //única subarvore
        if (u != v)
        {
            vetEdges.push_back(arestas[i]);
            unir(subarvores, u, v); // faz a união
        }
    }

    string graphType;
    string nodesSeparator;
    if (this->directed)
    {
        graphType = "digraph";
        nodesSeparator = "->";
    }
    else
    {
        graphType = "graph";
        nodesSeparator = "--";
    }

    saida << graphType << " Kruskal {\n";
    const string quote = "\"";

    int sizeVetEdge = vetEdges.size();
    for (int i = 0; i < sizeVetEdge; i++)
    {
        int v1 = vetEdges[i].u->getId();
        int v2 = vetEdges[i].v->getId();
        cout << v1 << " " << v2 << endl;
        saida << "\t" << v1 << " " << nodesSeparator << " "
              << v2 << " [label" << quote << vetEdges[i].weight << quote << "]\n";
    }

    saida << "}";
}

// Método utilizado para auxiliar o algoritmo de Kruskal
//Recebe como parametros um vetor de subarvores e um id de um vertice
//Ele busca nas subarvores o elemento i
int Graph::buscar(int subarvores[], int i)
{
    if (subarvores[i] == -1)
        return i;
    return buscar(subarvores, subarvores[i]);
}

// Método para unir dois subconjuntos em um único subconjunto
//Recebe como parametros um vetor de subarvores e dois ids de vertices que deseja-se unir
void Graph::unir(int subarvores[], int u, int v)
{
    int u_set = buscar(subarvores, u);
    int v_set = buscar(subarvores, v);
    subarvores[u_set] = v_set;
}

////////////////////////////////////////////////////ALGORITMO DE PRIM/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Estrutura auxiliar para ajudar armazenar as arestas do grafo
class Pares
{
public:
    int origem;
    int destino;
    int peso;
};

///algoritmo de Prim que encontra a Árvore Geradora Mínima para grafos orientados e nao orientados
//Recebe como parametros um subgrafo induzido por vertices e o arquivo de saida para gravar o resultado
void Graph::primMST(Graph *subgrafo, ofstream &saida)
{
    cout << "\n Iniciando o algoritmo de Prim" << endl;

    int menorPeso = INF;
    int cont = 0, somatorioPesos = 0, qtArestaSolucao = 0, n = subgrafo->getOrder();
    int **custo = new int *[n];
    for (int i = 0; i < n; i++)
        custo[i] = new int[n];
    int *prox = new int[n];
    int *aux = new int[n];
    Node *no;
    Edge *menorAresta, *aresta;
    Pares *solucao = new Pares[subgrafo->getNumberEdges()];
    Pares auxPares;

    //Laco para percorrer as arestas do grafo e preencher a matriz de custo entre os vertices
    for (int id_o = 0; id_o < n; id_o++)
    {
        for (int id_a = 0; id_a < n; id_a++)
        {
            if (id_o == id_a)
                custo[id_o][id_a] = 0;
            else
            { // Pegar um  vertice  para percorrer as Arestas dele
                no = subgrafo->getNode(id_o + 1);
                // Pegar aresta entre o vertice de origem do passo anterior e o vertice destino
                aresta = no->hasEdgeBetween(id_a + 1);
                // Verificando se existe a aresta
                if (aresta != nullptr) // Se existe preenche a distancia da origem para o destino sendo o peso
                    custo[id_o][id_a] = aresta->getWeight();
                else // Se nao existe aresta a distancia recebe infinito
                    custo[id_o][id_a] = INF;
            }
        }
    }
    //imprime na tela a matriz de custo entre os vertices
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //         cout << custo[i][j] << "   ";
    //     cout << endl;
    // }

    //Laço para encontrar a aresta de menor peso do grafo
    for (no = subgrafo->getFirstNode(); no != nullptr; no = no->getNextNode())
    {
        for (aresta = no->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
        {
            if (aresta->getWeight() < menorPeso)
            {
                menorPeso = aresta->getWeight();
                menorAresta = aresta;
            }
        }
    }

    //A aresta de menor peso entra na solucao
    auxPares.destino = menorAresta->getIdDestino();
    auxPares.origem = menorAresta->getIdOrigem();
    auxPares.peso = menorAresta->getWeight();
    solucao[qtArestaSolucao] = auxPares;
    qtArestaSolucao++;

    // cout << "Aresta menor : " << auxPair[0].destino << auxPair[0].origem << auxPair[0].peso << endl;
    //   cout << custo[0][menorAresta->getIdOrigem() - 1] << endl;
    //   cout << custo[0][menorAresta->getIdDestino() - 1] << endl;

    //Laço para fazer a inicializacao dos vetores prox e aux
    for (int i = 0; i < subgrafo->getOrder(); i++)
    {

        if (custo[i][menorAresta->getIdOrigem() - 1] < custo[i][menorAresta->getIdDestino() - 1])
        {
            prox[i] = menorAresta->getIdOrigem();
            aux[i] = custo[i][menorAresta->getIdOrigem() - 1];
        }
        else
        {
            prox[i] = menorAresta->getIdDestino();
            aux[i] = custo[i][menorAresta->getIdDestino() - 1];
        }
    }

    prox[menorAresta->getIdOrigem() - 1] = 0;
    prox[menorAresta->getIdDestino() - 1] = 0;

    // for (int i = 0; i < n; i++)
    // {
    //     cout << prox[i] << "  ";
    // }
    // cout << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     cout << aux[i] << "  ";
    // }

    while (cont < n - 2)
    {
        int j = auxPrim(aux, prox, n);
        //cout << "J = " << j << endl;
        auxPares.destino = j;
        auxPares.origem = prox[j - 1];
        auxPares.peso = aux[j - 1];
        solucao[qtArestaSolucao] = auxPares;
        qtArestaSolucao++;
        prox[j - 1] = 0;

        for (int i = 0; i < n; i++)
        {
            //cout << endl;
            //cout << prox[i] << " != 0 && " << custo[i][prox[i] - 1] << " > " << custo[i][j - 1] << endl;
            if (prox[i] != 0 && custo[i][prox[i] - 1] > custo[i][j - 1])
            {
                prox[i] = j;
                no = getNode(j);
                aresta = no->hasEdgeBetween(i + 1);
                aux[i] = aresta->getWeight();
            }
        }
        // cout << endl;
        // for (int i = 0; i < n; i++)
        //     cout << prox[i] << "    ";

        // cout << endl;
        // for (int i = 0; i < n; i++)
        //     cout << aux[i] << "    ";

        cont = cont + 1;
    }

    string graphType;
    string nodesSeparator;
    if (subgrafo->getDirected())
    {
        graphType = "digraph";
        nodesSeparator = "->";
    }
    else
    {
        graphType = "graph";
        nodesSeparator = "--";
    }

    saida << graphType << " Prim {\n";
    const string quote = "\"";

    for (int l = 0; l < qtArestaSolucao; l++)
    {
        cout << "[" << solucao[l].origem << " -> " << solucao[l].destino << "] - "
             << solucao[l].peso << endl;
        saida << "\t" << solucao[l].origem << " " << nodesSeparator << " "
              << solucao[l].destino << " [label" << quote << solucao[l].peso
              << quote << "]\n";
        somatorioPesos += solucao[l].peso;
    }
    cout << endl
         << "Somatorio dos Pesos: " << somatorioPesos << endl;

    saida << "}";
}
int Graph::auxPrim(int *aux, int *prox, int n)
{
    int menor = INF, j;
    for (int i = 0; i < n; i++)
    {
        if (prox[i] != 0 && aux[i] <= menor)
        {
            menor = aux[i];
            j = i + 1;
        }
    }
    return j;
}

////////////////////////////////////////////////////ALGORITMO DE FLOYD/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Algoritmo de caminho minimo Floyd para grafos orientados e tambem nao orientados
//Recebe como parametros os Ids dos vertices de origem e destino para que se possa
//encontrar o valor do caminho minimo entre vertice de origem e vertice de destino, e o arquivo
// de saida onde sera gravado o resultado
void Graph::Floyd(int origem, int destino, ofstream &saida)
{

    int n = this->getOrder() + 1, aux;
    int **custo = new int *[n];
    int **caminho = new int *[n];
    Node *no;
    Edge *aresta;
    for (int i = 1; i < n; i++)
    {
        custo[i] = new int[n];
        caminho[i] = new int[n];
    }

    //Laco para percorrer as arestas do grafo e preencher a matriz de custo entre os vertices
    for (int id_o = 1; id_o < n; id_o++)
    {
        for (int id_a = 1; id_a < n; id_a++)
        {
            if (id_o == id_a)
            {
                custo[id_o][id_a] = 0;
                caminho[id_o][id_a] = 0;
            }

            else
            { // Pegar um  vertice  para percorrer as Arestas dele
                no = getNode(id_o);
                // Pegar aresta entre o vertice de origem do passo anterior e o vertice destino
                aresta = no->hasEdgeBetween(id_a);
                // Verificando se existe a aresta
                if (aresta != nullptr) // Se existe preenche a distancia da origem para o destino sendo o peso
                {
                    custo[id_o][id_a] = aresta->getWeight();
                    caminho[id_o][id_a] = id_o;
                }

                else // Se nao existe aresta a distancia recebe infinito
                {
                    custo[id_o][id_a] = INF;
                    caminho[id_o][id_a] = -1;
                }
            }
        }
    }

    //imprime na tela a matriz de custo entre os vertices
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
            cout << custo[i][j] << "   ";
        cout << endl;
    }

    //laco para fazer a atualizacao dos pesos da matriz de custo dos arcos
    for (aux = 1; aux < n; aux++)
    {
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            { //a matriz em cada iteracao, vai ser o minimo entre a posicao a matriz anterior
                // se o vertice aux estiver no caminho mais curto de i para j, deve-se atualizar a matriz na posicao[i][j]
                if (custo[i][j] > custo[i][aux] + custo[aux][j])
                {
                    custo[i][j] = custo[i][aux] + custo[aux][j];
                    caminho[i][j] = caminho[aux][j];
                }
            }
        }
    }
    // cout << endl;
    // for (int i = 1; i < n; i++)
    // {
    //     for (int j = 1; j < n; j++)
    //         cout << custo[i][j] << "   ";
    //     cout << endl;
    // }

    string graphType;
    string nodesSeparator;
    if (this->getDirected())
    {
        graphType = "digraph";
        nodesSeparator = "->";
    }
    else
    {
        graphType = "graph";
        nodesSeparator = "--";
    }
    cout << endl;
    saida << "O caminho mais curto entre " << origem << " e " << destino << " tem comprimento: " << custo[origem][destino] << "\n";
    cout << "O caminho mais curto entre " << origem << " e " << destino << " tem comprimento: " << custo[origem][destino] << endl;
    saida << graphType << " Floyd {\n";
    const string quote = "\"";

    // cout << endl;
    // for (int i = 1; i < n; i++)
    // {
    //     for (int j = 1; j < n; j++)
    //         cout << caminho[i][j] << "   ";
    //     cout << endl;
    // }

    cout << endl;
    vector<int> vet;
    vet.push_back(origem);
    printPath(caminho, origem, destino, vet);
    vet.push_back(destino);

    for (int i = 1; i < vet.size(); i++)
    {
        cout << "\t"
             << "[" << vet[i - 1] << " " << nodesSeparator << " " << vet[i] << "]\n ";
        saida << "\t" << vet[i - 1] << " " << nodesSeparator << " "
              << vet[i] << "\n";
    }
    saida << "}";
}

//Funcao recursiva para impressao do caminho do vertice de origem ao vertice de destino
void Graph::printPath(int **path, int v, int u, vector<int> &vet)
{
    if (path[v][u] == v)
    {
        return;
    }

    printPath(path, v, path[v][u], vet);
    vet.push_back(path[v][u]);
    //cout << path[v][u] << " ";
}

////////////////////////////////////////////////////ALGORITMO DE DIJKSTRA/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Algoritmo que encontra o caminho minimo de um grafo atraves do algoritmo de Dijkstra
// Recebe o id de dois vertices origem e destino e mostra o caminho minimo entre eles
void Graph::dijkstra(int origem, int destino, ofstream &saida)
{
    if (!this->searchNode(origem) || !this->searchNode(destino))
    {
        cout << endl
             << "Ids dos vertices nao pertencem ao grafo" << endl;
        return;
    }

    cout << endl
         << "Iniciando algoritmo de Dijkstra" << endl;

    int i, k, min, aux;
    //vetor para determinar se um vertice ja foi visitado
    bool *visitados = new bool[this->order + 1];
    // vetor de distâncias
    int *dist = new int[this->order + 1];
    // Vetor para guardar o caminho mais curto entre os vertices origem e destino
    int *caminho = new int[this->order + 1];

    //inicializando variaveis
    for (int i = 0; i < this->order + 1; i++)
    {
        dist[i] = INF;
        visitados[i] = false;
        caminho[i] = origem;
    }

    // distancia do vertice de origem para ele mesmo = 0,
    //Vertice de origem fica como visitado no vetor de visitados
    dist[origem] = 0;
    visitados[origem] = true;
    Node *no = this->getNode(origem);

    //Laço para percorrer as arestas dos vertices adijacentes ao no Origem e armazenar seus custos.
    // Caso o vertice nao seja adjacente , ficara com o valor de INF
    for (Edge *aresta = no->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
    {
        dist[aresta->getIdDestino()] = aresta->getWeight();
    }

    // TESTES PARA VER OS VETORES
    //cout << "Matriz distancia e visitados " << endl;
    // for ( i = 0; i < this->order + 1; i++)
    //     cout << dist[i] << "  ";
    // cout << endl;
    // for ( i = 0; i < this->order + 1; i++)
    //     cout << visitados[i] << "  ";

    // Percorre todos os vertices do grafo
    for (i = 0; i < this->order + 1; i++)
    {
        min = INF;
        for (int i = 0; i < this->order + 1; i++)
        {
            //verifica se o vertice i ja foi visitado e se ele possui custo menor que o valor atual da variavel min
            if (visitados[i] == false && dist[i] <= min)
            {
                min = dist[i]; //se seim, min atualiza o seu valor
                aux = i;       //aux guarda o indice do vertice com menor custo
            }
        }
        if (aux == destino)
            continue;
        // atualiza o vertice de menor custo no vetor de visitados como visitado
        visitados[aux] = true;

        for (k = 0; k < this->order + 1; k++)
        {
            Node *atual = getNode(aux);
            //Se o vertice nao foi visitdao, se existe aresta entre o aux e k, e o custo de k nao é INF
            //vamos atualizar o custo
            if (!visitados[k] && dist[aux] != INF && atual->temEdgeBetween(k))
            {
                Edge *arestaEntre = atual->hasEdgeBetween(k);
                // Atualiza o valor da distancia caso o novo calculo seja menor do que o anterior.

                if (dist[aux] + arestaEntre->getWeight() < dist[k])
                {
                    dist[k] = dist[aux] + arestaEntre->getWeight(); //atualiza o novo custo
                    caminho[k] = aux;                               //atualiza o caminho
                }
            }
        }
    }

    string graphType;
    string nodesSeparator;
    if (this->getDirected())
    {
        graphType = "digraph";
        nodesSeparator = "->";
    }
    else
    {
        graphType = "graph";
        nodesSeparator = "--";
    }

    saida << "O caminho mais curto entre " << origem << " e " << destino << " tem comprimento: " << dist[destino] << "\n";
    cout << "O caminho mais curto entre " << origem << " e " << destino << " tem comprimento: " << dist[destino] << endl;
    saida << graphType << " Dijkstra {\n";
    const string quote = "\"";

    for (int l = destino; l != origem; l = caminho[l])
    {
        aux = l;
        cout << "\t"
             << "[" << caminho[l] << " " << nodesSeparator << " " << aux << "]\n ";
        saida << "\t" << caminho[l] << " " << nodesSeparator << " "
              << aux << "\n";
    }
    saida << "}";
}

float Graph::greed(ofstream &saida)
{
    clock_t tInicio, tFim, tDecorrido;
    tInicio = clock();

    std::vector<Edge> vetEdges = this->arestasVet;
    sort(vetEdges.begin(), vetEdges.end());
    std::vector<Edge> T;
    int somaPesos = 0, num = this->number_Groups;
    int *subArvore = new int(this->order);
    memset(subArvore, -1, sizeof(int) * this->order);
    int *vGroup = new int(number_Groups);
    // A função da biblioteca C memset(str, c, n) copia o caracter c (um unsigned char)
    //para os n primeiros caracteres da string apontada por str. (seta todo mundo para 0)
    memset(vGroup, 0, sizeof(int) * number_Groups);

    while (num > 1)
    {
        Edge edge = vetEdges.front();
        vetEdges.erase(vetEdges.begin());

        int u = buscar(subArvore, edge.getIdOrigem());
        int v = buscar(subArvore, edge.getIdDestino());

        // se forem diferentes é porque não formam ciclo, ou seja, nao estao na mesma subarvore
        //entao podemos incluir a aresta no vetor, e depois marcar que as duas subarvores são uma
        //única subarvore
        if (u != v)
        {
            Node *nodeU = getNode(edge.getIdOrigem());
            Node *nodeV = getNode(edge.getIdDestino());
            if (nodeU != nullptr && nodeV != nullptr)
            {
                int gu = nodeU->getGroupId();
                int gv = nodeV->getGroupId();

                if ((vGroup[gu - 1] == nodeU->getId() || vGroup[gu - 1] == 0) && (vGroup[gv - 1] == nodeV->getId() || vGroup[gv - 1] == 0))
                {
                    T.push_back(edge);
                    unir(subArvore, u, v); // faz a união
                    somaPesos += edge.getWeight();

                    num--;
                    if (vGroup[gu - 1] == 0)
                    {
                        vGroup[gu - 1] = nodeU->getId();
                    }
                    if (vGroup[gv - 1] == 0)
                    {
                        vGroup[gv - 1] = nodeV->getId();
                    }
                }
            }
        }
    }
    tFim = clock();
    tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));

    saida << "Tempo: " << tDecorrido << "ms \n";
    saida << "Total Peso: " << somaPesos << "\n";
}
float Graph::greedRandom()
{
}
float Graph::greedRactiveRandom()
{
}
