#include <iostream>
#include <sstream>


class Hashmap {
    int size;
    int* keys;
    int* values;
    int* deleted;

    static constexpr int DEFAULT_HASHMAP_SIZE = 50;
    static constexpr int EMPTY_KEY_VALUE = INT_MIN;
public:
    Hashmap() :
        size(DEFAULT_HASHMAP_SIZE), keys(new int[DEFAULT_HASHMAP_SIZE]{}), values(new int[DEFAULT_HASHMAP_SIZE]{}),
        deleted(new int[DEFAULT_HASHMAP_SIZE]{}) {
        for (int i = 0; i < DEFAULT_HASHMAP_SIZE; ++i)
            *(this->keys + i) = EMPTY_KEY_VALUE;
    }

    Hashmap(const int& size) :
        size(size), keys(new int[size]{}), values(new int[size]{}),
        deleted(new int[size]{}) {
        for (int i = 0; i < size; ++i)
            *(this->keys + i) = EMPTY_KEY_VALUE;
    }

    bool insert(const int& key, const int& value) {
        int hashIndex = key % this->size;
        int quadraticNumber{};

        while (hashIndex < this->size) {
            if (*(this->keys + hashIndex) == EMPTY_KEY_VALUE || *(this->deleted + hashIndex) == 1) {
                *(this->keys + hashIndex) = key;
                *(this->values + hashIndex) = value;
                *(this->deleted + hashIndex) = 0;
                return true;
            }
            ++quadraticNumber;
            hashIndex = (key % size + quadraticNumber * quadraticNumber) % size;
        }

        return false;
    }

    int find(const int& key) {
        int hashIndex = key % this->size;
        int quadraticNumber{};

        while (hashIndex < this->size) {
            if (*(this->keys + hashIndex) == key) {
                if (*(this->deleted + hashIndex) == 0)
                    return *(this->values + hashIndex);
                return -1;
            }

            if (*(this->keys + hashIndex) == EMPTY_KEY_VALUE)
                return -1;

            ++quadraticNumber;
            hashIndex = (key % size + quadraticNumber * quadraticNumber) % size;
        }

        return -1;
    }

    bool del(const int& key) {
        int hashIndex = key % this->size;
        int quadraticNumber{};

        while (hashIndex < this->size) {
            if (*(this->keys + hashIndex) == key) {
                if (*(this->deleted + hashIndex) == 0) {
                    *(this->deleted + hashIndex) = 1;
                    return true;
                }
                return false;
            }

            if (*(this->keys + hashIndex) == EMPTY_KEY_VALUE)
                return false;

            ++quadraticNumber;
            hashIndex = (key % size + quadraticNumber * quadraticNumber) % size;
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
        if (const int currentKey = *(hashmap.keys + i); currentKey != Hashmap::EMPTY_KEY_VALUE && *(hashmap.deleted + i) == 0)
            os << "  [" << currentKey << "] -> " << *(hashmap.values + i) << '\n';
    }
    return os;
}


int main() {
    Hashmap hashmap{10};

    hashmap.insert(10, 1);
    // hashmap.del(10);
    hashmap.insert(100, 10);
    hashmap.insert(1000, 100);

    std::cout << hashmap;

    return 0;
}
