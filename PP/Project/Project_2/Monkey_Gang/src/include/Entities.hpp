#pragma once
#include <stdio.h>
#include "GameObject.hpp"

class Entities
{
private:
    int size;
    int capacity;
    GameObject** game_objects;
public:
    Entities()
    {
        size = 0;
        capacity = 10;
        game_objects = new GameObject*[capacity];
    }
    ~Entities()
    {
        delete[] game_objects;
    }

    GameObject* At(int index) {
        if (index < 0 || index >= size) {
            printf("Index out of bounds!");
            return NULL;
        }
        return game_objects[index];
    }

    void AppendObject(GameObject* object)
    {
        if (size >= capacity)
        {
            capacity *= 2;
            GameObject** newData = new GameObject*[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = game_objects[i];
            }
            delete[] game_objects;
            game_objects = newData;
        }
        game_objects[size++] = object;
        
        printf("Object of the (%c) type appended! New number of objects: (%d)\n", object->type, size);
    }

    void CreateObject(const char* texturesheet, int x, int y, int speed, char type, float scale)
    {
        if (size >= capacity)
        {
            capacity *= 2;
            GameObject** newData = new GameObject*[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = game_objects[i];
            }
            delete[] game_objects;
            game_objects = newData;
        }
        game_objects[size++] = new GameObject(texturesheet, x, y, speed, type, scale);
        
        printf("Object of the (%c) type created! New number of objects: (%d)\n", game_objects[size - 1]->type, size);
    }

    void DestroyObject(GameObject* object)
    {
        for (int i = 0; i < size; i++)
        {
            if (game_objects[i] == object)
            {
                printf("Object of type (%c) found...", game_objects[i]->type);

                delete game_objects[i];

                for (int b = i + 1; b < size; b++)
                {
                    game_objects[b - 1] = game_objects[b];
                }
                game_objects[size] = nullptr;
                size--;

                printf(" ...and succesfully destroyed! New number of objects: (%d)\n", size);
                return;
            }
        }
        printf("There is no such object.\n");
        return;
    }

    void UpdateObjects()
    {
        for (int i = 0; i < size; i++)
        {
            game_objects[i]->Update();
        }
    }

    void RenderObjects()
    {
        for (int i = 0; i < size; i++)
        {
            game_objects[i]->Render();
        }
        
    }

    int GetSize()
    {
        return size;
    }

    GameObject** GetObjects()
    {
        return game_objects;
    }
};
