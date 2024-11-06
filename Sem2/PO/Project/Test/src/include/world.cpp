#include "world.h"


world::world(int y, int x, YX field_size, YX padding)
:dimensions({y,x}), field_size(field_size), padding(padding), round(0)
{
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    YX starting_padding = {2, max_x/2 - (x/2*(field_size.x + padding.x))};

    fields = new field*[y];

    for (int i = 0; i < y; i++) {
        fields[i] = new field[x];
    }

    // Initializing fields
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) 
        {
            fields[i][j].field_size = field_size;

            fields[i][j].position.y = i * (field_size.y + padding.y) + starting_padding.y;
            fields[i][j].id.y = i;
            fields[i][j].position.x = j * (field_size.x + padding.x) + starting_padding.x;
            fields[i][j].id.x = j;

            fields[i][j].member = nullptr;
        }
    }
}


field* world::FindField(YX id)
{
    if ((id.y <= dimensions.y) && (id.y >= 0) && (id.x <= dimensions.x) && (id.x >= 0))
    {
        return &(fields[id.y][id.x]);
    }
    else
    {
        return nullptr;
    }
}

void world::Draw()
{
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) 
        {
            fields[i][j].draw_box(field_size);
            if (fields[i][j].member != nullptr) 
            {
                fields[i][j].member->Draw({fields[i][j].position.y + fields[i][j].field_size.y/2, fields[i][j].position.x + fields[i][j].field_size.x/2});
            }
        }
    }

    //organizmy->Draw()
}
void world::Update(char input)
{
    round++;

    for (auto* org : members) { // i should add the initiative and age check
        if (auto player_ptr = dynamic_cast<player*>(org))
        {
            player_ptr->Action(input);
        }
        else
        {
            org->Action();
        }
    }

}

void world::Add(organizm* added)
{
    members.push_back(added);
    FindField(added->GetPosition())->member = added;
}

void world::Destroy(organizm* destroyed)
{
    FindField(destroyed->GetPosition())->member = nullptr;
    
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (*it == destroyed) 
        {
            delete *it;
            members.erase(it);
            break;
        }
    }
}

world::~world()
{
    for (auto it = members.begin(); it != members.end(); ++it) {
        delete *it;
        members.erase(it);
        break;
    }

    for (int i = 0; i < dimensions.y; i++) 
    {
        delete[] fields[i];
    }

    delete[] fields;
}

