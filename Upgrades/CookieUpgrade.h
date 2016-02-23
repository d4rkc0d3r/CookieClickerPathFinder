#ifndef COOKIEUPGRADE_H
#define COOKIEUPGRADE_H

#include "../Upgrade.h"


class CookieUpgrade : public Upgrade
{
    public:
        virtual ~CookieUpgrade();

        double unlockPrice;
        double multiplier;

        bool IsUnlocked(GameState game);

        static void Initialize();

    protected:
        CookieUpgrade(std::string name, double basePrice, double unlockPrice, double multiplier);

    private:
};

#endif // COOKIEUPGRADE_H
