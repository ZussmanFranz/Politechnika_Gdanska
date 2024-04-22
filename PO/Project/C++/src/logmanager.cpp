#include "logmanager.h"
#include "animals.h"
#include "organizm.h"

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
    }//add plants here!
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

    logFile << "winner is " << GetEntityName(winner).c_str() << "\n\n";

    return;
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