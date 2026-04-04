#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <set>


class GraphNodeEdge {
private:
    int firstNodeValue;
    int secondNodeValue;
    unsigned int edgeWeight;

public:
    GraphNodeEdge(const int firstNodeValue, const int secondNodeValue, const unsigned int edgeWeight)
        : firstNodeValue(firstNodeValue), secondNodeValue(secondNodeValue), edgeWeight(edgeWeight) {}

    [[nodiscard]] int getFirstNodeValue() const {
        return this->firstNodeValue;
    }

    [[nodiscard]] int getSecondNodeValue() const {
        return this->secondNodeValue;
    }

    [[nodiscard]] unsigned int getEdgeWeight() const {
        return this->edgeWeight;
    }
};

class Graph {
    std::map<int, std::set<GraphNodeEdge*>> nodeRelationshipsMapper; // {1: {firstNodeValue: 1, secondNodeValue: 2, edgeWeight: 1}}

    static bool firstOrSecondNodeValueNotPresentInVisitedNodesSet(
        const std::set<int>& visitedNodesSet,
        const GraphNodeEdge* graphNodeEdge
    ) {
        return (visitedNodesSet.contains(graphNodeEdge->getFirstNodeValue()) &&
                !visitedNodesSet.contains(graphNodeEdge->getSecondNodeValue()))
                ||
                (visitedNodesSet.contains(graphNodeEdge->getSecondNodeValue()) &&
                !visitedNodesSet.contains(graphNodeEdge->getFirstNodeValue()));
    }

    static bool firstAndSecondNodeValuePresentInVisitedNodesSet(
        const std::set<int>& visitedNodesSet,
        const GraphNodeEdge* graphNodeEdge
    ) {
        return visitedNodesSet.contains(graphNodeEdge->getFirstNodeValue()) &&
               visitedNodesSet.contains(graphNodeEdge->getSecondNodeValue());
    }

public:
    explicit Graph(const std::string& relationships) {
        std::istringstream strStream{relationships};
        std::string currentLine;

        while (std::getline(strStream, currentLine, ';')) {
            std::istringstream currentLineStream{currentLine};

            std::string firstNodeValueStr, secondNodeValueStr, edgeWeightStr;

            std::getline(currentLineStream, firstNodeValueStr, '-');
            std::getline(currentLineStream, secondNodeValueStr, ':');
            std::getline(currentLineStream, edgeWeightStr);

            this->addRelationship(
                std::stoi(firstNodeValueStr),
                std::stoi(secondNodeValueStr),
                std::stoul(edgeWeightStr)
            );
        }
    }

    Graph(const Graph& other) = delete;

    Graph& operator=(const Graph& other) = delete;

    void addRelationship(const int firstNodeValue, const int secondNodeValue, const unsigned int edgeWeight) {
        if (firstNodeValue == secondNodeValue)
            throw std::invalid_argument("Cannot add a relationship between the same node.");

        GraphNodeEdge* graphNodeEdge = new GraphNodeEdge{firstNodeValue, secondNodeValue, edgeWeight};

        if (this->nodeRelationshipsMapper.contains(firstNodeValue))
            this->nodeRelationshipsMapper[firstNodeValue].insert(graphNodeEdge);
        else
            this->nodeRelationshipsMapper[firstNodeValue] = std::set<GraphNodeEdge*>{graphNodeEdge};

        if (this->nodeRelationshipsMapper.contains(secondNodeValue))
            this->nodeRelationshipsMapper[secondNodeValue].insert(graphNodeEdge);
        else
            this->nodeRelationshipsMapper[secondNodeValue] = std::set<GraphNodeEdge*>{graphNodeEdge};
    }

