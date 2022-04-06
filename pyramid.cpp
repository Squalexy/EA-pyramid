#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>
#include <sstream>
using namespace std;

string line, word;
vector<int> numbers, node_values;
vector<vector<int>> nodes;
vector<pair<int, int>> table_used;
vector<pair<int, int>> table_unused;
vector<bool> calculated_nodes;

pair<int, int> pyramid(int node)
{
    // IF NODE IS A LEAF
    if (nodes[node].empty()) return make_pair(0,0);

    for (int son: nodes[node]){

        if (calculated_nodes[son] == false){
            pyramid(son);
            calculated_nodes[son] = true;
        }

        table_unused[node].first += table_used[son].first;
        table_unused[node].second += table_used[son].second;
        
        if (table_used[son].first < table_unused[son].first) {
            table_used[node].first += table_used[son].first;
            table_used[node].second += table_used[son].second;
        }

        else if (table_used[son].first > table_unused[son].first) {
            table_used[node].first += table_unused[son].first;
            table_used[node].second += table_unused[son].second;
        }

        else {
            if (table_used[son].second > table_unused[son].second) {
                table_used[node].first += table_used[son].first;
                table_used[node].second += table_used[son].second;
            }
            else {
                table_used[node].first += table_unused[son].first;
                table_used[node].second += table_unused[son].second;
            }
        }
    }

    if (table_used[0].first > table_unused[node].first) return make_pair(table_unused[0].first, table_unused[0].second);
    else if (table_used[0].first == table_unused[node].first) {
        if (table_used[0].second < table_unused[0].second) return make_pair(table_unused[0].first, table_unused[0].second);
        else return make_pair(table_used[0].first, table_used[0].second);
    }
    else return make_pair(table_used[0].first, table_used[0].second);
}

int main()
{

    node_values = vector<int>(100001, -1);
    nodes = vector<vector<int>>(100001);
    table_used = vector<pair<int, int>>(100001, make_pair(0,0));
    table_unused = vector<pair<int, int>>(100001, make_pair(0,0));
    calculated_nodes = vector<bool>(100001, false);

    while (getline(cin, line))
    {
        numbers = vector<int>();
        stringstream ss(line);
        bool skip = false;
        while (ss >> word)
        { // READ INPUT

            if (word == "-1")
            {
                // ----------------------------------- ALGORITHM
                pair <int, int> solution = pyramid(0);
                cout << solution.first << " " << solution.second << endl;
                // ----------------------------------- ALGORITHM
                skip = true;
                break;
            }
            numbers.push_back(atoi(word.c_str())); // ADD NUMBERS TO TEMP VARIABLE
        }
        if (skip == true)
            continue;

        node_values[numbers[0]] = numbers[numbers.size() - 1]; // ADD NODE VALUES
        table_used[numbers[0]] = make_pair(1, numbers[numbers.size() - 1]);
        table_unused[numbers[0]] = make_pair(0,0);
        calculated_nodes[numbers[0]] = false;
        nodes[numbers[0]] = vector<int>();

        if (numbers.size() != 2)
        {
            for (int i = 1; i < (int) numbers.size() - 1; i++)
                nodes[numbers[0]].push_back(numbers[i]); // ADD NODE CHILDREN
        }
    }
}