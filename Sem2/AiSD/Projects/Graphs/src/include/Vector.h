#pragma once
#include "Vertex.h"
#include <cstddef>

class Vector {
private:
    Vertex* elements;
    int capacity;
    int size;

    // Reserve capacity for the vector
    void reserve(int new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }
        Vertex* new_elements = new Vertex[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_elements[i] = elements[i];
        }
        delete[] elements;
        elements = new_elements;
        capacity = new_capacity;
    }
public:
    Vector() : elements(nullptr), capacity(0), size(0) {}

    // Destructor
    ~Vector() {
        delete[] elements;
    }

    // Copy constructor
    Vector(const Vector& other) {
        capacity = other.capacity;
        size = other.size;
        elements = new Vertex[capacity];
        for (int i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    // Assignment operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new Vertex[capacity];
            for (int i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    // Push back an element
    void push_back(const Vertex& vertex) {
        if (size == capacity) {
            if (capacity == 0) {
                reserve(1);
            } else {
                reserve(2 * capacity);
            }
        }
        elements[size++] = vertex;
    }
    

    // Remove element at the specified index
    void remove(int index) {
        if (index < 0 || index >= size) {
            // Invalid index
            return;
        }

        // Shift elements to the right to fill the gap
        for (int i = index; i < size - 1; ++i) {
            elements[i] = elements[i + 1];
        }
        delete &elements[size - 1];

        --size;
    }

    // Access an element by index
    Vertex& operator[](int index) {
        return elements[index];
    }

    const Vertex& operator[](int index) const {
        return elements[index];
    }

    Vertex* at(int index) {
        return &elements[index];
    }

    // Get the current size of the vector
    int getSize() const {
        return size;
    }

    Vertex* getNextVertex() {
        if (size == 0) {
            return nullptr;
        }

        int max_saturation = -1;
        int max_degree = -1;
        int index = -1;

        for (int i = 0; i < size; i++) {
            if ((elements[i].getSaturation() > max_saturation) || ((elements[i].getSaturation() == max_saturation) && (elements[i].getDegree() > max_degree))) {
                max_saturation = elements[i].getSaturation();
                max_degree = elements[i].getDegree();
                index = i;
            }
        }

        if (index != -1) {
            Vertex* found = new Vertex(elements[index]);
            remove(index);
            return found;
        }
    }
};
