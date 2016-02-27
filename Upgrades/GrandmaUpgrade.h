#ifndef GRANDMAUPGRADE_H
#define GRANDMAUPGRADE_H

#include "../Upgrade.h"

class Upgrade;
class GameState;

class GrandmaUpgrade : public Upgrade
{
    public:
        virtual ~GrandmaUpgrade();

        const std::string building;
        const double multiplierPerGrandma;

        bool IsUnlocked(GameState* game);

        static void Initialize();

    protected:
        GrandmaUpgrade(std::string name, double basePrice, std::string building, double multiplierPerGrandma);

    private:
};

#endif // GRANDMAUPGRADE_H
