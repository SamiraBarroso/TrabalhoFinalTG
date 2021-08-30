#include<iostream>
#include "ListaEncad.h"

using namespace std;

ListaEncad::ListaEncad()
{
    primeiro = NULL;
    ultimo = NULL;
}

bool ListaEncad::busca(int val)
{
    Node* p;
    for(p = primeiro; p != NULL; p = p->getNextNode())
    {
        if(p->getId() == val)
            return true;
    }
    return false;
}

void ListaEncad::insereInicio(int val)
{
    Node *p = new Node(val); // cria Node apontado por p
    p->setNextNode(primeiro); // preenche proximo
    primeiro = p; // Node apontado por p passa
// a ser o primeiro da lista
}
void ListaEncad::insereFinal(Node *node)
{
    node->setNextNode(NULL);
    if(primeiro == NULL)
    {
        primeiro = node;
        ultimo = node;
    }else
    {
        ultimo->setNextNode(node);
        ultimo = node;
    }
}
void ListaEncad::imprime()
{
    Node* p = primeiro;
    while(p != NULL)
    {
       cout<<p->getId();
       if(p->getNextNode() != NULL)
            cout<<"->";
       p = p->getNextNode();
    }
}
int ListaEncad::tamLista()
{
  int conte = 0;
  Node *p = primeiro;
  while(p!=NULL)
  {
    conte++;
    p = p->getNextNode();
  }
  return conte;
}
void ListaEncad::deletaLista()
{
    Node *p = primeiro;
    while(p != NULL)
    {
        Node *t = p->getNextNode();
        delete p;
        p = t;
    }
}
ListaEncad::~ListaEncad()
{
    Node *p = primeiro;
    while(p != NULL)
    {
        Node *t = p->getNextNode();
        delete p;
        p = t;
    }
}
Node* ListaEncad::getPrimeiro(){
    return this->primeiro;
}

Node* ListaEncad::retornaVertice(int v)
{
    Node* a = primeiro;
    while(a!=NULL)
    {
        if(a->getId() == v)
            return a;
        a = a->getNextNode();
    }
    cout<<"Vertice não encontrado!!"<<endl;
    exit(1);
}
