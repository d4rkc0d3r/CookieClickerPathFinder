#include "BuildingMultiplierUpgrade.h"

using namespace std;

BuildingMultiplierUpgrade::BuildingMultiplierUpgrade(string name, double basePrice, string building, double unlockAmount, double multiplier)
    : Upgrade(name, basePrice, "building_multiplier"), building(building), unlockAmount(unlockAmount), multiplier(multiplier)
{
    Building* b = Building::Get(building);
    if(b != nullptr)
    {
        b->upgrades.push_back(this);
    }
}

BuildingMultiplierUpgrade::~BuildingMultiplierUpgrade()
{

}

bool BuildingMultiplierUpgrade::IsUnlocked(GameState* game)
{
    return game->GetBuildingCount(building) >= unlockAmount;
}

void BuildingMultiplierUpgrade::Initialize()
{
    List.insert(List.end(), {
        new BuildingMultiplierUpgrade("Reinforced index finger", 100, "cursor", 1),
        new BuildingMultiplierUpgrade("Carpal tunnel prevention cream", 500, "cursor", 1),
        new BuildingMultiplierUpgrade("Ambidextrous", 10000, "cursor", 10)
    });
}
