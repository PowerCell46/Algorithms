#include <iostream>
#include <sstream>


class Hashmap {
    static const int DEFAULT_HASHMAP_SIZE = 50;
    int size;
    int* keys;
    int* values;
    int* deleted;
public:
    Hashmap() :
        size(DEFAULT_HASHMAP_SIZE), keys(new int[DEFAULT_HASHMAP_SIZE]{}), values(new int[DEFAULT_HASHMAP_SIZE]{}),
        deleted(new int[DEFAULT_HASHMAP_SIZE]{}) {
        for (int i = 0; i < DEFAULT_HASHMAP_SIZE; ++i)
            *(this->keys + i) = INT_MIN;
    }

    Hashmap(const int& size) :
        size(size), keys(new int[size]{}), values(new int[size]{}),
        deleted(new int[size]{}) {
        for (int i = 0; i < size; ++i)
            *(this->keys + i) = INT_MIN;
    }

    bool insert(const int& key, const int& value) {
        int hashIndex = key % this->size;

        while (hashIndex < this->size) {
            if (*(this->keys + hashIndex) == INT_MIN || *(this->deleted + hashIndex) == 1) {
                *(this->keys + hashIndex) = key;
                *(this->values + hashIndex) = value;
                *(this->deleted + hashIndex) = 0;
                return true;
            }
            ++hashIndex;
        }

        return false;
    }

    int find(const int& key) {
        int hashIndex = key % this->size;

        while (hashIndex < this->size) {
            if (*(this->keys + hashIndex) == key) {
                if (*(this->deleted + hashIndex) == 0)
                    return *(this->values + hashIndex);
                return -1;
            }

            if (*(this->keys + hashIndex) == INT_MIN)
                return -1;

            ++hashIndex;
        }

        return -1;
    }

    bool del(const int& key) {
        int hashIndex = key % this->size;

        while (hashIndex < this->size) {
            if (*(this->keys + hashIndex) == key) {
                if (*(this->deleted + hashIndex) == 0) {
                    *(this->deleted + hashIndex) = 1;
                    return true;
                }
                return false;
            }

            if (*(this->keys + hashIndex) == INT_MIN)
                return false;

            ++hashIndex;
        }

        return false;
    }

    ~Hashmap() {
        delete[] this->keys;
        delete[] this->values;
        delete[] this->deleted;
    }

    friend std::ostream& operator<<(std::ostream& os, const Hashmap& hashmap);
};


std::ostream& operator<<(std::ostream& os, const Hashmap& hashmap) {
    os << "Hash map:\n";
    for (int i = 0; i < hashmap.size; ++i) {
        if (const int currentKey = *(hashmap.keys + i); currentKey != INT_MIN && *(hashmap.deleted + i) == 0)
            os << "  [" << currentKey << "] -> " << *(hashmap.values + i) << '\n';
    }
    return os;
}


int main() {
    Hashmap hashmap{10};

    hashmap.insert(10, 1);
    // hashmap.del(10);

    hashmap.insert(100, 10);

    std::cout << hashmap;

    return 0;
}
