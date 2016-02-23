#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <unordered_set>
#include "Building.h"
#include <list>
#include <string>

class Building;

class GameState
{
    public:
        GameState();
        GameState(GameState* g);
        virtual ~GameState();

        static int FPS;
        static int CLICKS_PER_SECOND;
        static double WAIT_TIME_PER_PURCHASE;

        long long time; // time since start in frames

        std::list<std::string> history;

        int GetBuildingCount(std::string building);
        int GetBuildingCount(int id);
        int GetBuildingCount(Building* building);

        double GetBuildingPrice(Building* building);

        std::list<GameState> CalculateNextGameStates(bool buyAffordableStuff = false);

        double CalculateCps();
        double GetBank();
        double AllTimeCookies();
        void EarnCookies(double cookies);

        void AdvanceSeconds(double seconds);

        void BuyBuilding(std::string building);
        void BuyBuilding(Building* building);
        void BuyBuilding(int id);

        std::string ToString();
    protected:

    private:
        double cookies;
        double allTimeCookies;

        std::vector<int> buildings;
        std::unordered_set<std::string> boughtUpgrades;
};

#endif // GAMESTATE_H
