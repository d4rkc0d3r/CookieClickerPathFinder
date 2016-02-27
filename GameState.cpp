#include "GameState.h"
#include <sstream>
#include <cmath>
#include <iostream>

#include "Upgrades\CookieUpgrade.h"

using namespace std;

int GameState::FPS = 1;
int GameState::CLICKS_PER_SECOND = 1;
double GameState::WAIT_TIME_PER_PURCHASE = 0;
bool GameState::BUY_UPGRADES = true;

string formatTime(int t)
{
    stringstream ss;

    t /= GameState::FPS;

    int seconds = t % 60;
    int minutes = (t /= 60) % 60;
    int hours = (t /= 60) % 60;
    int days = (t /= 24);

    if(days > 0)
        ss << days << "d";
    if(hours > 0)
        ss << hours << "h";
    if(minutes > 0)
        ss << minutes << "m";
    ss << seconds << "s";

    return ss.str();
}

GameState::GameState()
{
    int buildingCount = Building::GetList().size();
    for(int i = 0; i < buildingCount; i++)
    {
        buildings.push_back(0);
    }
    cookies = 0;
    allTimeCookies = 0;
    time = 0;
}

GameState::GameState(GameState* g)
{
    buildings = g->buildings;
    boughtUpgrades = g->boughtUpgrades;
    cookies = g->cookies;
    allTimeCookies = g->allTimeCookies;
    time = g->time;
    history = g->history;
}

GameState::~GameState()
{

}

list<GameState> GameState::CalculateNextGameStates(bool buyAffordableStuff)
{
    list<GameState> result;

    double cps = CalculateCps();

    for(Building* b : Building::GetList())
    {
        double price = GetBuildingPrice(b);
        if((price <= cookies && (!buyAffordableStuff)) || (cps <= 0 && price > cookies))
            continue;
        GameState g(this);
        if(price > cookies)
        {
            double t = (price - cookies) / cps;
            if(t > FPS * 60 * 60 * 24)
                continue;
            g.AdvanceSeconds(t);
        }
        g.BuyBuilding(b);
        result.push_back(g);
    }

    if(BUY_UPGRADES)
    {
        for(Upgrade* upgrade : Upgrade::GetList())
        {
            double price = upgrade->basePrice;
            if((price <= cookies && (!buyAffordableStuff))
               || (cps <= 0 && price > cookies)
               || !upgrade->IsUnlocked(this)
               || boughtUpgrades.count(upgrade) > 0)
                continue;
            GameState g(this);
            if(price > cookies)
            {
                double t = (price - cookies) / cps;
                if(t > FPS * 60 * 60 * 24)
                    continue;
                g.AdvanceSeconds(t);
            }
            g.BuyUpgrade(upgrade);
            result.push_back(g);
        }
    }

    return result;
}

double GameState::GetBank()
{
    return cookies;
}

void GameState::EarnCookies(double cookies)
{
    this->cookies += cookies;
    this->allTimeCookies += cookies;
}

void GameState::AdvanceSeconds(double seconds, bool click)
{
    long long frames = (long long)ceil(seconds * FPS);
    time += frames;
    EarnCookies(CalculateCps(click) * frames / FPS);
}

double GameState::GetBuildingPrice(Building* building)
{
    return ceil(building->basePrice * pow(1.15, buildings[building->id]));
}

void GameState::BuyBuilding(string building)
{
    BuyBuilding(Building::Get(building));
}

void GameState::BuyBuilding(int id)
{
    BuyBuilding(Building::Get(id));
}

void GameState::AddHistoryEntry(string entry)
{
    history.push_back(formatTime(time) + " " + entry);
}

void GameState::BuyBuilding(Building* building)
{
    if(building == NULL)
        return;
    double price = GetBuildingPrice(building);
    if(price > cookies)
        return;
    AdvanceSeconds(WAIT_TIME_PER_PURCHASE, false);
    double cps1 = CalculateCps();
    buildings[building->id]++;
    cookies -= price;
    double cps2 = CalculateCps();
    AddHistoryEntry("buy " + building->name + " number "
                    + to_string(buildings[building->id]) + " for "
                    + to_string((long long)price) + " cookies"
                    + " (+" + to_string((cps2 / cps1 - 1) * 100) + "% cps)");
}

void GameState::BuyUpgrade(Upgrade* upgrade)
{
    if(upgrade == NULL
        || HasUpgrade(upgrade)
        || upgrade->basePrice > cookies
        || !upgrade->IsUnlocked(this))
        return;
    AdvanceSeconds(WAIT_TIME_PER_PURCHASE, false);
    double cps1 = CalculateCps();
    boughtUpgrades.insert(upgrade);
    cookies -= upgrade->basePrice;
    double cps2 = CalculateCps();
    AddHistoryEntry("buy UPGRADE " + upgrade->name
                    + " for " + to_string((long long)upgrade->basePrice) + " cookies"
                    + " (+" + to_string((cps2 / cps1 - 1) * 100) + "% cps)");
}

bool GameState::HasUpgrade(Upgrade* upgrade)
{
    return boughtUpgrades.count(upgrade) > 0;
}

string GameState::ToString()
{
    stringstream ss;

    ss << "{";
    ss << formatTime(time);
    ss << ",cps:" << CalculateCps();
    ss << ",bank:" << cookies;
    ss << ",all:" << allTimeCookies;
    ss << ",buildings:{";
    for(unsigned int i = 0; i < buildings.size(); i++)
    {
        if(i != 0)
            ss << ",";
        ss << buildings[i];
    }
    ss << "}";
    ss << "}";

    return ss.str();
}

double GameState::AllTimeCookies()
{
    return allTimeCookies;
}

double GameState::CalculateCps(bool includeClicks)
{
    double cps = 0;

    for(auto b : Building::GetList())
    {
        cps += b->GetCps(this);
    }

    for(Upgrade* upgrade : boughtUpgrades)
    {
        if(upgrade->type.compare("cookie") == 0)
        {
             cps *= ((CookieUpgrade*)upgrade)->multiplier;
        }
    }

    if(includeClicks)
    {
        double clickCps = CLICKS_PER_SECOND;

        clickCps *= (HasUpgrade(Upgrade::Get("Reinforced index finger"))) ? 2 : 1;
        clickCps *= (HasUpgrade(Upgrade::Get("Carpal tunnel prevention cream"))) ? 2 : 1;
        clickCps *= (HasUpgrade(Upgrade::Get("Ambidextrous"))) ? 2 : 1;

        cps += clickCps;
    }

    return cps;
}

int GameState::GetBuildingCount(Building* building)
{
    return buildings[building->id];
}

int GameState::GetBuildingCount(std::string building)
{
    Building* b = Building::Get(building);
    if(b == NULL)
        return -1;
    return buildings[b->id];
}

int GameState::GetBuildingCount(int id)
{
    Building* b = Building::Get(id);
    if(b == NULL)
        return -1;
    return buildings[b->id];
}
