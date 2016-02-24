#include <iostream>
#include <unordered_set>

#include "GameState.h"
#include "Building.h"
#include "Upgrade.h"

#include "conio.h"

using namespace std;

int main()
{
    Building::Initialize();
    Upgrade::Initialize();

    GameState::FPS = 1;
    GameState::CLICKS_PER_SECOND = 4;
    GameState::WAIT_TIME_PER_PURCHASE = 1;
    GameState::BUY_UPGRADES = true;

    unordered_set<char> output = {'+'/*, '~', '-'*/};

    double targetCookies = 1e6;

    bool buyAlsoStuffThatIsCheapEnoughtToBuy = true;

    GameState g;
    list<GameState> gameStates;

    if(GameState::CLICKS_PER_SECOND == 0)
    {
        g.EarnCookies(15);
        g.AdvanceSeconds(5);
        g.BuyBuilding("cursor");
    }

    gameStates.push_back(g);

    double lastCookiesPlusQuarterHourProduction = 0;
    while(gameStates.size() > 0)
    {
        g = gameStates.front();
        list<GameState>::iterator toRemove = gameStates.begin();
        for(list<GameState>::iterator i = gameStates.begin(); i != gameStates.end(); i++)
        {
            if((*i).time < g.time)
            {
                g = (*i);
                toRemove = i;
            }
        }
        gameStates.erase(toRemove);
        double gCps = g.CalculateCps();

        for(list<GameState>::iterator i = gameStates.begin(); i != gameStates.end();)
        {
            if((*i).time == g.time)
            {
                double testCps = (*i).CalculateCps();
                if(testCps > gCps || (testCps == gCps && (*i).AllTimeCookies() > g.AllTimeCookies()))
                {
                    if(output.count('-'))
                    {
                        cout << "-" << g.ToString() << endl;
                    }
                    gCps = testCps;
                    g = (*i);
                }
                else
                {
                    if(output.count('-'))
                    {
                        cout << "-" << (*i).ToString() << endl;
                    }
                }
                gameStates.erase(i++);
            }
            else
            {
                i++;
            }
        }

        double testFor = gCps * 60 * 15 + g.AllTimeCookies();
        if(lastCookiesPlusQuarterHourProduction * 0.8 > testFor)
        {
            if(output.count('~'))
            {
                cout << "~" << g.ToString() << endl;
            }
        }
        else
        {
            if(output.count('+'))
            {
                cout << "+" << g.ToString() << endl;
            }
            for(GameState gs : g.CalculateNextGameStates(buyAlsoStuffThatIsCheapEnoughtToBuy))
            {
                gameStates.push_back(gs);
            }
        }
        if(testFor > lastCookiesPlusQuarterHourProduction)
            lastCookiesPlusQuarterHourProduction = testFor;
        if(g.AllTimeCookies() >= targetCookies)
        {
            for(string s : g.history)
            {
                cout << s << endl;
            }
            break;
        }
    }
}
