#ifndef BUILDINGMULTIPLIERUPGRADE_H
#define BUILDINGMULTIPLIERUPGRADE_H

#include "../Upgrade.h"

class Upgrade;
class GameState;

class BuildingMultiplierUpgrade : public Upgrade
{
    public:
        virtual ~BuildingMultiplierUpgrade();

        const std::string building;
        const double unlockAmount;
        const double multiplier;

        bool IsUnlocked(GameState* game);

        static void Initialize();

    protected:
        BuildingMultiplierUpgrade(std::string name, double basePrice, std::string building, double unlockAmount, double multiplier = 2);

    private:
};

#endif // BUILDINGMULTIPLIERUPGRADE_H
