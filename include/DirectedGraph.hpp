#ifndef DIRECTED_GRAPH_HPP
#define DIRECTED_GRAPH_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

class DirectedGraph {
public:
    using NodeId = int;
    using NeighborSet = std::unordered_set<NodeId>;

private:
    // Hash table 1:
    // key   = FromNodeId
    // value = set of ToNodeIds
    std::unordered_map<NodeId, NeighborSet> fromIndex;

    // Hash table 2:
    // key   = ToNodeId
    // value = set of FromNodeIds
    std::unordered_map<NodeId, NeighborSet> toIndex;

    std::size_t edgeCount = 0;

public:
    DirectedGraph() = default;

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Error: cannot open file " + filename);
        }

        std::string line;

        while (std::getline(file, line)) {
            // Skip empty lines
            if (line.empty()) {
                continue;
            }

            // Skip comment/header lines beginning with '#'
            if (line[0] == '#') {
                continue;
            }

            std::istringstream iss(line);
            NodeId fromNode;
            NodeId toNode;

            if (!(iss >> fromNode >> toNode)) {
                continue;
            }

            addEdge(fromNode, toNode);
        }

        file.close();
    }

    void addEdge(NodeId fromNode, NodeId toNode) {
        // Insert into outgoing index
        auto insertedOut = fromIndex[fromNode].insert(toNode);

        // If this edge was newly inserted, also update incoming index
        if (insertedOut.second) {
            toIndex[toNode].insert(fromNode);
            edgeCount++;
        }
    }

    const NeighborSet& getOutgoingNeighbors(NodeId node) const {
        static const NeighborSet emptySet;

        auto it = fromIndex.find(node);
        if (it == fromIndex.end()) {
            return emptySet;
        }

        return it->second;
    }

    const NeighborSet& getIncomingNeighbors(NodeId node) const {
        static const NeighborSet emptySet;

        auto it = toIndex.find(node);
        if (it == toIndex.end()) {
            return emptySet;
        }

        return it->second;
    }

    bool hasEdge(NodeId fromNode, NodeId toNode) const {
        auto it = fromIndex.find(fromNode);

        if (it == fromIndex.end()) {
            return false;
        }

        return it->second.find(toNode) != it->second.end();
    }

    std::size_t getOutDegree(NodeId node) const {
        auto it = fromIndex.find(node);

        if (it == fromIndex.end()) {
            return 0;
        }

        return it->second.size();
    }

    std::size_t getInDegree(NodeId node) const {
        auto it = toIndex.find(node);

        if (it == toIndex.end()) {
            return 0;
        }

        return it->second.size();
    }

    std::size_t getEdgeCount() const {
        return edgeCount;
    }

    std::size_t getNumberOfNodes() const {
        std::unordered_set<NodeId> nodes;

        for (const auto& pair : fromIndex) {
            nodes.insert(pair.first);

            for (NodeId neighbor : pair.second) {
                nodes.insert(neighbor);
            }
        }

        for (const auto& pair : toIndex) {
            nodes.insert(pair.first);

            for (NodeId neighbor : pair.second) {
                nodes.insert(neighbor);
            }
        }

        return nodes.size();
    }

    void printSummary() const {
        std::cout << "Graph summary" << std::endl;
        std::cout << "-------------" << std::endl;
        std::cout << "Number of nodes: " << getNumberOfNodes() << std::endl;
        std::cout << "Number of edges: " << getEdgeCount() << std::endl;
        std::cout << "Number of FromNodeId keys: " << fromIndex.size() << std::endl;
        std::cout << "Number of ToNodeId keys: " << toIndex.size() << std::endl;
    }
};

#endif

