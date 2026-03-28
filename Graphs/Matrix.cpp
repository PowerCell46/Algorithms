class Graph {
private:
    unsigned int biggestNode;
    unsigned int** matrix;

public:
    explicit Graph(const unsigned int biggestNode)
        : biggestNode(biggestNode), matrix(new unsigned int*[biggestNode + 1]{}) {
        for (unsigned int rowIndex = 0; rowIndex < biggestNode + 1; ++rowIndex) {
            this->matrix[rowIndex] = new unsigned int[biggestNode + 1]{};
        }
    }

    explicit Graph(const unsigned int biggestNode, const std::string& relationships)
        : Graph(biggestNode) {
        std::istringstream strStream{relationships};
        std::string currentRelationship;

        while (std::getline(strStream, currentRelationship, ';')) {
            std::istringstream currentRelationshipStream{currentRelationship};
            std::string firstNodeStr, secondNodeStr;

            std::getline(currentRelationshipStream, firstNodeStr, '-');
            std::getline(currentRelationshipStream, secondNodeStr, '-');

            unsigned int firstNode = std::stoul(firstNodeStr);
            unsigned int secondNode = std::stoul(secondNodeStr);

            addRelationship(firstNode, secondNode);
        }
    }

    void addRelationship(const unsigned int node1, const unsigned int node2) {
        if (node1 > this->biggestNode || node2 > this->biggestNode)
            throw std::invalid_argument("Invalid node passed.");

        this->matrix[node1][node2] = 1;
        this->matrix[node2][node1] = 1;
    }

    ~Graph() {
        for (unsigned int i = 0; i < this->biggestNode; ++i)
            delete[] this->matrix[i];
        delete[] this->matrix;
    }

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    for (unsigned int rowIndex = 0; rowIndex < graph.biggestNode + 1; ++rowIndex) {
        for (unsigned int colIndex = 0; colIndex < graph.biggestNode + 1; ++colIndex) {
            os << graph.matrix[rowIndex][colIndex] << ' ';
        }
        os << '\n';
    }
    return os;
}

int main() {
    // Graph g{6};
    // g.addRelationship(1, 3);
    // g.addRelationship(3, 4);

    Graph graph{6, "0-3;3-5;5-2;2-4;4-6;6-0;3-1;5-1;2-1;4-1;6-1"};
    std::cout << graph;

    return 0;
}
