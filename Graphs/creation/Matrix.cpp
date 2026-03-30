class Graph {
private:
    unsigned int biggestNodeValue;
    unsigned int** matrix;

public:
    explicit Graph(const unsigned int biggestNodeValue)
        : biggestNodeValue(biggestNodeValue), matrix(new unsigned int*[biggestNodeValue + 1]{}) {
        for (unsigned int rowIndex = 0; rowIndex < biggestNodeValue + 1; ++rowIndex) {
            this->matrix[rowIndex] = new unsigned int[biggestNodeValue + 1]{};
        }
    }

    Graph(const unsigned int biggestNodeValue, const std::string& relationships)
        : Graph(biggestNodeValue) {
        std::istringstream strStream{relationships};
        std::string currentRelationship;

        while (std::getline(strStream, currentRelationship, ';')) { // Split by ;
            std::istringstream currentRelationshipStream{currentRelationship};
            std::string firstNodeValueStr, secondNodeValueStr;

            std::getline(currentRelationshipStream, firstNodeValueStr, '-'); // Split by -
            std::getline(currentRelationshipStream, secondNodeValueStr, '-'); // Split by -

            unsigned int firstNodeValue = std::stoul(firstNodeValueStr);
            unsigned int secondNodeValue = std::stoul(secondNodeValueStr);
            addRelationship(firstNodeValue, secondNodeValue);
        }
    }

    void addRelationship(const unsigned int nodeOneValue, const unsigned int nodeTwoValue) {
        if (nodeOneValue > this->biggestNodeValue || nodeTwoValue > this->biggestNodeValue)
            throw std::invalid_argument("Invalid node passed.");

        this->matrix[nodeOneValue][nodeTwoValue] = 1;
        this->matrix[nodeTwoValue][nodeOneValue] = 1;
    }

    Graph(const Graph& other) = delete;

    Graph& operator=(const Graph& other) = delete;

    ~Graph() {
        for (unsigned int rowIndex = 0; rowIndex < this->biggestNodeValue; ++rowIndex)
            delete[] this->matrix[rowIndex];
        delete[] this->matrix;
    }

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};

std::ostream& operator<<(std::ostream& os, const Graph& graph) { // .toString()
    for (unsigned int rowIndex = 0; rowIndex < graph.biggestNodeValue + 1; ++rowIndex) {
        for (unsigned int colIndex = 0; colIndex < graph.biggestNodeValue + 1; ++colIndex) {
            os << graph.matrix[rowIndex][colIndex] << ' ';
        }
        os << '\n';
    }
    return os;
}

int main() {
    Graph g{6};
    g.addRelationship(1, 3);
    g.addRelationship(3, 4);

    Graph graph{6, "0-3;3-5;5-2;2-4;4-6;6-0;3-1;5-1;2-1;4-1;6-1"};
    std::cout << graph;

    return 0;
}
