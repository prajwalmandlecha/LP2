#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct rules
{
    string condition1;
    string condition2;
    string fact;
    string inference;
};

vector<rules> knowledgeBase = {
    {"cold", "cough", "viral infection", "cold and cough both give viral infection"},
    {"high thermometer temperature", "", "fever", "fever is a direct symptom"},
    {"viral infection", "lung problem", "COVID", "covid is strong since lung disease"}};

set<string> fact;
// addfact by doing insert
// check if fact is present by counting

int main()
{
    vector<string> symptoms = {
        "cold", "cough", "high thermometer temperature", "viral infection", "lung problem"};
    cout << "Enter y for has symptom and n for not" << endl;
    for (int i = 0; i < symptoms.size(); i++)
    {
        cout << "Has symptom :" << symptoms[i] << "? y/n" << endl;
        string line;
        getline(cin, line);
        if (line == "y")
        {
            fact.insert(symptoms[i]);
        }
    }
    vector<bool> usedRule(20, false);
    int indexrule = 0;
    bool newfactfound = true;
    while (newfactfound)
    {
        newfactfound = false;
        for (int i = 0; i < 3; i++)
        {
            if (usedRule[i])
            {
                continue;
            }
            if (fact.count(knowledgeBase[i].condition1))
            {
                if (knowledgeBase[i].condition2 == "" || fact.count(knowledgeBase[i].condition2))
                {
                    fact.insert(knowledgeBase[i].fact);
                    usedRule[i] = true;
                    cout << "derivation: " << knowledgeBase[i].inference << endl;
                    newfactfound = true;
                }
            }
        }
    }
    cout << "total facts" << endl;
    for (auto x : fact)
    {
        cout << x;
    }
    return 0;
}