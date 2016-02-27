#include "Building.h"
#include "Upgrades\BuildingMultiplierUpgrade.h"
#include "Upgrades\GrandmaUpgrade.h"

using namespace std;

Building::Building(string name, double basePrice, double baseCps)
{
    this->name = name;
    this->basePrice = basePrice;
    this->baseCps = baseCps;
    this->id = -1;
}

Building::~Building()
{

}

double Building::GetCps(GameState* game)
{
    double cps = baseCps;

    bool isGrandma = name.compare("grandma") == 0;

    for(Upgrade* upgrade : upgrades)
    {
        if(!game->HasUpgrade(upgrade))
        {
            continue;
        }
        if(upgrade->type.compare("building_multiplier") == 0)
        {
            cps *= ((BuildingMultiplierUpgrade*)upgrade)->multiplier;
        }
        else if(upgrade->type.compare("grandma_upgrade") == 0)
        {
            if(isGrandma)
            {
                cps *= 2;
            }
            else
            {
                cps *= (1 + game->GetBuildingCount("grandma") * ((GrandmaUpgrade*)upgrade)->multiplierPerGrandma);
            }
        }
    }

    return cps * game->GetBuildingCount(id);
}

vector<Building*> Building::List;
unordered_map<string, unsigned int> Building::NameIdMap;

void Building::Initialize()
{
    List = {
        new Building("cursor", 15, 0.1),
        new Building("grandma", 100, 1),
        new Building("farm", 1100, 8),
        new Building("mine", 12000, 47),
        new Building("factory", 130000, 260),
        new Building("bank", 1.4e6, 1400),
        new Building("temple", 2e7, 7800),
        new Building("wizard_tower", 3.3e8, 44000),
        new Building("shipment", 5.1e9, 260000),
        new Building("alchemy_lab", 7.5e10, 1.6e6),
        new Building("portal", 1e12, 1e7),
        new Building("time_machine", 1.4e13, 6.5e7),
        new Building("antimatter_condenser", 1.7e14, 4.3e8),
        new Building("prism", 2.1e15, 2.9e9)
    };

    for(unsigned int i = 0; i < List.size(); i++)
    {
        Building* b = List[i];
        b->id = i;
        NameIdMap[b->name] = i;
    }
}

Building* Building::Get(unsigned int id)
{
    return (id < 0 || id >= List.size()) ? NULL : List[id];
}

Building* Building::Get(string name)
{
    return NameIdMap.count(name) == 0 ? NULL : Get(NameIdMap[name]);
}

vector<Building*> Building::GetList()
{
    return List;
}
