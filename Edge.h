/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED
#include <iostream>
using namespace std;

// Definition of the Edge class
class Edge
{
    // Attributes
private:
    int target_id;
    Edge *next_edge;
    float weight;
    int origem;
    int destino;

public:
    // Constructor
    Edge();
    Edge(int target_id, int id);
    Edge(int target_id, int id, float weight);
    // Destructor
    ~Edge();
    // Getters
    int getTargetId();
    Edge *getNextEdge();
    float getWeight();

    int getIdOrigem();
    int getIdDestino();

    // Setters
    void setNextEdge(Edge *edge);
    void setWeight(float weight);
    void setOrigem(int id_origem);
    void setDestino(int id_destino);
};

#endif // EDGE_H_INCLUDED