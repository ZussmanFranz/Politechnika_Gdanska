#pragma once
#include <fstream>
#include <string>
#include "organizm.h"


class logmanager
{
protected:
    const char* filepath;
    std::ofstream logFile;
public:
    logmanager(const char* filepath);

    std::string GetEntityName(organizm* entity);

    void Log(std::string prompt);

    void LogCollision(organizm* attaker, organizm* prey);
    void LogCollisionResult(organizm* winner);

    void NecroLog(organizm* RIP);

    ~logmanager();
};


