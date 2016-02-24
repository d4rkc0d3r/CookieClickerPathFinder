#include "Upgrade.h"
#include "Upgrades\CookieUpgrade.h"

using namespace std;

Upgrade::Upgrade(string name, double basePrice, string type) : type(type)
{
    this->name = name;
    this->basePrice = basePrice;
}

Upgrade::~Upgrade()
{

}

vector<Upgrade*> Upgrade::List;
unordered_map<string, unsigned int> Upgrade::NameIdMap;

void Upgrade::Initialize()
{
    CookieUpgrade::Initialize();

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
