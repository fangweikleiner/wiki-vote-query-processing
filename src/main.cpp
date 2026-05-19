#include <iostream>
#include <string>
#include "DirectedGraph.hpp"

void printSet(const DirectedGraph::NeighborSet& neighbors) {
    for (DirectedGraph::NodeId node : neighbors) {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::string filename = "data/Wiki-Vote.txt";

    if (argc >= 2) {
        filename = argv[1];
    }

    DirectedGraph graph;

    try {
        graph.loadFromFile(filename);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    graph.printSummary();

    std::cout << std::endl;

    // Example query 1: outgoing neighbors
    DirectedGraph::NodeId queryNode = 30;

    std::cout << "Outgoing neighbors of node " << queryNode << ":" << std::endl;
    printSet(graph.getOutgoingNeighbors(queryNode));

    std::cout << "Out-degree of node " << queryNode << ": "
              << graph.getOutDegree(queryNode) << std::endl;

    std::cout << std::endl;

    // Example query 2: incoming neighbors
    queryNode = 1412;

    std::cout << "Incoming neighbors of node " << queryNode << ":" << std::endl;
    printSet(graph.getIncomingNeighbors(queryNode));

    std::cout << "In-degree of node " << queryNode << ": "
              << graph.getInDegree(queryNode) << std::endl;

    std::cout << std::endl;

    // Example query 3: edge existence
    int fromNode = 30;
    int toNode = 1412;

    std::cout << "Checking edge " << fromNode << " -> " << toNode << ": ";

    if (graph.hasEdge(fromNode, toNode)) {
        std::cout << "exists" << std::endl;
    } else {
        std::cout << "does not exist" << std::endl;
    }

    return 0;
}

