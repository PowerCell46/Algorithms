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
    std::map<int, std::set<GraphNodeEdge*>> nodeRelationshipsMapper;

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

    // static bool firstAndSecondNodeValuePresentInVisitedNodesSet(
    //     const std::set<int>& visitedNodesSet,
    //     const GraphNodeEdge* graphNodeEdge
    // ) {
    //     return visitedNodesSet.contains(graphNodeEdge->getFirstNodeValue()) &&
    //            visitedNodesSet.contains(graphNodeEdge->getSecondNodeValue());
    // }

public:
    explicit Graph(const std::string& relationships) {
        std::istringstream strStream{relationships};
        std::string currentLine;

        while (std::getline(strStream, currentLine, ';')) {
            std::istringstream currentLineStream{currentLine};

            std::string firstNodeStr, secondNodeStr, edgeWeightStr;

            std::getline(currentLineStream, firstNodeStr, '-');
            std::getline(currentLineStream, secondNodeStr, ':');
            std::getline(currentLineStream, edgeWeightStr);

            this->addRelationship(
                std::stoi(firstNodeStr),
                std::stoi(secondNodeStr),
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

        if (nodeRelationshipsMapper.contains(firstNodeValue))
            this->nodeRelationshipsMapper[firstNodeValue].insert(graphNodeEdge);
        else
            this->nodeRelationshipsMapper[firstNodeValue] = {graphNodeEdge};

        if (this->nodeRelationshipsMapper.contains(secondNodeValue))
            this->nodeRelationshipsMapper[secondNodeValue].insert(graphNodeEdge);
        else
            this->nodeRelationshipsMapper[secondNodeValue] = {graphNodeEdge};
    }

    std::vector<int> primsAlgorithm(const int nodeValue) {
        if (!this->nodeRelationshipsMapper.contains(nodeValue))
            throw std::invalid_argument("The passed in nodeValue is not valid.");

        std::vector<int> visitedNodesVector;
        visitedNodesVector.reserve(this->nodeRelationshipsMapper.size());
        std::set<int> visitedNodesSet;

        visitedNodesVector.push_back(nodeValue);
        visitedNodesSet.insert(nodeValue);

        std::set<GraphNodeEdge*> potentialGraphNodeEdges = this->nodeRelationshipsMapper[nodeValue];
        while (visitedNodesSet.size() < this->nodeRelationshipsMapper.size()) {
            unsigned int smallestEdgeWeight = INT_MAX;
            GraphNodeEdge* smallestGraphNodeEdge = nullptr;

            for (auto potentialGraphNodeEdgeIter = potentialGraphNodeEdges.begin(); potentialGraphNodeEdgeIter != potentialGraphNodeEdges.end();) {
                if (firstOrSecondNodeValueNotPresentInVisitedNodesSet(visitedNodesSet, *potentialGraphNodeEdgeIter)) {
                    if ((*potentialGraphNodeEdgeIter)->getEdgeWeight() < smallestEdgeWeight) {
                        smallestEdgeWeight = (*potentialGraphNodeEdgeIter)->getEdgeWeight();
                        smallestGraphNodeEdge = *potentialGraphNodeEdgeIter;
                    }
                    ++potentialGraphNodeEdgeIter;

                } else /* if firstAndSecondNodeValuePresentInVisitedNodesSet(visitedNodesSet, *potentialGraphNodeEdgeIter) */ {
                    potentialGraphNodeEdgeIter = potentialGraphNodeEdges.erase(potentialGraphNodeEdgeIter);
                }
            }

            if (smallestGraphNodeEdge == nullptr) {
                throw std::runtime_error("Didn't find next smallest graphNodeEdge.");
            }

            if (visitedNodesSet.contains(smallestGraphNodeEdge->getFirstNodeValue())) {
                visitedNodesVector.push_back(smallestGraphNodeEdge->getSecondNodeValue());
                visitedNodesSet.insert(smallestGraphNodeEdge->getSecondNodeValue());

                const std::set<GraphNodeEdge*>& newEdges = this->nodeRelationshipsMapper[smallestGraphNodeEdge->getSecondNodeValue()];
                potentialGraphNodeEdges.insert(newEdges.begin(), newEdges.end());

            } else {
                visitedNodesVector.push_back(smallestGraphNodeEdge->getFirstNodeValue());
                visitedNodesSet.insert(smallestGraphNodeEdge->getFirstNodeValue());

                const std::set<GraphNodeEdge*>& newEdges = this->nodeRelationshipsMapper[smallestGraphNodeEdge->getFirstNodeValue()];
                potentialGraphNodeEdges.insert(newEdges.begin(), newEdges.end());
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

        for (const GraphNodeEdge* uniqueGraphNodeEdge : uniqueGraphNodeEdges) {
            delete uniqueGraphNodeEdge;
        }
    }
};

int main() {
    // Graph graph{"4-2:2;4-3:5;2-1:1;2-5:2;2-3:3;1-5:5;3-5:2"};
    // std::vector<int> primsAlgorithmResultVector = graph.primsAlgorithm(4);

    Graph graph{"1-2:4;1-3:2;1-4:1;2-5:3;2-3:5;3-5:6;3-4:8;4-5:7"};
    std::vector<int> primsAlgorithmResultVector = graph.primsAlgorithm(1);

    for (const int& nodeValue : primsAlgorithmResultVector) {
        std::cout << nodeValue << " ";
    }

    return 0;
}
