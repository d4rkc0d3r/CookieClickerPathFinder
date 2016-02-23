#include <iostream>

#include "GameState.h"
#include "Building.h"

#include "conio.h"

using namespace std;

int main()
{
    Building::InitializeBuildings();

    GameState g;
    list<GameState> gameStates;

    GameState::FPS = 1;
    GameState::CLICKS_PER_SECOND = 30;
    GameState::WAIT_TIME_PER_PURCHASE = 0;

    g.EarnCookies(15);
    g.AdvanceSeconds(5);
    g.BuyBuilding("cursor");

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
                    //cout << "-" << g.ToString() << endl;
                    gCps = testCps;
                    g = (*i);
                }
                else
                {
                    //cout << "-" << (*i).ToString() << endl;
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
            cout << "~";
        }
        else
        {
            cout << "+";
            for(GameState gs : g.CalculateNextGameStates(true))
            {
                gameStates.push_back(gs);
            }
        }
        if(testFor > lastCookiesPlusQuarterHourProduction)
            lastCookiesPlusQuarterHourProduction = testFor;
        cout << g.ToString() << endl;
        if(g.AllTimeCookies() >= 1e9)
        {
            for(string s : g.history)
            {
                cout << s << endl;
            }
            break;
        }
    }
}
