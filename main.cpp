#include "helpers.h"
#include "graph.h"
#include <string>
#include <iostream>
#define filename "dataset.txt"
using namespace std;
int main()
{
    Graph g(filename);
    while (1)
    {
        int input;
        prinMenu();
        cin >> input;

        switch (input)
        {
        case 16:
            return 0;
            break;
        case 1:
            g.getNoOfNodes();
            break;
        case 2:
            g.getNoOfEdges();
            break;
        case 3:
            g.getNoOfSourceNodes();
            break;
        case 4:
            g.getNoOfSinkNodes();
            break;
        case 5:
            g.getNoOfIsolatedNodes();
            break;
        case 6:
            g.getNoOfBridgesdEdges();
            break;
        case 7:
            g.getNoOfAPNodes();
            break;
        case 8:
            g.getShortestPathDist();
            break;
        case 9:
            g.getDiameterOfGraph();
            break;
        case 10:
            g.getInDegreeDist();
            break;
        case 11:
            g.getOutDegreeDist();
            break;
        case 12:
            g.getMaxSccOfGraph();
            break;
        case 13:
            g.getSccDist();
            break;
        case 14:
            g.getMaxWccOfGraph();
            break;
        case 15:
            g.getWccDist();
            break;

        default:
            break;
        }

        string i;
        printf("press any key then enter to go back to menu\n");
        cin >> i;
    }

    return 0;
}