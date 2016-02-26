#ifndef UPGRADE_H
#define UPGRADE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "GameState.h"

class GameState;

class Upgrade
{
    public:
        virtual ~Upgrade();

        const std::string type;
        const std::string name;
        const double basePrice;

        unsigned int id;

        virtual bool IsUnlocked(GameState* game) = 0;

        static void Initialize();

        static Upgrade* Get(std::string name);
        static Upgrade* Get(unsigned int id);
        static std::vector<Upgrade*> GetList();

    protected:
        Upgrade(std::string name, double basePrice, std::string type);

        static std::vector<Upgrade*> List;
        static std::unordered_map<std::string, unsigned int> NameIdMap;

    private:
};

#endif // UPGRADE_H
