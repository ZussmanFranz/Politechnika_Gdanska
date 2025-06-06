#include "world.h"
#include "animal.h"
#include "animals.h"
#include "logmanager.h"
#include "organizm.h"
#include "plant.h"
#include "plants.h"
#include "plants.h"
#include "player.h"
#include <cstddef>
#include <cstdlib>
#include <ctime> 
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include <fstream>
//#include<unistd.h>


world::world(const char* filepath)
{
    dimensions.y = 12;
    dimensions.x = 12;

    initscr();
    start_color();
    use_default_colors();

    //initialasing color pairs for different types
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    window_width = max_x * 0.6;
    window_height = max_y;

    //initialasing a world's window
    worldWindow = newwin(max_y, window_width, 0, 0);

    noecho(); 
    curs_set(0);

    //initialising random for the whole project
    srand(time(NULL));

    //Logger initialisation
    Logger = new logmanager("log.txt");

    round = 0;
    end = false;
    this->field_size = {3, 5};
    this->padding = {0, 1};

    YX starting_padding = {2, window_width/2 - (dimensions.x/2*(field_size.x + padding.x))};

    Load(filepath);

    fields = new field*[dimensions.y];

    for (int i = 0; i < dimensions.y; i++) {
        fields[i] = new field[dimensions.x];
    }

    // Initializing fields
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) 
        {
            fields[i][j].window = worldWindow;

            fields[i][j].field_size = field_size;

            fields[i][j].position.y = i * (field_size.y + padding.y) + starting_padding.y;
            fields[i][j].id.y = i;
            fields[i][j].position.x = j * (field_size.x + padding.x) + starting_padding.x;
            fields[i][j].id.x = j;

            fields[i][j].member = nullptr;
        }
    }
    
    update_order = 0;

    for (int i = 0; i < members.size(); i++) {
        fields[members[i]->GetPosition().y][members[i]->GetPosition().x].member = members[i];
        if (dynamic_cast<player*>(members[i]) != nullptr) {
            update_order = i;
        }
    }

    SortMembers();
}

world::world(int y, int x)
{
    initscr();
    start_color();
    use_default_colors();

    //initialasing color pairs for different types
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    window_width = max_x * 0.6;
    window_height = max_y;

    //initialasing a world's window
    worldWindow = newwin(max_y, window_width, 0, 0);

    noecho(); 
    curs_set(0);

    //initialising random for the whole project
    srand(time(NULL));

    //Logger initialisation
    Logger = new logmanager("log.txt");

    round = 0;
    end = false;
    dimensions = {y, x};
    this->field_size = {3, 5};
    this->padding = {0, 1};

    YX starting_padding = {2, window_width/2 - (x/2*(field_size.x + padding.x))};

    fields = new field*[y];

    for (int i = 0; i < y; i++) {
        fields[i] = new field[x];
    }

    // Initializing fields
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) 
        {
            fields[i][j].window = worldWindow;

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

    //GenerateRandomStart((y * x) / 6);
    GenerateEvenStart((y * x) / 12);

    update_order = 0;

    SortMembers();
}


field* world::FindField(YX id)
{
    if ((id.y < dimensions.y) && (id.y >= 0) && (id.x < dimensions.x) && (id.x >= 0))
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

std::vector<field*> world::GetFieldsNear(YX position)
{
    std::vector<field*> near;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if ((i == 0) && (j == 0)) {
                continue;
            }

            field* target = FindField({position.y + i, position.x + j});

            if (target != nullptr) 
            {
                near.push_back(target);
            }
        }
    }

    return near;
}

void world::Draw()
{
    wclear(worldWindow);

    DrawInterface();

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
    return;
}

void world::DrawInterface()
{
    mvwprintw(worldWindow,1, window_width/2 - 5, "Round is %d", round);
    mvwprintw(worldWindow,0, window_width/2 - 15, "Yauheni Pyryeu 201253 project");
    mvwprintw(worldWindow,window_height - 1, window_height/2 - 14, "q - quit, e - ability, w a s d - controls");
    
    return;
}

void world::DrawEndscreen()
{
    wclear(worldWindow);
    //wclear(Logger->GetWindow());

    mvwprintw(worldWindow,0, window_width/2 - 6, "End of Game!");
    mvwprintw(worldWindow,1, window_width/2 - 5, "Round is %d", round);
    
    if ((members.size() == 1) && (GetPlayer() != nullptr)) {
        mvwprintw(worldWindow,2, window_width/2 - 7, "You have won!!");
    }
    else if (GetPlayer() == nullptr) {
        mvwprintw(worldWindow,2, window_width/2 - 7, "You have lost!");
    }
    else {
        mvwprintw(worldWindow, 3, window_width/2 - 3, "saved");
        Save("save.txt");
    }

    //Draw();
    Logger->LogF(TECHNICAL, "---!log ended!---");
    wrefresh(Logger->GetWindow());

    wgetch(worldWindow);

    return;
}

organizm* world::GetPlayer()
{
    for (int i = 0; i < members.size(); i++) {
        if (player* player_ptr = dynamic_cast<player*>(members[i])) {
            return player_ptr;
        }
    }

    return nullptr;
}

void world::Update()
{
    round++;

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

        if ((update_order > 0) && (update_order < members.size())) {
            i = update_order;
            update_order = 0;
        }

        members[i]->Action();
    }

    Clean();
}

// void world::SleepMiliseconds(int ms)
// {
//     clock_t goal = ms + clock(); // The end time

//     while (goal > clock());
//     return;
// }

void world::Add(organizm* added)
{
    added->SetBirth(round);
    members.push_back(added);
    FindField(added->GetPosition())->member = added;

    SortMembers();

    Logger->LogCreation(added);

    return;
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

    //Logger->LogOrder(members);
}

