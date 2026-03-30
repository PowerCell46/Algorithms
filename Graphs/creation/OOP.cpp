class GraphEdge {
private:
    unsigned int fromNodeValue;
    unsigned int toNodeValue;

public:
    GraphEdge(const unsigned int fromNodeValue, const unsigned int toNodeValue)
        : fromNodeValue(fromNodeValue), toNodeValue(toNodeValue) {}

    [[nodiscard]] unsigned int getFromNodeValue() const {
        return this->fromNodeValue;
    }

    [[nodiscard]] unsigned int getToNodeValue() const {
        return this->toNodeValue;
    }
};

class Graph {
private:
    unsigned int currentIndex;
    GraphEdge** graphEdges; // GraphEdge[]
    unsigned int countGraphEdges;

public:
    explicit Graph(const unsigned int countGraphEdges)
        : currentIndex(0), graphEdges(new GraphEdge*[countGraphEdges]{}), countGraphEdges(countGraphEdges) {}

    Graph(const unsigned int countGraphEdges, GraphEdge** graphEdges)
        : currentIndex(countGraphEdges), graphEdges(graphEdges), countGraphEdges(countGraphEdges) {}

    Graph(const Graph& other) = delete;

    Graph& operator=(const Graph& other) = delete;

    void addEdge(const unsigned int fromNodeValue, const unsigned int toNodeValue) {
        if (this->currentIndex >= this->countGraphEdges)
            throw std::invalid_argument("Number of edges overflows predefined size.");

        this->graphEdges[this->currentIndex] = new GraphEdge{fromNodeValue, toNodeValue};
        ++this->currentIndex;
    }

    [[nodiscard]] GraphEdge** getRelatedNodes(const unsigned int nodeValue, unsigned int& relatedNodesSize) const {
        relatedNodesSize = 0;
        for (unsigned int i = 0; i < this->currentIndex; ++i) {
            if (this->graphEdges[i]->getFromNodeValue() == nodeValue) {
                ++relatedNodesSize;
            }
        }

        GraphEdge** relatedNodes = new GraphEdge*[relatedNodesSize]{};
        unsigned int indexRelatedNodes = 0;

        for (unsigned int i = 0; i < this->currentIndex; ++i) {
            if (this->graphEdges[i]->getFromNodeValue() == nodeValue) {
                relatedNodes[indexRelatedNodes++] = this->graphEdges[i];
            }
        }

        return relatedNodes;
    }

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

    ~Graph() {
        for (unsigned int index = 0; index < this->currentIndex; ++index) {
            delete this->graphEdges[index];
        }
        delete[] this->graphEdges;
    }
};

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    for (unsigned int index = 0; index < std::min(graph.currentIndex, graph.countGraphEdges); ++index) {
        os << graph.graphEdges[index]->getFromNodeValue() << " -> " << graph.graphEdges[index]->getToNodeValue() << std::endl;
    }
    return os;
}

int main() {
    Graph g{22};

    g.addEdge(0, 3);
    g.addEdge(3, 0);

    g.addEdge(0, 6);
    g.addEdge(6, 0);

    g.addEdge(3, 5);
    g.addEdge(5, 3);

    g.addEdge(3, 1);
    g.addEdge(1, 3);

    g.addEdge(5, 1);
    g.addEdge(1, 5);

    g.addEdge(5, 2);
    g.addEdge(2, 5);

    g.addEdge(2, 1);
    g.addEdge(1, 2);

    g.addEdge(2, 4);
    g.addEdge(4, 2);

    g.addEdge(4, 1);
    g.addEdge(1, 4);

    g.addEdge(4, 6);
    g.addEdge(6, 4);

    g.addEdge(6, 1);
    g.addEdge(1, 6);

    GraphEdge* graphEdge1 = new GraphEdge(0, 3);
    GraphEdge* graphEdge2 = new GraphEdge(3, 0);

    GraphEdge* graphEdge3 = new GraphEdge(0, 6);
    GraphEdge* graphEdge4 = new GraphEdge(6, 0);

    GraphEdge* graphEdge5 = new GraphEdge(3, 5);
    GraphEdge* graphEdge6 = new GraphEdge(5, 3);

    GraphEdge* graphEdge7 = new GraphEdge(3, 1);
    GraphEdge* graphEdge8 = new GraphEdge(1, 3);

    GraphEdge* graphEdge9 = new GraphEdge(5, 1);
    GraphEdge* graphEdge10 = new GraphEdge(1, 5);

    GraphEdge* graphEdge11 = new GraphEdge(5, 2);
    GraphEdge* graphEdge12 = new GraphEdge(2, 5);

    GraphEdge* graphEdge13 = new GraphEdge(2, 1);
    GraphEdge* graphEdge14 = new GraphEdge(1, 2);

    GraphEdge* graphEdge15 = new GraphEdge(2, 4);
    GraphEdge* graphEdge16 = new GraphEdge(4, 2);

    GraphEdge* graphEdge17 = new GraphEdge(4, 1);
    GraphEdge* graphEdge18 = new GraphEdge(1, 4);

    GraphEdge* graphEdge19 = new GraphEdge(4, 6);
    GraphEdge* graphEdge20 = new GraphEdge(6, 4);

    GraphEdge* graphEdge21 = new GraphEdge(6, 1);
    GraphEdge* graphEdge22 = new GraphEdge(1, 6);

    Graph graph{22, new GraphEdge*[] {
        graphEdge1, graphEdge2, graphEdge3, graphEdge4, graphEdge5,
        graphEdge6, graphEdge7, graphEdge8, graphEdge9, graphEdge10,
        graphEdge11, graphEdge12, graphEdge13, graphEdge14, graphEdge15,
        graphEdge16, graphEdge17, graphEdge18, graphEdge19, graphEdge20,
        graphEdge21, graphEdge22
    }};

    std::cout << graph;

    return 0;
}
