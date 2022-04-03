#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>
#include <sstream>
using namespace std;

string line;
vector <int> numbers;

int main(){
  
    // ----------------------------------- INPUTS

    while (getline (cin ,line)){
        istringstream ss(line);
        string word;
        while (ss >> word) {
            if (word == "-1") continue;
            cout << word << " ";
        }
        cout << endl;
    }

    // ----------------------------------- ALGORITHM
    

}