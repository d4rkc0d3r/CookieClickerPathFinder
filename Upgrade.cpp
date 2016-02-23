#include "Upgrade.h"

using namespace std;

Upgrade::Upgrade(string name, double basePrice)
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
    // add initialize functions of upgrade classes here

    for(unsigned int i = 0; i < List.size(); i++)
    {
        Upgrade* b = List[i];
        b->id = i;
        NameIdMap[b->name] = i;
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
