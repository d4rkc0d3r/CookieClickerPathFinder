#include "CookieUpgrade.h"

using namespace std;

CookieUpgrade::CookieUpgrade(string name, double basePrice, double unlockPrice, double multiplier)
    : Upgrade(name, basePrice, "cookie"), unlockPrice(unlockPrice), multiplier(multiplier)
{

}

CookieUpgrade::~CookieUpgrade()
{

}

bool CookieUpgrade::IsUnlocked(GameState* game)
{
    return game->AllTimeCookies() >= unlockPrice;
}

void CookieUpgrade::Initialize()
{
    List.insert(List.end(), {
        new CookieUpgrade("Plain cookies", 999999, 50000, 1.01),
        new CookieUpgrade("Sugar cookies", 5e6, 250000, 1.01),
        new CookieUpgrade("Oatmeal raisin cookies", 1e7, 500000, 1.01),
        new CookieUpgrade("Peanut butter cookies", 5e7, 2.5e6, 1.01),
        new CookieUpgrade("Coconut cookies", 1e8, 5e6, 1.01),
        new CookieUpgrade("White chocolate cookies", 5e8, 2.5e7, 1.02),
        new CookieUpgrade("Macadamia nut cookies", 1e9, 5e7, 1.02),
        new CookieUpgrade("Double-chip cookies", 5e9, 2.5e8, 1.02),
        new CookieUpgrade("White chocolate macadamia nut cookies", 1e10, 5e8, 1.02),
        new CookieUpgrade("All-chocolate cookies", 5e10, 2.5e9, 1.02)
    });
}
