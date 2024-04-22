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
    bool death_sentence;
public:
    organizm();
    organizm(world* world_point);

    virtual int Action() = 0;
    virtual int Collision(organizm* target) = 0;
    virtual int Fight(organizm* target) = 0;
    virtual bool RejectAttak(organizm* attaker) = 0;
    virtual void Draw(YX position);

    world* GetWorld();

    void SetPosition(YX position);
    YX GetPosition();

    int GetStrength() { return strength; }
    int GetInitiative() { return initiative; }
    void SetBirth(int new_birth) { birth = new_birth; }
    int GetBirth() { return birth; }

    //void IEddardOfTheHouseStartLordOfWinterfellAndWardenOfTheNorthSentenceYouToDie() { death_sentence = true; }
    //bool GetSentence() { return death_sentence; }

    virtual CLASS GetClass() = 0;

    ~organizm();
};