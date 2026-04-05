#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <map>


class DirectedGraph {
private:
    std::map<int, std::set<int>> nodeRelationshipMapper; // {1: {firstNodeValue: 1, secondNodeValue: 2}}
    std::set<int> uniqueNodeValues;

    void BFS( // ! Will stack overflow on large graphs
        std::map<int, int>& nodeValueParentNodeValueMapper,
        std::set<int>& visitedNodes,
        std::queue<int>& nextNodeValues,
        const int nodeValue,
        const int searchedNodeValue
    ) {
        if (nodeValue == searchedNodeValue)
            return;

        if (!visitedNodes.contains(nodeValue)) {
            visitedNodes.insert(nodeValue);

            if (this->nodeRelationshipMapper.contains(nodeValue)) {
                for (const int& pointedAtNodeValue : this->nodeRelationshipMapper[nodeValue]) {
                    nextNodeValues.push(pointedAtNodeValue);
                    // Set the parent node (only if it's not already set)
                    if (!nodeValueParentNodeValueMapper.contains(pointedAtNodeValue)) {
                        nodeValueParentNodeValueMapper[pointedAtNodeValue] = nodeValue;
                    }
                }
            }
        }

        if (!nextNodeValues.empty()) {
            const int nextNodeValue = nextNodeValues.front();
            nextNodeValues.pop();
            BFS(nodeValueParentNodeValueMapper, visitedNodes, nextNodeValues, nextNodeValue, searchedNodeValue);
        }
    }

public:
    explicit DirectedGraph(const std::string& relationships) {
        std::istringstream strStream{relationships};
        std::string currentLine;

        while (std::getline(strStream, currentLine, ';')) {
            std::istringstream currentLineStream{currentLine};

            std::string firstNodeValueStr, secondNodeValueStr, edgeWeightStr;

            std::getline(currentLineStream, firstNodeValueStr, '-');
            std::getline(currentLineStream, secondNodeValueStr);

            this->addRelationship(std::stoi(firstNodeValueStr), std::stoi(secondNodeValueStr));
        }
    }

    DirectedGraph(const DirectedGraph& other) = delete;

    DirectedGraph& operator=(const DirectedGraph& other) = delete;

    void addRelationship(const int firstNodeValue, const int secondNodeValue) {
        if (firstNodeValue == secondNodeValue)
            throw std::invalid_argument("Cannot add a relationship between the same node.");

        if (this->nodeRelationshipMapper.contains(firstNodeValue)) {
            this->nodeRelationshipMapper[firstNodeValue].insert(secondNodeValue);

        } else {
            this->nodeRelationshipMapper[firstNodeValue] = std::set<int>{secondNodeValue};
            this->uniqueNodeValues.insert(firstNodeValue);
        }

        this->uniqueNodeValues.insert(secondNodeValue);
    }

    std::vector<int> bfsShortestPath(const int startNodeValue, const int searchedNodeValue) {
        if (!this->uniqueNodeValues.contains(startNodeValue) || !this->uniqueNodeValues.contains(searchedNodeValue))
            throw std::invalid_argument("StartNodeValue or searchedNodeValue isn't valid.");

        std::map<int, int> nodeValueParentNodeValueMapper; // {1: 6, 2: 6, 3: 1}
        nodeValueParentNodeValueMapper[startNodeValue] = startNodeValue;

        std::queue<int> nextNodeValues{};
        std::set<int> visitedNodes{};

        BFS(nodeValueParentNodeValueMapper, visitedNodes, nextNodeValues, startNodeValue, searchedNodeValue);

        if (nodeValueParentNodeValueMapper.contains(searchedNodeValue))
            throw std::runtime_error("No path found to the searched node.");

        std::vector<int> shortestPathReversed;
        shortestPathReversed.reserve(this->uniqueNodeValues.size());

        int nodeValue = searchedNodeValue;
        while (nodeValue != nodeValueParentNodeValueMapper[nodeValue]) {
            shortestPathReversed.push_back(nodeValue);
            nodeValue = nodeValueParentNodeValueMapper[nodeValue];
        }
        shortestPathReversed.push_back(nodeValue);

        return std::vector<int>{shortestPathReversed.rbegin(), shortestPathReversed.rend()};
    }
};


int main() {
    DirectedGraph graph{"6-1;6-2;1-2;1-3;1-4;2-4;3-4;3-5;4-5"};

    const std::vector<int> shortestPath_from_6_to_5 = graph.bfsShortestPath(6, 5);

    for (const int& nodeValue : shortestPath_from_6_to_5) {
        std::cout << nodeValue << " ";
    }
}
