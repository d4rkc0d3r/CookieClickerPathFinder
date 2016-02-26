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
        new BuildingMultiplierUpgrade("Ambidextrous", 10000, "cursor", 10),

        new BuildingMultiplierUpgrade("Forwards from grandma", 1000, "grandma", 1),
        new BuildingMultiplierUpgrade("Steel-plated rolling pins", 5000, "grandma", 5),
        new BuildingMultiplierUpgrade("Lubricated dentures", 50000, "grandma", 25),
        new BuildingMultiplierUpgrade("Prune juice", 5e6, "grandma", 50),
        new BuildingMultiplierUpgrade("Double-thick glasses", 5e8, "grandma", 100),
        new BuildingMultiplierUpgrade("Aging agents", 5e10, "grandma", 150),
        new BuildingMultiplierUpgrade("Xtreme walkers", 5e13, "grandma", 200),
        new BuildingMultiplierUpgrade("The Unbridling", 5e16, "grandma", 250),

        new BuildingMultiplierUpgrade("Cheap hoes", 11000, "farm", 1),
        new BuildingMultiplierUpgrade("Fertilizer", 55000, "farm", 5),
        new BuildingMultiplierUpgrade("Cookie trees", 550000, "farm", 25),
        new BuildingMultiplierUpgrade("Genetically-modified cookies", 55e6, "farm", 50),
        new BuildingMultiplierUpgrade("Gingerbread scarecrows", 55e8, "farm", 100),
        new BuildingMultiplierUpgrade("Pulsar sprinklers", 55e10, "farm", 150),
        new BuildingMultiplierUpgrade("Fudge fungus", 55e13, "farm", 200),
        new BuildingMultiplierUpgrade("Wheat triffids", 55e16, "farm", 250),

        new BuildingMultiplierUpgrade("Sugar gas", 120000, "mine", 1),
        new BuildingMultiplierUpgrade("Megadrill", 600000, "mine", 5),
        new BuildingMultiplierUpgrade("Ultradrill", 6e6, "mine", 25),
        new BuildingMultiplierUpgrade("Ultimadrill", 6e8, "mine", 50),
        new BuildingMultiplierUpgrade("H-bomb mining", 6e10, "mine", 100),
        new BuildingMultiplierUpgrade("Coreforge", 6e12, "mine", 150),
        new BuildingMultiplierUpgrade("Planetsplitters", 6e15, "mine", 200),
        new BuildingMultiplierUpgrade("Canola oil wells", 6e18, "mine", 250),
    });
}
