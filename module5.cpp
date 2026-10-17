#include "entities.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <cctype>

using namespace std;

// Convert string to lowercase
string toLower(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower((unsigned char)s[i]);
    }
    return s;
}

// Search event by name
vector<Event> searchByName(string name, vector<Event> events)
{
    vector<Event> result;
    name = toLower(name);

    for (int i = 0; i < events.size(); i++)
    {
        string eventName = toLower(events[i].getName());

        if (eventName.find(name) != string::npos)
        {
            result.push_back(events[i]);
        }
    }

    if (result.empty())
        throw runtime_error("No events found!");

    return result;
}

// Search event by category
vector<Event> searchByCategory(string category, vector<Event> events)
{
    vector<Event> result;
    category = toLower(category);

    for (int i = 0; i < events.size(); i++)
    {
        if (toLower(events[i].getCategory()) == category)
        {
            result.push_back(events[i]);
        }
    }

    if (result.empty())
        throw runtime_error("No events found in this category!");

    return result;
}

// Display search results
void displayEvents(vector<Event> events)
{
    for (int i = 0; i < events.size(); i++)
    {
        cout << "ID: " << events[i].getId() << endl;
        cout << "Name: " << events[i].getName() << endl;
        cout << "Category: " << events[i].getCategory() << endl;
        cout << "Date: " << events[i].getDate() << endl;
        cout << "--------------------\n";
    }
}

// Save results in a file
void saveResults(vector<Event> events)
{
    ofstream file("search_results.txt");

    if (!file)
    {
        cout << "Unable to open file.\n";
        return;
    }

    for (int i = 0; i < events.size(); i++)
    {
        file << events[i].getId() << " | "
             << events[i].getName() << " | "
             << events[i].getCategory() << " | "
             << events[i].getDate() << endl;
    }

    file.close();
    cout << "Results saved to search_results.txt\n";
}

int main()
{
    // Dummy event data
    vector<Event> events = {
        Event(1, "Robotics Workshop", "Tech", "20261110", 50, 42, 42),
        Event(2, "Chess Tournament", "Games", "20261115", 30, 18, 18),
        Event(3, "Coding Competition", "Tech", "20261120", 100, 75, 75),
        Event(4, "Music Night", "Cultural", "20261125", 80, 60, 60)
    };

    int choice;
    string search;

    cout << "1. Search by name\n";
    cout << "2. Search by category\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore(10000, '\n');

    try
    {
        if (choice == 1)
        {
            cout << "Enter event name or part of name: ";
            getline(cin, search);

            vector<Event> result = searchByName(search, events);
            displayEvents(result);
            saveResults(result);
        }
        else if (choice == 2)
        {
            cout << "Enter category (Tech, Games, Cultural): ";
            getline(cin, search);

            vector<Event> result = searchByCategory(search, events);
            displayEvents(result);
            saveResults(result);
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

