#pragma once

class Vertex {
private:
    int id;
    int saturation;
    int degree;
    Vertex* next;
public:
    Vertex() : id(0), saturation(0), degree(0), next(nullptr) {}

    Vertex(int id, int saturation, int degree){
        this->id = id;
        this->saturation = saturation;
        this->degree = degree;
        this->next = nullptr;
        return;
    }

    Vertex(const Vertex& orig) 
    : id(orig.id), saturation(orig.saturation), degree(orig.degree), next(nullptr) {}


    bool operator<(const Vertex& other) const {
        if (saturation == other.saturation) {
            if (degree == other.degree) {
                return id > other.id;
            }
            return degree < other.degree;
        }
        return saturation < other.saturation;
    }

    int getId() { return id; }
    void setId(int new_id) { id = new_id; }

    int getSaturation() { return saturation; }
    void setSaturation(int new_saturation) { saturation = new_saturation; }

    int getDegree() { return degree; }
    void setDegree(int new_degree) { degree = new_degree; }

    Vertex* getNext() { return next; }
    void setNext(Vertex* new_next) { next = new_next; }

    ~Vertex()
    {
        if (next != nullptr)
        {
            delete next;
            next = nullptr;   
        }
    }
};