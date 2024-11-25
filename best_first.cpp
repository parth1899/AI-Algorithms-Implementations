#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Node {
    string name;
    int cost;       // Cumulative cost from the start node
    int heuristic;  // Heuristic value

    Node(string name, int cost, int heuristic) 
        : name(name), cost(cost), heuristic(heuristic) {}

    // Comparator to prioritize nodes with the lowest heuristic values
    bool operator<(const Node& other) const {
        return heuristic > other.heuristic; // Min-heap based on heuristic
    }
};

void bestFirstSearch(map<string, vector<Node>>& graph, map<string, int>& heuristic, string start, string goal) {
    priority_queue<Node> pq;
    map<string, bool> visited;

    // Add the starting node to the priority queue
    pq.push(Node(start, 0, heuristic[start]));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // If the node is already visited, skip it
        if (visited[current.name]) {
            continue;
        }

        // Mark the current node as visited
        visited[current.name] = true;

        cout << "Visiting: " << current.name 
             << " (Cost: " << current.cost 
             << ", Heuristic: " << current.heuristic << ")" << endl;

        // If the goal is reached, print the total cost and exit
        if (current.name == goal) {
            cout << "Goal " << goal << " reached with total cost: " << current.cost << endl;
            return;
        }

        // Add neighbors to the priority queue
        for (const Node& neighbor : graph[current.name]) {
            if (!visited[neighbor.name]) {
                // Update the cost to include the edge cost
                pq.push(Node(neighbor.name, current.cost + neighbor.cost, heuristic[neighbor.name]));
            }
        }
    }

    cout << "Goal not reachable from the start node." << endl;
}

int main() {
    map<string, vector<Node>> graph;
    map<string, int> heuristic;

    heuristic["Arad"] = 366;
    heuristic["Zerind"] = 374;
    heuristic["Oradea"] = 380;
    heuristic["Sibiu"] = 253;
    heuristic["Fagaras"] = 178;
    heuristic["Rimnicu Vilcea"] = 193;
    heuristic["Pitesti"] = 98;
    heuristic["Bucharest"] = 0;

    graph["Arad"] = {Node("Zerind", 75, heuristic["Zerind"]), Node("Sibiu", 140, heuristic["Sibiu"])};
    graph["Zerind"] = {Node("Arad", 75, heuristic["Arad"]), Node("Oradea", 71, heuristic["Oradea"])};
    graph["Oradea"] = {Node("Zerind", 71, heuristic["Zerind"]), Node("Sibiu", 151, heuristic["Sibiu"])};
    graph["Sibiu"] = {Node("Arad", 140, heuristic["Arad"]), Node("Oradea", 151, heuristic["Oradea"]), Node("Fagaras", 99, heuristic["Fagaras"]), Node("Rimnicu Vilcea", 80, heuristic["Rimnicu Vilcea"])};
    graph["Fagaras"] = {Node("Sibiu", 99, heuristic["Sibiu"]), Node("Bucharest", 211, heuristic["Bucharest"])};
    graph["Rimnicu Vilcea"] = {Node("Sibiu", 80, heuristic["Sibiu"]), Node("Pitesti", 97, heuristic["Pitesti"])};
    graph["Pitesti"] = {Node("Rimnicu Vilcea", 97, heuristic["Rimnicu Vilcea"]), Node("Bucharest", 101, heuristic["Bucharest"])};
    graph["Bucharest"] = {};

    string start = "Arad";
    string goal = "Bucharest";

    bestFirstSearch(graph, heuristic, start, goal);

    return 0;
}
