#pragma once

#include <cstdio>
class Vertex {
private:
    int id;
    int saturation;
    int degree;
    Vertex* next;
    Vertex* prev;
public:
    Vertex() : id(0), saturation(0), degree(0), next(nullptr) {}

    Vertex(int id, int saturation, int degree)
    : id(id), saturation(saturation), degree(degree), next(nullptr), prev(nullptr) {}

    Vertex(const Vertex& orig) 
    : id(orig.id), saturation(orig.saturation), degree(orig.degree), next(nullptr), prev(nullptr) {}


    // bool operator<(const Vertex& other) const {
    //     printf("operator is comparing vertixes\n\n");
    //     if (saturation == other.saturation) {
    //         if (degree == other.degree) {
    //             return id > other.id;
    //         }
    //         return degree < other.degree;
    //     }
    //     return saturation < other.saturation;
    // }

    bool lesser_than(Vertex* other)
    {
        // printf("operator is comparing vertixes\n\n");
        if (saturation == other->getSaturation()) {
            if (degree == other->getDegree()) {
                return id > other->getId();
            }
            return degree < other->getDegree();
        }
        return saturation < other->getSaturation();
    }

    int getId() { return id; }
    void setId(int new_id) { id = new_id; }

    int getSaturation() { return saturation; }
    void setSaturation(int new_saturation) { saturation = new_saturation; }

    int getDegree() { return degree; }
    void setDegree(int new_degree) { degree = new_degree; }

    Vertex* getNext() { return next; }
    void setNext(Vertex* new_next) { next = new_next; }

    Vertex* getPrev() { return prev; }
    void setPrev(Vertex* new_prev) { prev = new_prev; }

    ~Vertex()
    {}
};
