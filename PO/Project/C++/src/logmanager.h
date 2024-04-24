#pragma once
#include <fstream>
#include <string>
#include <vector>
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

    void LogTime();

    void LogCollision(organizm* attaker, organizm* prey);
    void LogCollisionResult(organizm* winner);

    void LogCreation(organizm* created);

    void LogReproductionCollision(organizm* roditiel1, organizm* roditiel2);

    void LogOrder(std::vector<organizm*> members);

    void LogStrengthIncrease(organizm* lucky_boy);

    void LogOverpopulation(organizm* unlucky_boy, int neighbours);

    void NecroLog(organizm* RIP);

    ~logmanager();
};


