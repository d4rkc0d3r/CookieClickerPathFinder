#include "Upgrade.h"
#include "Upgrades\CookieUpgrade.h"
#include "Upgrades\BuildingMultiplierUpgrade.h"
#include "Upgrades\GrandmaUpgrade.h"

using namespace std;

Upgrade::Upgrade(string name, double basePrice, string type) : type(type), name(name), basePrice(basePrice)
{
    id = -1;
}

Upgrade::~Upgrade()
{

}

vector<Upgrade*> Upgrade::List;
unordered_map<string, unsigned int> Upgrade::NameIdMap;

void Upgrade::Initialize()
{
    CookieUpgrade::Initialize();
    BuildingMultiplierUpgrade::Initialize();
    GrandmaUpgrade::Initialize();

    for(unsigned int i = 0; i < List.size(); i++)
    {
        Upgrade* u = List[i];
        u->id = i;
        NameIdMap[u->name] = i;
    }
}

Upgrade* Upgrade::Get(unsigned int id)
{
    return (id < 0 || id >= List.size()) ? NULL : List[id];
}

Upgrade* Upgrade::Get(string name)
{
    return NameIdMap.count(name) == 0 ? NULL : Get(NameIdMap[name]);
}

vector<Upgrade*> Upgrade::GetList()
{
    return List;
}