int world::CountNeighboursSameType(organizm* me)
{
    int count = 0;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (((i == 0) && (j == 0)) || (FindField({me->GetPosition().y + i, me->GetPosition().x + j}) == nullptr)) {
                continue;
            }

            organizm* target = FindField({me->GetPosition().y + i, me->GetPosition().x + j})->member;

            if ((target != nullptr) && (SameType(target, me))) {
                count++;
            } 
        }
    }

    return count;
}

bool world::SameType(organizm* a, organizm* b)
{
    // Check if both pointers are valid
    if (a && b) {
        // Get the type_info objects
        const std::type_info& type1 = typeid(*a);
        const std::type_info& type2 = typeid(*b);

        // Compare the type_info objects
        return type1 == type2;
    }
    return false; 
}

void world::Clean()
{
    //Logger->Log("cleaning routine...");

    for (int i = 0; i < members.size(); i++) {
        int neighbours = CountNeighboursSameType(members[i]);
        if (neighbours > 2) {
            Logger->LogOverpopulation(members[i], neighbours);
            Destroy(members[i]);
            i--;
        }
    }

    return;
}

void world::GenerateRandomOrganizm(int type, int sub_type)
{
    field* random = GetRandomField();
    if (random == nullptr)
    {
        clear();
        wprintw(worldWindow,"There is no free field!");
        wgetch(worldWindow);
        return;
    }
    

    // int type = rand() % 2 + 1; // Generates 1 or 2
    // int sub_type = rand() % 5 + 1; // Generates from 1 to 5

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
        GenerateRandomOrganizm(rand() % 2 + 1, rand() % 5 + 1);   
    }

    return;
}

void world::GenerateEvenStart(int number_of_organizms)
{
    int type = 1;
    int subtype = 1;
    int count = 0;

    while (count < number_of_organizms)
    {
        type = (type == 1) ? 2 : 1;

        if (count % 2 == 0) 
        {
            subtype = (subtype >= 5) ? 1 : (subtype + 1);
        }

        GenerateRandomOrganizm(type, subtype);
        count++;
    }

    return;
}

void world::Save(const char* filepath)
{
    // Open the file for writing
    std::ofstream file(filepath, std::ios::trunc);
    if (!file.is_open()) {
        // Handle error if file cannot be opened
        Logger->LogF(DEATH, "---!error saving file!---\n");
        std::cerr << "Error: Unable to open save file for writing.\n";
        return;
    }

    // World "info"
    file << dimensions.y << " " << dimensions.x << "\n";
    file << round << "\n";

    //members
    file << members.size() << "\n\n";
    for (int i = 0; i < members.size(); i++) {
        file << members[i]->GetAvatar() << "\n";
        file << members[i]->GetPosition().y << ' ' << members[i]->GetPosition().x << '\n';
        file << members[i]->GetStrength() << '\n';
        file << members[i]->GetBirth() << "\n\n";
    }

    player* player_ptr = dynamic_cast<player*>(GetPlayer());
    file << player_ptr->GetCooldown();

    // Close the file
    file.close();

    Logger->LogF(TECHNICAL, "---!The game is saved!---\n");

    return;
}

void world::Load(const char* filepath)
{
    // Open the save file for reading
    std::ifstream file(filepath);
    if (!file.is_open()) {
        // Handle error if file cannot be opened
        Logger->LogF(DEATH, "---!error loading from file!---\n");
        std::cerr << "Error: Unable to open save file for reading.\n";
        return;
    }

    file >> dimensions.y >> dimensions.x >> round;
    round--;

    int n_entities;
    file >> n_entities;

    for (int i = 0; i < n_entities; i++) {
        char avatar;
        file >> avatar;

        YX e_position;
        int strength, birth;

        file >> e_position.y >> e_position.x;
        file >> strength;
        file >> birth;

        organizm* entity = nullptr;

        switch (avatar) 
        {
            case 'P':
                entity = new player(this,{e_position.y, e_position.x});
                break;
            case 'W':
                entity = new wolf(this,{e_position.y, e_position.x});
                break;
            case 'F':
                entity = new fox(this,{e_position.y, e_position.x});
                break;
            case 'T':
                entity = new turtle(this,{e_position.y, e_position.x});
                break;
            case 'A':
                entity = new antelope(this,{e_position.y, e_position.x});
                break;
            case 'S':
                entity = new sheep(this,{e_position.y, e_position.x});
                break;
            case 'g':
                entity = new grass({e_position.y, e_position.x},this);
                break;
            case 'u':
                entity = new guarana({e_position.y, e_position.x},this);
                break;
            case 'm':
                entity = new mlecz({e_position.y, e_position.x},this);
                break;
            case 'w':
                entity = new wolfberry({e_position.y, e_position.x},this);
                break;
            case 'h':
                entity = new hogweed({e_position.y, e_position.x},this);
                break;
            default:
                break;
        }

        if (entity != nullptr) {
            entity->SetStrength(strength);
            entity->SetBirth(birth);
            members.push_back(entity);
        }
    }

    int cooldown;
    file >> cooldown;

    player* player_ptr = dynamic_cast<player*>(GetPlayer());
    player_ptr->SetCooldown(cooldown - 1);

    // Close the file
    file.close();

    Logger->LogF(TECHNICAL, "---!The game is loaded!---\n");
}

world::~world()
{
    for (organizm* org : members) {
        delete org;
    }

    members.clear();

    for (int i = 0; i < dimensions.y; i++) 
    {
        delete[] fields[i];
    }

    delwin(worldWindow);
    
    delete[] fields;
    delete Logger;  
    endwin();
}
