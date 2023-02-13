#pragma once
#pragma once
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

vector<string> split(const string& s, const char& sep)
{
    vector<string> v;
    string curr = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == sep)
        {
            v.push_back(curr);
            curr = "";
        }
        else
        {
            curr += s[i];
        }
    }
    v.push_back(curr);
    return v;
}

void prinMenu()
{
    printf("Choose an option:\n[1]  Display the number of nodes\n[2]  Display the number of edges\n[3]  Display the number of source nodes\n[4]  Display the number of sink nodes\n[5]  Display the number of isolated nodes\n[6]  Display the number of bridge edges\n[7]  Display the number of articulation nodes \n[8]  Display the shortest path length distribution\n[9]  Display the diameter of the graph \n[10] Display the in-degree distribution in the form of a table\n[11] Display the out-degree distribution in the form of a table\n[12] Display the size of the largest strongly connected component (SCC)\n[13] Display the size distribution of all SCCs\n[14] Display the size of the largest weakly connected component (WCC)\n[15] Display the size distribution of all WCCs \n\n\n[16] to quit the program....\n\n");
}