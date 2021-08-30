#include <iostream>
#include "Edge.h"

using namespace std;

// Constructor
Edge::Edge()
{
}

Edge::Edge(int target_id, int id)
{

    this->target_id = target_id;
    this->next_edge = nullptr;
    this->weight = 0;
    this->origem = id;
    this->destino = target_id;
}
Edge::Edge(int target_id, int id, float weight)
{

    this->target_id = target_id;
    this->next_edge = nullptr;
    this->weight = weight;
    this->origem = id;
    this->destino = target_id;
}

// Destructor
Edge::~Edge()
{

    if (this->next_edge != nullptr)
    {
        delete this->next_edge;
        this->next_edge = nullptr;
    }
}

// Getters
int Edge::getTargetId()
{

    return this->target_id;
}

Edge *Edge::getNextEdge()
{

    return this->next_edge;
}

float Edge::getWeight()
{

    return this->weight;
}

int Edge::getIdOrigem()
{
    return this->origem;
}

int Edge::getIdDestino()
{
    return this->destino;
}
// Setters
void Edge::setNextEdge(Edge *edge)
{

    this->next_edge = edge;
}

void Edge::setWeight(float weight)
{

    this->weight = weight;
}

void Edge::setOrigem(int id_origem)
{
    this->origem = id_origem;
}

void Edge::setDestino(int id_destino)
{
    this->destino = id_destino;
}