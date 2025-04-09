#include <iostream>
#include <sstream>

class Hashmap {
    struct HashmapNode {
        int key;
        int value;
        HashmapNode *next;
    };

    static constexpr int DEFAULT_HASHMAP_SIZE = 50;
    int size;
    HashmapNode **hashmapNodesArray;

public:
    Hashmap()
        : size(DEFAULT_HASHMAP_SIZE), hashmapNodesArray(new HashmapNode *[DEFAULT_HASHMAP_SIZE]{}) {}

    Hashmap(const int &size)
        : size(std::max(size, 1)), hashmapNodesArray(new HashmapNode *[std::max(size, 1)]) {}


    void insert(const int &key, const int &value) {
        const int hashIndex = key % this->size;

        HashmapNode *hashmapNode = *(this->hashmapNodesArray + hashIndex);

        if (!hashmapNode)
            *(this->hashmapNodesArray + hashIndex) = new HashmapNode{key, value, nullptr};

        else {
            while (hashmapNode) {
                if (key < hashmapNode->key) {
                    HashmapNode *newHashmapNode = new HashmapNode{key, value, hashmapNode};
                    *(this->hashmapNodesArray + hashIndex) = newHashmapNode;
                    break;
                }
                if (key == hashmapNode->key) {
                    hashmapNode->value = value;
                    break;
                }
                if (!hashmapNode->next) {
                    hashmapNode->next = new HashmapNode{key, value, nullptr};
                    break;
                }
                hashmapNode = hashmapNode->next;
            }
        }
    }

    int find(const int &key) const {
        const int hashIndex = key % this->size;

        HashmapNode *hashmapNode = *(this->hashmapNodesArray + hashIndex);

        while (hashmapNode) {
            if (hashmapNode->key == key)
                return hashmapNode->value;

            hashmapNode = hashmapNode->next;
        }
        return -1;
    }

    bool del(const int &key) {
        const int hashIndex = key % this->size;

        HashmapNode *hashmapNode = *(this->hashmapNodesArray + hashIndex);

        if (!hashmapNode)
            return false;

        HashmapNode *previous = nullptr;
        while (hashmapNode) {
            if (hashmapNode->key == key) {
                if (previous) {
                    previous->next = hashmapNode->next;
                    delete hashmapNode;
                    return true;
                }
                HashmapNode *next = hashmapNode->next;
                delete hashmapNode;
                *(this->hashmapNodesArray + hashIndex) = next;
                return true;
            }
            previous = hashmapNode;
            hashmapNode = hashmapNode->next;
        }
        return false;
    }

    ~Hashmap() {
        for (int i = 0; i < this->size; ++i) {
            HashmapNode *hashmapNode = *(this->hashmapNodesArray + i);

            while (hashmapNode) {
                HashmapNode *next = hashmapNode->next;
                delete hashmapNode;
                hashmapNode = next;
            }
        }
        delete[] this->hashmapNodesArray;

    }

    friend std::ostream &operator<<(std::ostream &os, const Hashmap &hashmap);
};

std::ostream &operator<<(std::ostream &os, const Hashmap &hashmap) {
    os << "HashMap: \n";

    for (int i = 0; i < hashmap.size; ++i) {
        auto hashMapNode = *(hashmap.hashmapNodesArray + i);
        while (hashMapNode) {
            os << "  [" << hashMapNode->key << "] -> " << hashMapNode->value << '\n';
            hashMapNode = hashMapNode->next;
        }
    }
    return os;
}


int main() {
    Hashmap hashmap;

    hashmap.insert(1, 213);

    hashmap.insert(10, 100);
    hashmap.insert(60, 200); // 10 and 60 will collide if size = 50
    hashmap.insert(110, 300); // same index again

    // hashmap.del(60);  // delete from the middle of the chain
    std::cout << hashmap;

    return 0;
}
