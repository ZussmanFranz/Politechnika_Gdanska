#include "logmanager.h"
#include "animals.h"
#include "plants.h"
#include "organizm.h"
#include "plants.h"
#include <cstdarg>
#include <ncurses.h>
#include <string>

logmanager::logmanager(const char* filepath)
:filepath(filepath), logFile(filepath)
{
    if (logFile.is_open()) 
    {
        logFile << "---!log started!---\n";
    } else {
        // Print an error message if the file couldn't be opened
        std::cerr << "Error: Unable to open log file for writing.\n";
    }

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    logWindow = newwin(max_y, max_x * 0.4, 0, max_x * 0.6);

    init_pair(NORMAL, COLOR_WHITE, -1);
    init_pair(SPAWN, COLOR_GREEN, -1);
    init_pair(FIGHT, COLOR_YELLOW, -1);
    init_pair(DEATH, COLOR_RED, -1);
    init_pair(WARNING, COLOR_CYAN, -1);
    init_pair(ABILITY, COLOR_BLUE, -1);
    init_pair(TECHNICAL, COLOR_MAGENTA, -1);

    //box(logWindow, 0, 0);
    scrollok(logWindow, TRUE);
    wrefresh(logWindow);

    LogF(TECHNICAL, "---!log started!---\n\n");
}

std::string logmanager::GetEntityName(organizm* entity)
{
    if (dynamic_cast<player*>(entity) != nullptr)
    {
        return "player";
    }
    else if (dynamic_cast<wolf*>(entity) != nullptr)
    {
        return "wolf";
    }
    else if (dynamic_cast<sheep*>(entity) != nullptr)
    {
        return "sheep";
    }
    else if (dynamic_cast<fox*>(entity) != nullptr)
    {
        return "fox";
    }
    else if (dynamic_cast<turtle*>(entity) != nullptr)
    {
        return "turtle";
    }
    else if (dynamic_cast<antelope*>(entity) != nullptr)
    {
        return "antelope";
    }
    else if (dynamic_cast<grass*>(entity) != nullptr)
    {
        return "grass";
    }
    else if (dynamic_cast<mlecz*>(entity) != nullptr)
    {
        return "mlecz";
    }
    else if (dynamic_cast<guarana*>(entity) != nullptr)
    {
        return "guarana";
    }
    else if (dynamic_cast<wolfberry*>(entity) != nullptr)
    {
        return "wolfberry";
    }
    else if (dynamic_cast<hogweed*>(entity) != nullptr)
    {
        return "hogweed";
    }
    else
    {
        return "ERROR";
    }
}

void logmanager::Log(std::string prompt)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << prompt << '\n';
    LogF(WARNING, (prompt + "\n\n").c_str());

    return;
}

void logmanager::LogF(int color, const char* prompt, ...)
{
    wattron(logWindow, COLOR_PAIR(color));
    va_list args;
    va_start(args, prompt);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), prompt, args);

    std::string logMessage = std::string(buffer);
    wprintw(logWindow, logMessage.c_str());
    wrefresh(logWindow);

    va_end(args);
    wattroff(logWindow, COLOR_PAIR(color));
}


void logmanager::LogTime()
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << "current time is " << time(NULL) << "\n\n";
}

void logmanager::LogCreation(organizm* created)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << "Created " << GetEntityName(created) << " at y = " << created->GetPosition().y << " x = " << created->GetPosition().x << '\n';

    LogF(SPAWN, "Created %s at y = %d and x = %d\n\n",GetEntityName(created).c_str() , created->GetPosition().y, created->GetPosition().x);
    return;
}

void logmanager::LogCollision(organizm* attaker, organizm* prey)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }
    
    std::string attaker_name = GetEntityName(attaker).c_str();
    std::string prey_name = GetEntityName(prey).c_str();

    logFile << "Fight log: " << attaker_name << " vs " << prey_name << "\n";

    logFile << "location: y = " << prey->GetPosition().y << " x = " << prey->GetPosition().x << "\n";

    logFile << "round: " << attaker->GetWorld()->GetRound() << '\n';

    logFile << attaker_name << " strength = " << attaker->GetStrength() << ", " << prey_name << " strength = " << prey->GetStrength() << '\n';

    LogF(FIGHT, ("Fight: " + attaker_name + " vs " + prey_name + "\n").c_str());

    return;
}

void logmanager::LogCollisionResult(organizm* winner)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << "the winner is " << GetEntityName(winner).c_str() << "\n\n";

    //LogF(FIGHT, ("Winner: " + GetEntityName(winner)).c_str());

    return;
}

void logmanager::LogReproductionCollision(organizm* roditiel1, organizm* roditiel2)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << GetEntityName(roditiel1).c_str() << " and " << GetEntityName(roditiel2).c_str() << " now have a child!\n\n";

    return;
}

void logmanager::LogOrder(std::vector<organizm*> members)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << "The New Order:\n";

    for (int i = 0; i < members.size(); i++) 
    {
        logFile << i << ") " << GetEntityName(members[i]) << '\n';
    }

    logFile << '\n';

    return;
}

void logmanager::LogStrengthIncrease(organizm* lucky_boy)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << "Strength of the " << GetEntityName(lucky_boy) << " has been increased by 3, new strength is " << lucky_boy->GetStrength() << '\n';

    LogF(ABILITY, "Strength of the %s has been increased by 3, new strength is %d\n\n", GetEntityName(lucky_boy).c_str(), lucky_boy->GetStrength());

    return;
}

void logmanager::LogOverpopulation(organizm* unlucky_boy, int neighbours)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << GetEntityName(unlucky_boy).c_str() << " has died because of overpopulation, it had " << neighbours << " neighbours\n\n";

    return;
}

void logmanager::NecroLog(organizm* RIP)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << GetEntityName(RIP).c_str() << " is dead :(\nIt's age was " << RIP->GetWorld()->GetRound() - RIP->GetBirth() << "\n\n";

    LogF(DEATH, "%s died at (y = %d, x = %d), it's age was %d\n\n", GetEntityName(RIP).c_str(), RIP->GetPosition().y, RIP->GetPosition().x, RIP->GetWorld()->GetRound() - RIP->GetBirth());

    return;
}

logmanager::~logmanager()
{
    if (logFile.is_open()) 
    {
        logFile << "---!log ended!---";
        logFile.close();
    }

    delwin(logWindow);   
}