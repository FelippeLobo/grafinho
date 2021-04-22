#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
    for (size_t i = 0; i < order; i++)
    {
        insertNode(i);
    }
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

list<list<int>> Graph::getListaAdjacencia()
{

    return this->adjacencia;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::insertNode(int id)
{
    Node *novoNo = new Node(id);

    if (this->first_node == nullptr)
    {

        this->first_node = novoNo;
        this->last_node = novoNo;
    }
    else
    {

        if (this->searchNode(id) == false)
        {
            this->last_node->setNextNode(novoNo);
            this->last_node = novoNo;
        }
    }
    order++;
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    if (searchNode(id))
    {
        Node *node = getNode(id);

        node->insertEdge(target_id, weight);
    }
}

void Graph::removeNode(int id)
{

    if (this->first_node != nullptr)
    {

        if (this->searchNode(id))
        {

            if (this->first_node->getId() == id)
            {

                Node *atual = this->first_node;

                atual->removeAllEdges();

                this->first_node = atual->getNextNode();

                delete atual;
            }
            else
            {

                Node *atual = this->first_node;
                Node *anterior = nullptr;

                while (atual->getId() != id)
                {
                    anterior = atual;
                    atual = atual->getNextNode();
                }

                anterior->setNextNode(atual->getNextNode());

                if (this->last_node->getId() == id)
                {

                    this->last_node = anterior;
                }

                atual->removeAllEdges();

                delete atual;
            }
        }
    }
}

bool Graph::searchNode(int id)
{
    if (this->first_node != nullptr)
    {
        Node *node = this->first_node;
        while (node->getNextNode() != nullptr)
        {

            if (node->getId() == id)
            {
                return true;
            }

            node = node->getNextNode();
        }
        if (node->getId() == id)
        {
            return true;
        }

        return false;
    }

    return false;
}

Node *Graph::getNode(int id)
{
    if (searchNode(id))
    {
        Node *node = this->first_node;

        while (node->getNextNode() != nullptr)
        {
            if (node->getId() == id)
            {
                return node;
            }

            node = node->getNextNode();
        }
        if (node->getId() == id)
        {
            return node;
        }

        return nullptr;
    }

    return nullptr;
}

void Graph::carregarListaAdjacencia()
{

    for (int i = 0; i < this->order; i++)
    {
        list<int> adjList;
        adjacencia.push_back(adjList);
    }

    Node *node = this->first_node;

    list<list<int>>::iterator it;
    for (it = adjacencia.begin(); it != adjacencia.end() && node != nullptr; ++it)
    {
        Edge *edge = node->getFirstEdge();

        while (edge != nullptr)
        {
            it->push_back(edge->getTargetId());
            edge = edge->getNextEdge();
        }

        node = node->getNextNode();
    }
}

void Graph::imprimeAdjacencias()
{
    list<list<int>>::iterator l;
    int j = 0;
    for (l = adjacencia.begin(); l != adjacencia.end(); ++l)
    {
        cout << j << " : ";

        list<int>::iterator i;
        for (i = l->begin(); i != l->end(); ++i)
        {
            cout << *i << " // ";
        }
        cout << endl;
        j++;
    }
}

float Graph::verifyEdgeWeight(int sourceID, int targetID)
{

    if (searchNode(sourceID))
    {
        Node *node = getNode(sourceID);
        if (node->hasEdgeBetween(targetID))
        {
            Edge *edge = node->getFirstEdge();

            while (edge != nullptr)
            {
                if (edge->getTargetId() == targetID)
                {
                    return edge->getWeight();
                }

                edge = edge->getNextEdge();
            }
        }
        else
        {
            cout << endl
                 << "Error: doesn't exist edge between this nodes." << endl;
        }
    }
    else
    {
        cout << endl
             << "Error: that's node doesn't exist." << endl;
    }
    return -1;
}
//Function that prints a set of edges belongs breadth tree

// void Graph::breadthFirstSearch(ofstream &output_file)
// {
// }

// float Graph::floydMarshall(int idSource, int idTarget)
// {
// }

// float Graph::dijkstra(int idSource, int idTarget)
// {
// }

// //function that prints a topological sorting
// void topologicalSorting()
// {
// }

// void breadthFirstSearch(ofstream &output_file)
// {
// }
// Graph *getVertexInduced(int *listIdNodes)
// {
// }

// Graph *agmKuskal()
// {
// }
// Graph *agmPrim()
// {
// }
