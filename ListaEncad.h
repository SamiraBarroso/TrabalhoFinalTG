#ifndef LISTAENCAD_H_INCLUDED
#define LISTAENCAD_H_INCLUDED

#include "Node.h"

class ListaEncad
{
public:
    ListaEncad();
    ~ListaEncad();
    bool busca(int val);
    void insereInicio(int val);
    void insereFinal(Node *node);
    void imprime();
    void deletaLista();
    int tamLista();
    Node* getPrimeiro();
    Node* retornaVertice(int v);
private:
    Node* primeiro;
    Node* ultimo;
};

#endif 
