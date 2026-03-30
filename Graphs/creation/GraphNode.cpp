class GraphNode {
private:
    int value;
    GraphNode** nodes; // GraphNode[]
    size_t nodesSize;

public:
    GraphNode(const int value, GraphNode** nodes, const int nodesSize)
        : value(value), nodes(nodes), nodesSize(nodesSize) {}

    GraphNode(const GraphNode& other) = delete;

    GraphNode& operator=(const GraphNode& other) = delete;
};  

int main() {
    GraphNode* g1 = new GraphNode{10, nullptr, 0};
    GraphNode* g2 = new GraphNode{15, nullptr, 0};
    GraphNode* g3 = new GraphNode{20, new GraphNode*[]{g1, g2}, 2};

    delete g1;
    delete g2;
    delete g3;

    return 0;
}
