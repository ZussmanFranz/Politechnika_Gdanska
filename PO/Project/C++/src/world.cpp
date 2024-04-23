#include "world.h"
#include "animals.h"
#include "organizm.h"
#include "plants.h"
#include "plants.h"
#include <cstddef>
#include <cstdlib>
#include <ctime> 
#include <ncurses.h>
#include <vector>


world::world(int y, int x, YX field_size, YX padding)
{
    //initialising random for the whole project
    srand(time(NULL));

    //initialasing color pairs for different types
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);

    //Logger initialisation
    Logger = new logmanager("log.txt");

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

    SortMembers();
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

field* world::GetFreeFieldNear(YX position)
{
    std::vector<field*> free_fields;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if ((i == 0) && (j == 0)) {
                continue;
            }

            field* target = FindField({position.y + i, position.x + j});

            if ((target != nullptr) && (target->member == nullptr)) 
            {
                free_fields.push_back(target);
            }
        }
    }

    if (free_fields.size() == 0) {
        return nullptr;
    }

    else {
        return free_fields[rand() % free_fields.size()];
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
void world::Update()
{
    round++;

    //sorting of the vector
    //SortMembers();

    for (int i = 0; i < members.size(); i++)
    {
        if (members.size() <= 1)
        {
            end = true;
        }
        
        if (end)
        {
            return;
        }
        
        // //diagnostics
        // if (dynamic_cast<plant*>(members[i])) {
        //     printw("plant's turn\n");
        //     getch();
        // }

        members[i]->Action();
    }
}

void world::Add(organizm* added)
{
    added->SetBirth(round);
    members.push_back(added);
    FindField(added->GetPosition())->member = added;

    SortMembers();
}

void world::Destroy(organizm* destroyed)
{
    Logger->NecroLog(destroyed);

    FindField(destroyed->GetPosition())->member = nullptr;

    //auto it = std::find(members.begin(), members.end(), destroyed);
    organizm* it = nullptr;
    int index;

    for (int i = 0; i < members.size(); i++) {
        if (members[i] == destroyed) {
            it = members[i];
            index = i;
        }
    }

    if (it == nullptr) { return; }

    if (dynamic_cast<player*>(it) != nullptr)
    {
        end = true;
    }

    delete destroyed;
    members.erase(members.begin() + index);

    SortMembers();
}
void world::SortMembers()
{
    std::sort(members.begin(), members.end(), [](organizm* a, organizm* b)
    {
        int aInitiative = a->GetInitiative();
        int bInitiative = b->GetInitiative();
        int aBirthRound = a->GetBirth();
        int bBirthRound = b->GetBirth();
        
        if (aInitiative == bInitiative)
        {
            return aBirthRound > bBirthRound;
        }
        return aInitiative > bInitiative; 
    });

    Logger->LogOrder(members);
}


void world::GenerateRandomOrganizm()
{
    field* random = GetRandomField();
    if (random == nullptr)
    {
        clear();
        printw("There is no free field!");
        getch();
        return;
    }
    

    int type = rand() % 2 + 1; // Generates 1 or 2
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
    }
    else if (type == 2) // plant
    {
        switch (sub_type)
        {
        case 1:
            // grass
            Add(new grass(random->id, this));
            break;
        case 2:
            // mlecz
            Add(new mlecz(random->id, this));
            break;
        case 3:
            // guarana
            Add(new guarana(random->id, this));
            break;
        case 4:
            // wolfberry
            Add(new wolfberry(random->id, this));
            break;
        case 5:
            // hogweed
            Add(new hogweed(random->id, this));
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
    delete Logger;

    for (organizm* org : members) {
        delete org;
    }

    members.clear();

    for (int i = 0; i < dimensions.y; i++) 
    {
        delete[] fields[i];
    }

    delete[] fields;
    // delete Logger;
}
