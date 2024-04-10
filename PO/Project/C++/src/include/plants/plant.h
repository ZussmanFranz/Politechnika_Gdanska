#ifndef PLANT_H
#define PLANT_H


#include "organizm.h"

class plant: public virtual organizm
{
protected:
    
public:
    plant(world* world_point):organizm(world_point) { initiative = 0; };

    void Draw(YX position) override;

    CLASS GetClass() override { return PLANT; }

    ~plant();
};

plant::~plant()
{
}

void plant::Draw(YX position)
{
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    
    attron(COLOR_PAIR(1));
    
    mvprintw(position.y, position.x, &avatar);
    
    attroff(COLOR_PAIR(1));
}

#endif // PLANT_H