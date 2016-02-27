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

        new BuildingMultiplierUpgrade("Sturdier conveyor belts", 1.3e6, "factory", 1),
        new BuildingMultiplierUpgrade("Child labor", 6.5e6, "factory", 5),
        new BuildingMultiplierUpgrade("Sweatshop", 6.5e7, "factory", 25),
        new BuildingMultiplierUpgrade("Radium reactors", 6.5e9, "factory", 50),
        new BuildingMultiplierUpgrade("Recombobulators", 6.5e11, "factory", 100),
        new BuildingMultiplierUpgrade("Deep-bake process", 6.5e13, "factory", 150),
        new BuildingMultiplierUpgrade("Cyborg workforce", 6.5e16, "factory", 200),
        new BuildingMultiplierUpgrade("78-hour days", 6.5e19, "factory", 250),

        new BuildingMultiplierUpgrade("Taller tellers", 1.4e7, "bank", 1),
        new BuildingMultiplierUpgrade("Scissor-resistant credit cards", 7e7, "bank", 5),
        new BuildingMultiplierUpgrade("Acid-proof vaults", 7e8, "bank", 25),
        new BuildingMultiplierUpgrade("Chocolate coins", 7e10, "bank", 50),
        new BuildingMultiplierUpgrade("Exponential interest rates", 7e12, "bank", 100),
        new BuildingMultiplierUpgrade("Financial zen", 7e14, "bank", 150),
        new BuildingMultiplierUpgrade("Way of the wallet", 7e17, "bank", 200),
        new BuildingMultiplierUpgrade("The stuff rationale", 7e20, "bank", 250),
    });
}
