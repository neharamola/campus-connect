#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include "file.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;



string recommendationLower(string s)
{
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);

    return s;
}



string recommendationTodayDate()
{
    time_t now = time(0);
    tm *t = localtime(&now);

    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", t);

    return date;
}



vector<vector<int> > buildClubGraph()
{
    vector<vector<int> > graph(clubs.size());

    for (int i = 0; i < clubs.size(); i++)
    {
        for (int j = i + 1; j < clubs.size(); j++)
        {
            if (recommendationLower(clubs[i].getCategory()) ==
                recommendationLower(clubs[j].getCategory()))
            {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    return graph;
}



int findRecommendationClub(string cid)
{
    for (int i = 0; i < clubs.size(); i++)
    {
        if (clubs[i].getClubId() == cid)
            return i;
    }

    return -1;
}


void recommendClubs()
{
    if (clubs.size() < 2)
    {
        cout << "\nNot enough clubs for recommendations.\n";
        return;
    }

    cout << "\n========== AVAILABLE CLUBS ==========\n";

    for (int i = 0; i < clubs.size(); i++)
    {
        cout << clubs[i].getClubId() << " - "
             << clubs[i].getName() << " ("
             << clubs[i].getCategory() << ")\n";
    }

    string cid;

    cout << "\nEnter your preferred Club ID: ";
    cin >> cid;

    int start = findRecommendationClub(cid);

    if (start == -1)
    {
        cout << "Invalid Club ID.\n";
        return;
    }

    vector<vector<int> > graph = buildClubGraph();

    vector<bool> visited(clubs.size(), false);

    queue<int> q;

    visited[start] = true;
    q.push(start);

    int count = 0;

    cout << "\n========== RECOMMENDED CLUBS ==========\n";

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        for (int i = 0; i < graph[current].size(); i++)
        {
            int next = graph[current][i];

            if (!visited[next])
            {
                visited[next] = true;
                q.push(next);

                cout << "\nClub Name: "
                     << clubs[next].getName();

                cout << "\nCategory: "
                     << clubs[next].getCategory();

                cout << "\nDescription: "
                     << clubs[next].getDescription();

                cout << "\n--------------------------\n";

                count++;
            }
        }
    }

    if (count == 0)
        cout << "No similar clubs found.\n";
}



void recommendUpcomingEvents()
{
    string today = recommendationTodayDate();

    vector<Event> upcoming;

    for (int i = 0; i < events.size(); i++)
    {
        if (events[i].getDate() >= today)
            upcoming.push_back(events[i]);
    }

    if (upcoming.empty())
    {
        cout << "\nNo upcoming events available.\n";
        return;
    }

    
    for (int i = 0; i < upcoming.size(); i++)
    {
        for (int j = 0; j < upcoming.size() - i - 1; j++)
        {
            if (upcoming[j].getDate() > upcoming[j + 1].getDate())
            {
                Event temp = upcoming[j];
                upcoming[j] = upcoming[j + 1];
                upcoming[j + 1] = temp;
            }
        }
    }

    cout << "\n========== UPCOMING EVENT RECOMMENDATIONS ==========\n";

    for (int i = 0; i < upcoming.size(); i++)
    {
        cout << "\nEvent: " << upcoming[i].getName();
        cout << "\nDate: " << upcoming[i].getDate();
        cout << "\n--------------------------\n";
    }
}



void recommendationModule()
{
    int choice;

    do
    {
        cout << "\n========== RECOMMENDATION MODULE ==========\n";
        cout << "1. Get Club Recommendations\n";
        cout << "2. Get Upcoming Event Recommendations\n";
        cout << "3. Back\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                recommendClubs();
                break;

            case 2:
                recommendUpcomingEvents();
                break;

            case 3:
                cout << "Returning to Student Dashboard.\n";
                break;

            default:
                cout << "Invalid Choice.\n";
        }

    } while (choice != 3);
}

#endif
