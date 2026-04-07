#include <iostream>
#include <vector>
#include <sstream>
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

    // ! Weights are of datatype unsigned int, so you cannot run it with negative weights
    [[nodiscard]] unsigned int bellmanFordsAlgorithm(const int startingNode, const int searchedNode) const {
        if (
            !this->nodeValueToNodeEdgesMapper.contains(startingNode) ||
            !this->nodeValueToNodeEdgesMapper.contains(searchedNode)
        ) {
            throw std::invalid_argument("Passed in method arguments aren't present in the graph.");
        }

        std::map<int, unsigned int> nodeValueToWeightMapper;
        for (const auto& [nodeValue, _] : this->nodeValueToNodeEdgesMapper) {
            nodeValueToWeightMapper[nodeValue] = UINT_MAX;
        }
        nodeValueToWeightMapper[startingNode] = 0;

        for (int index = 0; index < this->nodeValueToNodeEdgesMapper.size() - 1; ++index) { // Number of nodes - 1
            bool noWeightImprovementsFound = true;

            for (const auto& [nodeValue, nodeEdges] : this->nodeValueToNodeEdgesMapper) {
                if (nodeValueToWeightMapper.at(nodeValue) == UINT_MAX) // ATP we don't know how to reach nodeValue, so we skip it
                    continue;

                for (const DirectedWeightedGraphNodeEdge* nodeEdge : nodeEdges) {
                    const unsigned int newProbableWeight = nodeValueToWeightMapper.at(nodeValue) + nodeEdge->getWeight(); // TODO: Could potentially overflow unsigned int

                    if (newProbableWeight < nodeValueToWeightMapper.at(nodeEdge->getToNodeValue())) {
                        noWeightImprovementsFound = false;
                        nodeValueToWeightMapper[nodeEdge->getToNodeValue()] = newProbableWeight;
                    }
                }
            }

            if (noWeightImprovementsFound) {
                break;
            }
        }

        if (nodeValueToWeightMapper.at(searchedNode) == UINT_MAX) {
            throw std::runtime_error("Cannot find shortest path from the given startingNode to the searchedNode.");
        }
        return nodeValueToWeightMapper.at(searchedNode);
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
    const DirectedWeightedGraph graph{"6-1:1;6-2:5;1-2:2;1-3:2;1-4:1;2-4:2;3-4:3;3-5:1;4-5:2"};

    const unsigned int weight = graph.bellmanFordsAlgorithm(6, 5);
    std::cout << "Weight distance between 6 and 5: " << weight << '.' << std::endl;

    return 0;
}
 