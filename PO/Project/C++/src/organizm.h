#pragma once
class world;

typedef struct {
    int y;
    int x;
} YX;

typedef enum {
    PLANT,
    ANIMAL,
    PLAYER
} CLASS;

class organizm {
protected:
    int strength;
    int initiative;
    int birth;
    YX position;
    world* world_point;
    char avatar;

public:
    organizm();
    organizm(world* world_point);

    virtual void Action() = 0;
    virtual int Collision(organizm* target) = 0;
    virtual void Draw(YX position);

    world* GetWorld();

    void SetPosition(YX position);
    YX GetPosition();

    int GetStrength() { return strength; }
    int GetInitiative() { return initiative; }
    void SetBirth(int new_birth) { birth = new_birth; }
    int GetBirth() { return birth; }

    virtual CLASS GetClass() = 0;

    ~organizm();
};