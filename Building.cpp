#include "Building.h"

Building::Building(std::string name, double basePrice, double baseCps)
{
    this->name = name;
    this->basePrice = basePrice;
    this->baseCps = baseCps;
    this->id = -1;
}

Building::~Building()
{
    //dtor
}

double Building::GetCps(GameState* game)
{
    return baseCps * game->GetBuildingCount(id);
}

std::vector<Building*> Building::BuildingList;
std::unordered_map<std::string, unsigned int> Building::BuildingNameIdMap;

void Building::InitializeBuildings()
{
    BuildingList = {
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

    for(unsigned int i = 0; i < BuildingList.size(); i++)
    {
        Building* b = BuildingList[i];
        b->id = i;
        BuildingNameIdMap[b->name] = i;
    }
}

Building* Building::Get(unsigned int id)
{
    return (id < 0 || id >= BuildingList.size()) ? NULL : BuildingList[id];
}

Building* Building::Get(std::string name)
{
    return BuildingNameIdMap.count(name) == 0 ? NULL : Get(BuildingNameIdMap[name]);
}

std::vector<Building*> Building::GetList()
{
    return BuildingList;
}
