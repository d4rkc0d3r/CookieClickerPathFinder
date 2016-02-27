#include "GrandmaUpgrade.h"

using namespace std;

GrandmaUpgrade::GrandmaUpgrade(string name, double basePrice, string building, double multiplierPerGrandma)
    : Upgrade(name, basePrice, "grandma_upgrade"), building(building), multiplierPerGrandma(multiplierPerGrandma)
{
    Building* b = Building::Get(building);
    if(b != nullptr)
    {
        b->upgrades.push_back(this);
    }
    b = Building::Get("grandma");
    if(b != nullptr)
    {
        b->upgrades.push_back(this);
    }
}

GrandmaUpgrade::~GrandmaUpgrade()
{

}

bool GrandmaUpgrade::IsUnlocked(GameState* game)
{
    return game->GetBuildingCount("grandma") >= 1 && game->GetBuildingCount(building) >= 15;
}

void GrandmaUpgrade::Initialize()
{
    List.insert(List.end(), {
        new GrandmaUpgrade("Farmer grandmas", 55000, "farm", 0.01),
        new GrandmaUpgrade("Miner grandmas", 600000, "mine", 0.01 / 2),
        new GrandmaUpgrade("Worker grandmas", 6.5e6, "factory", 0.01 / 3),
        new GrandmaUpgrade("Banker grandmas", 7e7, "bank", 0.01 / 4),
        new GrandmaUpgrade("Priestess grandmas", 1e9, "temple", 0.01 / 5),
        new GrandmaUpgrade("Witch grandmas", 1.65e10, "wizard_tower", 0.01 / 6),
        new GrandmaUpgrade("Cosmic grandmas", 2.55e11, "shipment", 0.01 / 7),
        new GrandmaUpgrade("Transmuted grandmas", 3.75e12, "alchemy_lab", 0.01 / 8),
        new GrandmaUpgrade("Altered grandmas", 5e13, "portal", 0.01 / 9),
        new GrandmaUpgrade("Grandmas grandmas", 7e14, "time_machine", 0.01 / 10),
        new GrandmaUpgrade("Antigrandmas", 8.5e15, "antimatter_condenser", 0.01 / 11),
        new GrandmaUpgrade("Rainbow grandmas", 1.05e17, "prism", 0.01 / 12),
    });
}
