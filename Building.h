#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>
#include <unordered_map>
#include "GameState.h"

class GameState;

class Building
{
    public:
        virtual ~Building();

        std::string name;
        double basePrice;
        double baseCps;
        unsigned int id;

        double GetCps(GameState* game);

        static void InitializeBuildings();
        static Building* Get(unsigned int id);
        static Building* Get(std::string name);
        static std::vector<Building*> GetList();

    protected:
        Building(std::string name, double basePrice, double baseCps);

        static std::vector<Building*> BuildingList;
        static std::unordered_map<std::string, unsigned int> BuildingNameIdMap;

    private:
};

#endif // BUILDING_H
