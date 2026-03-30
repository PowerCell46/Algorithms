class Graph {
private:
    std::vector<std::vector<unsigned int>> matrix;

public:
    Graph() : matrix() {}

    explicit Graph(const std::string& relationships) {
        std::istringstream strStream{relationships};
        std::string currentRelationship;

        while (std::getline(strStream, currentRelationship, ';')) { // Split by ;
            std::istringstream currentRelationshipStream{currentRelationship};
            std::string firstNodeStr, secondNodeStr;

            std::getline(currentRelationshipStream, firstNodeStr, '-'); // Split by -
            std::getline(currentRelationshipStream, secondNodeStr, '-'); // Split by -

            unsigned int firstNode = std::stoul(firstNodeStr);
            unsigned int secondNode = std::stoul(secondNodeStr);
            addRelationship(firstNode, secondNode);
        }
    }

    void addRelationship(const unsigned int node1, const unsigned int node2) {
        if (node1 == node2)
            throw std::invalid_argument("Cannot add relationship between the same node.");

        const unsigned int smallerIndexNode = node1 > node2 ? node2 : node1;
        const unsigned int biggerIndexNode = node1 > node2 ? node1 : node2;

        if (this->matrix.size() < biggerIndexNode + 1)
            increaseMatrixRows(biggerIndexNode + 1);

        this->matrix[smallerIndexNode].push_back(biggerIndexNode);
        this->matrix[biggerIndexNode].push_back(smallerIndexNode);
    }

    void increaseMatrixRows(const unsigned int newSize) {
        const unsigned int numberOfNewRows = newSize - this->matrix.size();
        for (unsigned int i = 0; i < numberOfNewRows; ++i)
                this->matrix.emplace_back();
    }
};

int main() {
    Graph g{};
    g.addRelationship(1, 3);
    g.addRelationship(3, 10);

    Graph graph{"0-3;3-5;5-2;2-4;4-6;6-0;3-1;5-1;2-1;4-1;6-1"};
}
