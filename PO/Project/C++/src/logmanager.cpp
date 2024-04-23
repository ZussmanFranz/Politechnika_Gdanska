#include "logmanager.h"
#include "animals.h"
#include "plants.h"
#include "organizm.h"
#include "plants.h"

logmanager::logmanager(const char* filepath)
:filepath(filepath), logFile(filepath)
{
    logFile << "---!log started!---\n\n";
    // if (logFile.is_open()) 
    // {
    //     logFile << "---!log started!---\n";
    // } else {
    //     // Print an error message if the file couldn't be opened
    //     std::cerr << "Error: Unable to open log file for writing.\n";
    // }
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
    
    return;
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
}

void logmanager::NecroLog(organizm* RIP)
{
    if (!logFile.is_open())
    {
        //error!
        return;
    }

    logFile << GetEntityName(RIP).c_str() << " is dead :(\nIt's age was " << RIP->GetWorld()->GetRound() - RIP->GetBirth() << "\n";

    return;
}

logmanager::~logmanager()
{
    if (logFile.is_open()) 
    {
        logFile << "---!log ended!---";
        logFile.close();
    }   
}