#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>


class DirectedWeightedGraphNodeEdge {
private:
    int toNodeValue;
    unsigned int weight;
public:
    DirectedWeightedGraphNodeEdge(const int toNodeValue, const unsigned int weight)
        : toNodeValue(toNodeValue), weight(weight) {}

    [[nodiscard]] int getToNodeValue() const {
        return this->toNodeValue;
    }

    [[nodiscard]] unsigned int getWeight() const {
        return this->weight;
    }
};

class DirectedWeightedGraph {
private:
    std::map<int, std::vector<DirectedWeightedGraphNodeEdge*>> nodeValueToNodeEdgesMapper;
public:
    explicit DirectedWeightedGraph(const std::string& relationships) {
        std::istringstream relationshipsStream{relationships};
        std::string currentLine;

        while (std::getline(relationshipsStream, currentLine, ';')) {
            std::istringstream currentLineStream{currentLine};

            std::string fromNodeValueStr, toNodeValueStr, weightStr;

            std::getline(currentLineStream, fromNodeValueStr, '-');
            std::getline(currentLineStream, toNodeValueStr, ':');
            std::getline(currentLineStream, weightStr);

            addRelationship(
                std::stoi(fromNodeValueStr),
                std::stoi(toNodeValueStr),
                std::stoul(weightStr)
            );
        }
    }

    DirectedWeightedGraph(const DirectedWeightedGraph& other) = delete;

    DirectedWeightedGraph& operator=(const DirectedWeightedGraph& other) = delete;

    void addRelationship(const int fromNodeValue, const int toNodeValue, const unsigned int weight) {
        if (fromNodeValue == toNodeValue) {
            throw std::invalid_argument("Cannot set relationship between the same node.");
        }

        auto* graphNodeEdge = new DirectedWeightedGraphNodeEdge{toNodeValue, weight};

        if (this->nodeValueToNodeEdgesMapper.contains(fromNodeValue))
            this->nodeValueToNodeEdgesMapper[fromNodeValue].push_back(graphNodeEdge);
        else
            this->nodeValueToNodeEdgesMapper[fromNodeValue] = std::vector<DirectedWeightedGraphNodeEdge*>{graphNodeEdge};

        if (!this->nodeValueToNodeEdgesMapper.contains(toNodeValue))
            this->nodeValueToNodeEdgesMapper[toNodeValue] = std::vector<DirectedWeightedGraphNodeEdge*>{};
    }

    unsigned int dijkstrasAlgorithm(const int startNodeValue, const int searchedNodeValue) {
        if (
            !this->nodeValueToNodeEdgesMapper.contains(startNodeValue) ||
            !this->nodeValueToNodeEdgesMapper.contains(searchedNodeValue)
        ) {
            throw std::invalid_argument("Invalid nodeValues passed in as method parameters.");
        }

        std::map<int, unsigned int> nodeValueToWeightMapper;
        std::set<int> visitedNodeValues;

        for (const auto& [nodeValue, _] : this->nodeValueToNodeEdgesMapper) {
            nodeValueToWeightMapper[nodeValue] = UINT_MAX;
        }
        nodeValueToWeightMapper[startNodeValue] = 0;

        while (!visitedNodeValues.contains(searchedNodeValue)) {
            unsigned int smallestWeight = UINT_MAX;
            int smallestWeightNodeValue{};

            for (auto& [nodeValue, distance] : nodeValueToWeightMapper) {
                if (visitedNodeValues.contains(nodeValue)) // Skip if we already have iterated through the nodeValue
                    continue;
                if (distance < smallestWeight) {
                    smallestWeight = distance;
                    smallestWeightNodeValue = nodeValue;
                }
            }

            if (smallestWeight == UINT_MAX) {
                throw std::runtime_error("Cannot find path to the searchedNode from the startNode.");
            }

            for (const DirectedWeightedGraphNodeEdge* graphNodeEdge : this->nodeValueToNodeEdgesMapper[smallestWeightNodeValue]) {
                nodeValueToWeightMapper[graphNodeEdge->getToNodeValue()] = std::min(
                    nodeValueToWeightMapper[graphNodeEdge->getToNodeValue()],
                    smallestWeight + graphNodeEdge->getWeight() // TODO: Could potentially overflow unsigned int
                );
            }
            visitedNodeValues.insert(smallestWeightNodeValue);
        }

        return nodeValueToWeightMapper[searchedNodeValue];
     }

    ~DirectedWeightedGraph() {
        for (auto& [nodeValue, graphNodeEdges] : this->nodeValueToNodeEdgesMapper) {
            for (DirectedWeightedGraphNodeEdge* graphNodeEdge : graphNodeEdges) {
                delete graphNodeEdge;
            }
        }
    }
};


int main() {
    DirectedWeightedGraph graph{"6-1:1;6-2:5;1-2:2;1-3:2;1-4:1;2-4:2;3-4:3;3-5:1;4-5:2"};

    const unsigned int weight = graph.dijkstrasAlgorithm(6, 5);
    std::cout << "Weight distance between 6 and 5: " << weight << '.' << std::endl;

    return 0;
}
