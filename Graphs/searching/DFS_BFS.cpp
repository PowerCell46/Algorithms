#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <queue>


class Graph { // Directed
private:
    std::vector<std::vector<unsigned int>> matrix;

    void _DFS(const unsigned int node, std::unordered_set<unsigned int>& visitedNodes) const {
        if (visitedNodes.contains(node)) {
            return;
        }
        visitedNodes.insert(node);

        for (const unsigned int& childNode : this->matrix[node]) {
            _DFS(childNode, visitedNodes);
        }
        std::cout << node << " ";
    }

    void _BFS(
        const unsigned int node,
        std::unordered_set<unsigned int>& visitedNodes,
        std::queue<unsigned int>& nextNodes
    ) const {
        if (!visitedNodes.contains(node)) {
            std::cout << node << " ";
            visitedNodes.insert(node);

            for (const unsigned int& childNode : this->matrix[node]) {
                nextNodes.push(childNode);
            }
        }

        if (!nextNodes.empty()) {
            const unsigned int nextNode = nextNodes.front();
            nextNodes.pop();
            _BFS(nextNode, visitedNodes, nextNodes);
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

    void increaseMatrixRows(const unsigned int newSize) {
        const unsigned int numberOfNewRows = newSize - this->matrix.size();
        for (unsigned int i = 0; i < numberOfNewRows; ++i)
            this->matrix.emplace_back();
    }

    void DFS(const unsigned int node) const {
        std::unordered_set<unsigned int> visitedNodes;
        visitedNodes.reserve(this->matrix.size());

        _DFS(node, visitedNodes);
    }

    void BFS(const unsigned int node) const {
        std::unordered_set<unsigned int> visitedNodes;
        visitedNodes.reserve(this->matrix.size());

        std::queue<unsigned int> nextNodes;

        _BFS(node, visitedNodes, nextNodes);
    }
};

int main() {
    Graph g{};
    g.addRelationship(1, 3);
    g.addRelationship(3, 10);

    // Graph graph{"1-19;1-21;1-14;19-7;19-12;19-31;19-21;21-14;14-6;14-23;7-1;31-21;23-21"};
    // graph.DFS(1);

    Graph graph{"1-19;1-21;1-14;19-7;19-12;19-31;19-21;21-14;14-23;14-6;7-1;31-21;23-21"};
    graph.BFS(1);
}
