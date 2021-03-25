#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Grafo/Graph.h"
#include "Grafo/Node.h"

int main()
{
    Graph *graph = new Graph(4, false, true, false);
    
    graph->insertNode(1);
    graph->insertNode(2);
    graph->insertNode(3);
    graph->insertNode(4);

    graph->insertEdge(1,2,1);
    graph->insertEdge(2,3,2);
    graph->insertEdge(3,2,3);   
    graph->insertEdge(4,1,4);
 
    graph->removeNode(4);

    cout << graph->getFirstNode()->getId() << endl;
    cout << graph->getLastNode()->getId() << endl;
    cout << graph->searchNode(4); 

}