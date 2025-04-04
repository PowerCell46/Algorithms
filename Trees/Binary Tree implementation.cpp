#include <iostream>

class Node {
public:
    Node *leftChild;
    int data;
    Node *rightChild;
};

class Queue {
    int front;
    int rear;
    int size;
    Node **Q;

public:
    Queue() : front(-1), rear(-1), size(10), Q(new Node *[size]) {}
    Queue(int size) : front(-1), rear(-1), size(size), Q(new Node *[size]) {}

    void enqueue(Node *node) {
        if (rear == size - 1) {
            std::cout << "Queue is full\n";
        } else {
            rear++;
            Q[rear] = node;
        }
    }

    Node *dequeue() {
        if (front == rear) {
            std::cout << "Queue is empty\n";
            return nullptr;
        }
        front++;
        return Q[front];
    }

    void Display() const {
        for (int i = front + 1; i <= rear; ++i)
            std::cout << Q[i]->data << ' ';
        std::cout << "\n";
    }

    bool isEmpty() {
        return front == rear;
    }

    ~Queue() {
        delete[] Q;
    }
};

class Tree {
    Node *root;

public:
    Tree() : root(nullptr) {}

    Node *getRoot() const { return this->root; }

    void createTree();

    void preOrder() const { preOrder(this->root); }
    static void preOrder(Node *p);

    void inOrder() const { inOrder(this->root); }
    static void inOrder(Node *p);

    void postOrder() const { postOrder(this->root); }
    static void postOrder(Node *p);

    void levelOrder() const { levelOrder(this->root); }
    static void levelOrder(Node *p);

    int height() const { return height(this->root); }
    static int height(Node *p);
};

void Tree::createTree() {
    Node *p, *t;
    int x;
    Queue q(100);

    std::cout << "Enter root value: ";
    std::cin >> x;

    root = new Node{nullptr, x, nullptr};
    q.enqueue(root);

    while (!q.isEmpty()) {
        p = q.dequeue();

        std::cout << "Enter left child of " << p->data << " (-1 for no child): ";
        std::cin >> x;
        if (x != -1) {
            t = new Node{nullptr, x, nullptr};
            p->leftChild = t;
            q.enqueue(t);
        }

        std::cout << "Enter right child of " << p->data << " (-1 for no child): ";
        std::cin >> x;
        if (x != -1) {
            t = new Node{nullptr, x, nullptr};
            p->rightChild = t;
            q.enqueue(t);
        }
    }
}

void Tree::preOrder(Node *p) {
    if (p) {
        std::cout << p->data << ' ';
        preOrder(p->leftChild);
        preOrder(p->rightChild);
    }
}

void Tree::inOrder(Node *p) {
    if (p) {
        inOrder(p->leftChild);
        std::cout << p->data << ' ';
        inOrder(p->rightChild);
    }
}

void Tree::postOrder(Node *p) {
    if (p) {
        postOrder(p->leftChild);
        postOrder(p->rightChild);
        std::cout << p->data << ' ';
    }
}

void Tree::levelOrder(Node *p) {
    if (!p) return;
    Queue q(100);

    std::cout << p->data << ' ';
    q.enqueue(p);

    while (!q.isEmpty()) {
        p = q.dequeue();
        if (p->leftChild) {
            std::cout << p->leftChild->data << ' ';
            q.enqueue(p->leftChild);
        }
        if (p->rightChild) {
            std::cout << p->rightChild->data << ' ';
            q.enqueue(p->rightChild);
        }
    }
}

int Tree::height(Node *p) {
    if (!p) return 0;

    int leftHeight = height(p->leftChild);
    int rightHeight = height(p->rightChild);

    return std::max(leftHeight, rightHeight) + 1;
}

int main() {
    Tree tree;

    tree.createTree();

    std::cout << "\nPreOrder: ";
    tree.preOrder();

    std::cout << "\nInOrder: ";
    tree.inOrder();

    std::cout << "\nPostOrder: ";
    tree.postOrder();

    std::cout << "\nLevelOrder: ";
    tree.levelOrder();

    std::cout << "\nHeight: " << tree.height() << "\n";

    return 0;
}
