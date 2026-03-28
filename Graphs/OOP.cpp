class GraphEdge {
private:
    unsigned int fromNode;
    unsigned int toNode;

public:
    GraphEdge(const unsigned int fromNode, const unsigned int toNode)
        : fromNode(fromNode), toNode(toNode) {}

    [[nodiscard]] unsigned int getFromNode() const {
        return this->fromNode;
    }

    [[nodiscard]] unsigned int getToNode() const {
        return this->toNode;
    }
};

class Graph {
private:
    unsigned int currentIndex;
    GraphEdge** graphEdges;
    unsigned int graphEdgesCount;

public:
    explicit Graph(const unsigned int graphEdgesCount)
        : currentIndex(0), graphEdges(new GraphEdge*[graphEdgesCount]{}), graphEdgesCount(graphEdgesCount) {}

    Graph(const unsigned int graphEdgesCount, GraphEdge** graphEdges)
        : currentIndex(graphEdgesCount), graphEdges(graphEdges), graphEdgesCount(graphEdgesCount) {}

    void addEdge(const unsigned int fromNode, const unsigned int toNode) {
        if (this->currentIndex >= this->graphEdgesCount)
            throw std::invalid_argument("Invalid number of edges.");

        this->graphEdges[this->currentIndex] = new GraphEdge{fromNode, toNode};
        ++this->currentIndex;
    }

    [[nodiscard]] std::vector<GraphEdge*> getRelatedNodes(const unsigned int node) const {
        std::vector<GraphEdge*> edges;

        for (unsigned int i = 0; i < this->currentIndex; ++i) {
            if (this->graphEdges[i]->getFromNode() == node) {
                edges.push_back(this->graphEdges[i]);
            }
        }

        return edges;
    }

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

    ~Graph() {
        for (unsigned int i = 0; i < this->currentIndex; ++i) {
            delete this->graphEdges[i];
        }
        delete[] this->graphEdges;
    }
};

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    for (unsigned int i = 0; i < std::min(graph.currentIndex, graph.graphEdgesCount); ++i) {
        os << graph.graphEdges[i]->getFromNode() << " -> " << graph.graphEdges[i]->getToNode() << std::endl;
    }
    return os;
}

int main() {
    // Graph graph{22};

    // graph.addEdge(0, 3);
    // graph.addEdge(3, 0);
    //
    // graph.addEdge(0, 6);
    // graph.addEdge(6, 0);
    //
    // graph.addEdge(3, 5);
    // graph.addEdge(5, 3);
    //
    // graph.addEdge(3, 1);
    // graph.addEdge(1, 3);
    //
    // graph.addEdge(5, 1);
    // graph.addEdge(1, 5);
    //
    // graph.addEdge(5, 2);
    // graph.addEdge(2, 5);
    //
    // graph.addEdge(2, 1);
    // graph.addEdge(1, 2);
    //
    // graph.addEdge(2, 4);
    // graph.addEdge(4, 2);
    //
    // graph.addEdge(4, 1);
    // graph.addEdge(1, 4);
    //
    // graph.addEdge(4, 6);
    // graph.addEdge(6, 4);
    //
    // graph.addEdge(6, 1);
    // graph.addEdge(1, 6);

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
