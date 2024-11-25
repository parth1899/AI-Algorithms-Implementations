// Graph Problems: Uninformed
// BFS, DFS, IDDFS

#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>

using namespace std;

void bfs(unordered_map<string, vector<string>>& cities, const string& start) {
    unordered_set<string> visited;
    queue<string> q; // queue for cities
    q.push(start);

    while(!q.empty()) {
        string curr = q.front();
        q.pop();

        if(visited.find(curr) != visited.end()) {
            continue;
        }

        visited.insert(curr);
        cout << "visited: " << curr << endl;

        for(string& city : cities[curr]) {
            q.push(city);
        } 
    }
}

void dfs(unordered_map<string, vector<string>>& cities, const string& start) {
    unordered_set<string> visited;
    stack<string> s;
    s.push(start);

    while(!s.empty()) {
        string curr = s.top();
        s.pop();

        if(visited.find(curr) == visited.end()) {
            visited.insert(curr);
            cout << "Visited: " << curr << endl;

            for(const string& neighbour : cities[curr]) {
                if(visited.find(neighbour) == visited.end()) {
                    s.push(neighbour);
                }
            }
        }
    }
}

bool depthLimitedDFS(unordered_map<string, vector<string>>& cities, const string curr, const string& dest, const int& max_depth, unordered_set<string>& visited) {

    visited.insert(curr);
    cout << "visited: " << curr << endl;

    if(curr == dest) return true;

    if(max_depth == 0) return false;

    for(const string& neighbour : cities[curr]) {
        if(visited.find(neighbour) == visited.end()) {
            if(depthLimitedDFS(cities, neighbour, dest, max_depth - 1, visited)) {
                return true;
            }
        }
    }
    return false;
}

bool iddfs(unordered_map<string, vector<string>>& cities, const string& start, const string& dest, int max_depth) {
    for(int depth = 0; depth <= max_depth; depth++) {
        unordered_set<string> visited;
        if(depthLimitedDFS(cities, start, dest, depth, visited)) {
            cout << "Found " << dest << " at depth " << depth << endl;
            return true;
        } 
        cout << endl;
    }
    return false;
}

int main() {

    unordered_map<string, vector<string>> cities;

    cities["mumbai"].push_back("delhi");
    cities["mumbai"].push_back("bangalore");

    cities["delhi"].push_back("mumbai");
    cities["delhi"].push_back("kolkata");
    
    cities["bangalore"].push_back("chennai");
    cities["bangalore"].push_back("mumbai");

    cities["chennai"].push_back("bangalore");
    cities["chennai"].push_back("kolkata");

    cities["kolkata"].push_back("chennai");
    cities["kolkata"].push_back("delhi");


    // bfs(cities, "mumbai");
    // dfs(cities, "mumbai");
    iddfs(cities, "mumbai", "kolkata", 2);
    return 0;
}