#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>
#include <unordered_map>
#include "GameState.h"

class GameState;
class Upgrade;

class Building
{
    public:
        virtual ~Building();

        std::string name;
        double basePrice;
        double baseCps;
        unsigned int id;

        std::vector<Upgrade*> upgrades;

        double GetCps(GameState* game);

        static void Initialize();

        static Building* Get(unsigned int id);
        static Building* Get(std::string name);
        static std::vector<Building*> GetList();

    protected:
        Building(std::string name, double basePrice, double baseCps);

        static std::vector<Building*> List;
        static std::unordered_map<std::string, unsigned int> NameIdMap;

    private:
};

#endif // BUILDING_H
