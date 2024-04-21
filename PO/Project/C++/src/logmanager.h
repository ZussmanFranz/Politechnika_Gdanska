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

    void LogCollision(organizm* attaker, organizm* prey, int result);

    ~logmanager();
};


