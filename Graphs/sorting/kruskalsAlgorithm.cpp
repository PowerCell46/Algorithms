#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <set>
#include <map>


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
private:
    std::map<int, std::set<GraphNodeEdge*>> nodeRelationshipMapper; // {1: {firstNodeValue: 1, secondNodeValue: 2, edgeWeight: 1}}

    [[nodiscard]] static int getNodeRootAscendant(std::map<int, int>& nodeValueTreeParentMapper, const int nodeValue) {
        if (nodeValueTreeParentMapper[nodeValue] == nodeValue)
            return nodeValue;
        return getNodeRootAscendant(nodeValueTreeParentMapper, nodeValueTreeParentMapper[nodeValue]);
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

        if (this->nodeRelationshipMapper.contains(firstNodeValue))
            this->nodeRelationshipMapper[firstNodeValue].insert(graphNodeEdge);
        else
            this->nodeRelationshipMapper[firstNodeValue] = std::set<GraphNodeEdge*>{graphNodeEdge};

        if (this->nodeRelationshipMapper.contains(secondNodeValue))
            this->nodeRelationshipMapper[secondNodeValue].insert(graphNodeEdge);
        else
            this->nodeRelationshipMapper[secondNodeValue] = std::set<GraphNodeEdge*>{graphNodeEdge};
    }

    std::vector<std::string> kruskalsAlgorithm() {
        std::vector<std::string> resultGraphNodeEdgesVector;
        resultGraphNodeEdgesVector.reserve(this->nodeRelationshipMapper.size());

        std::set<GraphNodeEdge*> uniqueGraphNodeEdges;
        for (const auto& [nodeValue, graphNodeEdges] : this->nodeRelationshipMapper) {
            uniqueGraphNodeEdges.insert(graphNodeEdges.begin(), graphNodeEdges.end());
        }

        std::vector<GraphNodeEdge*> graphNodeEdgesSortedByWeightAsc{
            uniqueGraphNodeEdges.begin(),
            uniqueGraphNodeEdges.end()
        };
        std::sort(
            graphNodeEdgesSortedByWeightAsc.begin(),
            graphNodeEdgesSortedByWeightAsc.end(),
            [](const GraphNodeEdge* firstGraphNodeEdge, const GraphNodeEdge* secondGraphNodeEdge) {
               return firstGraphNodeEdge->getEdgeWeight() < secondGraphNodeEdge->getEdgeWeight();
        });

        std::map<int, int> nodeValueTreeParentMapper; // {1: 1, 2: 2, 3: 3}
        // Initialize each graphNodeValue as a tree
        for (const auto& [nodeValue, graphNodeEdges] : this->nodeRelationshipMapper) {
            nodeValueTreeParentMapper[nodeValue] = nodeValue;
        }
        size_t uniqueTreesCount = nodeValueTreeParentMapper.size();

        auto iterGraphNodeEdgesSortedByWeightAsc = graphNodeEdgesSortedByWeightAsc.begin();
        while (uniqueTreesCount > 1) {
            const int firstNodeValue = (*iterGraphNodeEdgesSortedByWeightAsc)->getFirstNodeValue();
            const int secondNodeValue = (*iterGraphNodeEdgesSortedByWeightAsc)->getSecondNodeValue();
            const unsigned int edgeWeight = (*iterGraphNodeEdgesSortedByWeightAsc)->getEdgeWeight();

            const int firstNodeRootParentAncestor = getNodeRootAscendant(nodeValueTreeParentMapper, firstNodeValue);
            const int secondNodeRootParentAncestor = getNodeRootAscendant(nodeValueTreeParentMapper, secondNodeValue);

            if (firstNodeRootParentAncestor != secondNodeRootParentAncestor) { // The two nodes are located on separate trees
                std::stringstream currentGraphNodeEdgeStream{};
                currentGraphNodeEdgeStream << firstNodeValue << " -> " << secondNodeValue << " (" << edgeWeight << ")\n";

                // Make the secondNodeTree subtree of the firstNodeTree
                nodeValueTreeParentMapper[firstNodeRootParentAncestor] = secondNodeRootParentAncestor;
                --uniqueTreesCount;

                resultGraphNodeEdgesVector.push_back(currentGraphNodeEdgeStream.str());
            }

            ++iterGraphNodeEdgesSortedByWeightAsc;
            if (iterGraphNodeEdgesSortedByWeightAsc == graphNodeEdgesSortedByWeightAsc.end())
                throw std::runtime_error("Error occurred while iterating through the graphNodeEdges.");
        }

        return resultGraphNodeEdgesVector;
    }

    ~Graph() {
        std::set<GraphNodeEdge*> uniqueGraphNodeEdges;
        for (const auto& [nodeValue, graphNodeEdges] : this->nodeRelationshipMapper) {
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
    Graph graph = Graph{"1-2:4;1-3:2;1-4:1;2-5:3;2-3:5;3-5:9;3-4:8;4-5:7"};
    std::vector<std::string> kruskalsAlgorithmResultVector = graph.kruskalsAlgorithm();

    for (const std::string& graphNodeEdgeStr : kruskalsAlgorithmResultVector)
        std::cout << graphNodeEdgeStr;
}
