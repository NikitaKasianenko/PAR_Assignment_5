#include <iostream>
#include <string>
#include <stack>

using namespace std;

class QueueList {
public:
    QueueList() : pointer(0), capacity(10) {
        array = new string[capacity];
    }

    ~QueueList() {
        delete[] array;
    }

    void Add(const string& element) {
        if (pointer == capacity) {
            extendArray();
        }
        array[pointer++] = element;
    }


    string* begin() const {
        return array;
    }

    string* end() const {
        return array + pointer;
    }

private:
    string* array;
    int pointer;
    int capacity;

    void extendArray() {
        int newCapacity = capacity * 2;
        string* extendedArray = new string[newCapacity];
        for (int i = 0; i < capacity; i++) {
            extendedArray[i] = array[i];
        }
        delete[] array;
        array = extendedArray;
        capacity = newCapacity;
    }
};