    std::vector<int> primsAlgorithm(const int nodeValue) {
        if (!this->nodeRelationshipsMapper.contains(nodeValue))
            throw std::invalid_argument("The passed in nodeValue is not valid.");

        std::vector<int> visitedNodesVector; // Keeps the insertion order
        visitedNodesVector.reserve(this->nodeRelationshipsMapper.size());
        std::set<int> visitedNodesSet;

        visitedNodesVector.push_back(nodeValue);
        visitedNodesSet.insert(nodeValue);

        std::set<GraphNodeEdge*> potentialGraphNodeEdges = this->nodeRelationshipsMapper[nodeValue];
        while (visitedNodesVector.size() < this->nodeRelationshipsMapper.size()) {
            unsigned int smallestPotentialEdgeWeight = INT_MAX;
            GraphNodeEdge* smallestPotentialGraphNodeEdge = nullptr;

            for (auto potentialGraphNodeEdgeIter = potentialGraphNodeEdges.begin(); potentialGraphNodeEdgeIter != potentialGraphNodeEdges.end();) {
                if (firstOrSecondNodeValueNotPresentInVisitedNodesSet(visitedNodesSet, *potentialGraphNodeEdgeIter)) {
                    if ((*potentialGraphNodeEdgeIter)->getEdgeWeight() < smallestPotentialEdgeWeight) {
                        smallestPotentialEdgeWeight = (*potentialGraphNodeEdgeIter)->getEdgeWeight();
                        smallestPotentialGraphNodeEdge = *potentialGraphNodeEdgeIter;
                    }
                    ++potentialGraphNodeEdgeIter;

                } else /* if (firstAndSecondNodeValuePresentInVisitedNodesSet(visitedNodesSet, *potentialGraphNodeEdgeIter)) */ {
                    potentialGraphNodeEdgeIter = potentialGraphNodeEdges.erase(potentialGraphNodeEdgeIter);
                }
            }

            if (smallestPotentialGraphNodeEdge == nullptr) {
                throw std::runtime_error("Error occurred while finding the next smallest graphNodeEdge.");
            }

            if (visitedNodesSet.contains(smallestPotentialGraphNodeEdge->getFirstNodeValue())) {
                visitedNodesVector.push_back(smallestPotentialGraphNodeEdge->getSecondNodeValue());
                visitedNodesSet.insert(smallestPotentialGraphNodeEdge->getSecondNodeValue());

                const std::set<GraphNodeEdge*>& newPotentialGraphNodeEdges = this->nodeRelationshipsMapper[smallestPotentialGraphNodeEdge->getSecondNodeValue()];
                potentialGraphNodeEdges.insert(newPotentialGraphNodeEdges.begin(), newPotentialGraphNodeEdges.end());

            } else {
                visitedNodesVector.push_back(smallestPotentialGraphNodeEdge->getFirstNodeValue());
                visitedNodesSet.insert(smallestPotentialGraphNodeEdge->getFirstNodeValue());

                const std::set<GraphNodeEdge*>& newPotentialGraphNodeEdges = this->nodeRelationshipsMapper[smallestPotentialGraphNodeEdge->getFirstNodeValue()];
                potentialGraphNodeEdges.insert(newPotentialGraphNodeEdges.begin(), newPotentialGraphNodeEdges.end());
            }
        }

        return visitedNodesVector;
    }

    ~Graph() {
        std::set<GraphNodeEdge*> uniqueGraphNodeEdges;
        for (const auto& [nodeValue, graphNodeEdges] : this->nodeRelationshipsMapper) {
            for (GraphNodeEdge* graphNodeEdge : graphNodeEdges) {
                uniqueGraphNodeEdges.insert(graphNodeEdge);
            }
        }

        for (const GraphNodeEdge* graphNodeEdge : uniqueGraphNodeEdges) {
            delete graphNodeEdge;
        }
    }
};

int main() {
    // Graph graph{"4-2:2;4-3:5;2-1:1;2-5:2;2-3:3;1-5:5;3-5:2"};
    // std::vector<int> primsAlgorithmResultVector = graph.primsAlgorithm(4);

    Graph graph{"1-2:4;1-3:2;1-4:1;2-5:3;2-3:5;3-5:6;3-4:8;4-5:7"};
    std::vector<int> primsAlgorithmResultVector = graph.primsAlgorithm(1);

    for (const int& nodeValue : primsAlgorithmResultVector)
        std::cout << nodeValue << " ";

    return 0;
}
