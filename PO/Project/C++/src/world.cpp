#include "world.h"
#include "animals.h"
#include <cstdlib>
#include <ctime> 


world::world(int y, int x, YX field_size, YX padding)
{
    //initialising random for the whole project
    srand(time(NULL));

    round = 0;
    end = false;
    dimensions = {y, x};
    this->field_size = field_size;
    this->padding = padding;

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

    player* Player = new player(this, {0,0});
    Add(Player);

    GenerateRandomStart(5);
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

field* world::GetRandomField()
{
    std::vector<field*> free_fields;

    for (int y = 0; y < dimensions.y; y++)
    {
        for (int x = 0; x < dimensions.x; x++)
        {
            if (fields[y][x].member == nullptr)
            {
                free_fields.push_back(&(fields[y][x]));
            }   
        }
    }
    
    int n_free_fields = free_fields.size();

    if (n_free_fields == 0)
    {
        return nullptr;
    }
    else
    {
        return free_fields[ rand() % n_free_fields ];
    }
}

void world::Draw()
{
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) 
        {
            mvprintw(20 + i + j, 2, "i: %d j: %d", i, j);
            getch();

            fields[i][j].draw_box(field_size);
            if (fields[i][j].member != nullptr) 
            {
                mvprintw(i + j, 2, "encounter an entity!");
                getch();
                fields[i][j].member->Draw({fields[i][j].position.y + fields[i][j].field_size.y/2, fields[i][j].position.x + fields[i][j].field_size.x/2});
                getch();
            }
        }
    }

    //organizmy->Draw()
}
void world::Update(char input)
{
    round++;

    for (organizm* org : members) { // i should add the initiative and age check
        if (player* player_ptr = dynamic_cast<player*>(org)) {
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
    added->SetBirth(round);
    members.push_back(added);
    FindField(added->GetPosition())->member = added;
}

void world::Destroy(organizm* destroyed)
{
    FindField(destroyed->GetPosition())->member = nullptr;
    
    for (std::vector<organizm*>::iterator it = members.begin(); it != members.end(); ++it) {
    if (*it == destroyed) {
        if (dynamic_cast<player*>(*it) != nullptr) {
            end = true;
        }

        delete *it;
        members.erase(it);
        break;
    }
}
}

void world::GenerateRandomOrganizm()
{
    field* random = GetRandomField();
    if (random == nullptr)
    {
        printw("There is no free field!");
        getch();
        return;
    }
    

    int type = rand() % 2 + 1; // Generates 1 or 2

    type = 1; // !set type to 1 because plants are incomplete!

    int sub_type = rand() % 5 + 1; // Generates from 1 to 5

    if (type == 1) // animal
    {
        switch (sub_type)
        {
        case 1:
            // wolf
            Add(new wolf(this, random->id));
            break;
        case 2:
            // sheep
            Add(new sheep(this, random->id));
            break;
        case 3:
            // fox
            Add(new fox(this, random->id));
            break;
        case 4:
            // turtle
            Add(new turtle(this, random->id));
            break;
        case 5:
            // antelope
            Add(new antelope(this, random->id));
            break;
        default:
            break;
        }

        printw("created an animal with the i = %d and j = %d", random->id.y, random->id.x);
        getch();
    }
    else if (type == 2) // plant
    {
        switch (sub_type)
        {
        case 1:
            // grass
            break;
        case 2:
            // mlecz
            break;
        case 3:
            // guarana
            break;
        case 4:
            // wolfberry
            break;
        case 5:
            // hogweed
            break;
        default:
            break;
        }
    }
}

void world::GenerateRandomStart(int number_of_organizms)
{
    for (int object = 0; object < number_of_organizms; object++)
    {
        GenerateRandomOrganizm();   
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
