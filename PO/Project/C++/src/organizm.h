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
    int starting_strength;
    int initiative;
    int birth;
    bool death_sentence;
    YX position;
    world* world_point;
    char avatar;
public:
    organizm();
    organizm(world* world_point, int strength, int initiative, YX position);

    virtual int Action() = 0;
    virtual int Collision(organizm* target) = 0;
    virtual int Fight(organizm* target) = 0;
    virtual bool RejectAttak(organizm* attaker) = 0;
    virtual void Draw(YX position);

    world* GetWorld();

    void SetPosition(YX position);
    YX GetPosition();

    int GetStrength() { return strength; }
    void SetStrength(int new_strength) { strength = new_strength; }
    int GetInitiative() { return initiative; }
    void SetBirth(int new_birth) { birth = new_birth; }
    int GetBirth() { return birth; }
    bool GetSentence() { return death_sentence; }
    char GetAvatar() {return avatar;}

    void IAmEddarOfHouseStartkLordOfWinterfellAndWardenOfTheNorthSentenceYouToDie() { death_sentence = true; }

    virtual organizm* MakeChild(YX new_position) = 0;
    void Reproduct();

    virtual CLASS GetClass() = 0;

    ~organizm();
};