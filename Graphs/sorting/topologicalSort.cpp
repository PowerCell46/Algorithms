#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <queue>


class Graph {
private:
    std::vector<std::vector<unsigned int>> matrix;

    void increaseMatrixRows(const unsigned int newSize) {
        const unsigned int numberOfNewRows = newSize - this->matrix.size();

        for (unsigned int i = 0; i < numberOfNewRows; ++i) {
            this->matrix.emplace_back();
        }
    }

public:
    Graph() : matrix() {}

    explicit Graph(const std::string& relationships) {
        std::istringstream strStream{relationships};
        std::string currentRelationship;

        while (std::getline(strStream, currentRelationship, ';')) { // Split by ;
            std::istringstream currentRelationshipStream{currentRelationship};
            std::string firstNodeStr, secondNodeStr;

            std::getline(currentRelationshipStream, firstNodeStr, '-'); // Split by -
            std::getline(currentRelationshipStream, secondNodeStr, '-'); // Split by -

            unsigned int firstNode = std::stoul(firstNodeStr);
            unsigned int secondNode = std::stoul(secondNodeStr);
            addRelationship(firstNode, secondNode);
        }
    }

    void addRelationship(const unsigned int node1, const unsigned int node2) {
        if (node1 == node2)
            throw std::invalid_argument("Cannot add relationship between the same node.");

        const unsigned int biggerIndexNode = node1 > node2 ? node1 : node2;

        if (this->matrix.size() < biggerIndexNode + 1)
            increaseMatrixRows(biggerIndexNode + 1);

        this->matrix[node1].push_back(node2);
    }

    void topologicalSort() const {
        std::vector<std::vector<unsigned int>> adjacencyMatrixCopy = this->matrix;
        std::map<unsigned int, unsigned int> nodeReferencesMapper; // {nodeA: referenced by 3 other nodes, nodeB: referenced by 1 other node}

        for (unsigned int index = 0; index < adjacencyMatrixCopy.size(); ++index) {
            const std::vector<unsigned int>& referencedNodes = adjacencyMatrixCopy[index];

            if (referencedNodes.empty()) { // No reference nodes: leaf or empty matrix row
                continue;
            }

            if (!nodeReferencesMapper.contains(index)) { // Initialize if it's not referenced by another node 
                nodeReferencesMapper[index] = 0;
            }

            for (const unsigned int& referencedNode : referencedNodes) {
                if (nodeReferencesMapper.contains(referencedNode))
                    nodeReferencesMapper[referencedNode] += 1;
                else
                    nodeReferencesMapper[referencedNode] = 1;
            }
        }

        do {
            std::vector<unsigned int> removedNodes;

            for (auto nodeRefIterator = nodeReferencesMapper.begin(); nodeRefIterator != nodeReferencesMapper.end();) {
                if (nodeRefIterator->second == 0) { // If the node isn't referenced by other nodes
                    std::cout << nodeRefIterator->first << " ";

                    removedNodes.push_back(nodeRefIterator->first);
                    nodeRefIterator = nodeReferencesMapper.erase(nodeRefIterator);

                } else {
                    ++nodeRefIterator;
                }
            }

            for (const unsigned int& removedNode : removedNodes) {
                for (const unsigned int& referencedNode : adjacencyMatrixCopy[removedNode]) {
                    --nodeReferencesMapper[referencedNode];
                }
                adjacencyMatrixCopy[removedNode].clear();
            }

        } while (!nodeReferencesMapper.empty());
    }
};


int main() {
    Graph graph{"1-2;1-3;2-4;2-5;3-6;4-3;4-6;5-4"};

    graph.topologicalSort();
    // Expected output: 1 2 5 4 3 6
}
