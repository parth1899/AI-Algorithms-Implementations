#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

struct Node {
    string name;
    int g; // cost from start node
    int h; // heuristic cost to goal
    Node* parent;

    Node(string name, int g, int h, Node* parent = nullptr) : name(name), g(g), h(h), parent(parent) {}

    int getF() const {
        return g + h;
    }

    bool operator>(const Node& other) const {
        return getF() > other.getF();
    }
};

using Graph = map<string, vector<Node>>;

void printPriorityQueue(priority_queue<Node, vector<Node>, greater<Node>> openList) {
    while (!openList.empty()) {
        const Node& node = openList.top();
        cout << "Node: " << node.name << ", g: " << node.g << ", h: " << node.h << ", f: " << node.getF() << endl;
        openList.pop();
    }
}

vector<string> reconstructPath(Node* node) {
    vector<string> path;
    while (node != nullptr) {
        path.push_back(node->name);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<string> aStarSearch(const Graph& graph, const map<string, int>& heuristic, const string& start, const string& goal) {
    priority_queue<Node, vector<Node>, greater<Node>> openList;
    map<string, Node*> openListMap;
    set<string> closedList;

    Node* startNode = new Node(start, 0, heuristic.at(start));
    openList.push(*startNode);
    openListMap[start] = startNode;

    cout << "Starting A* search from " << start << " to " << goal << endl;

    while (!openList.empty()) {
        cout << "\nCurrent state of open list (priority queue):" << endl;
        printPriorityQueue(openList);

        Node current = openList.top();
        openList.pop();
        openListMap.erase(current.name);

        cout << "\nExploring node: " << current.name << endl;
        cout << "Current path cost (g): " << current.g << endl;
        cout << "Estimated total cost (f): " << current.getF() << endl;

        if (current.name == goal) {
            cout << "Goal reached!" << endl;
            return reconstructPath(&current);
        }

        closedList.insert(current.name);

        for (const Node& neighbor : graph.at(current.name)) {
            if (closedList.find(neighbor.name) != closedList.end()) {
                continue;
            }

            int tentativeG = current.g + neighbor.g;
            cout << "Checking neighbor: " << neighbor.name << endl;
            cout << "Tentative path cost (g): " << tentativeG << endl;

            if (openListMap.find(neighbor.name) == openListMap.end() || tentativeG < openListMap[neighbor.name]->g) {
                if (openListMap.find(neighbor.name) != openListMap.end()) {
                    cout << "Updating node: " << neighbor.name << " in open list" << endl;
                }

                Node* neighborNode = new Node(neighbor.name, tentativeG, neighbor.h, new Node(current));
                openList.push(*neighborNode);
                openListMap[neighbor.name] = neighborNode;

                cout << "Adding/Updating neighbor: " << neighbor.name << endl;
                cout << "New path cost (g): " << neighborNode->g << endl;
                cout << "Estimated total cost (f): " << neighborNode->getF() << endl;
            }
        }
    }

    cout << "No path found." << endl;
    return {};
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

    vector<string> path = aStarSearch(graph, heuristic, "Arad", "Bucharest");

    if (!path.empty()) {
        cout << "Path found: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}



// #include <iostream>
// #include <vector>
// #include <map>
// #include <set>
// #include <queue>
// #include <algorithm>
// using namespace std;

// class Node {
// public:
//   string name;
//   int g;
//   int h;
//   Node* parent;
  
//   Node(string name, int g, int h, Node* parent = nullptr) : name(name), g(g), h(h), parent(parent) {}
  
//   int getF() const {
//     return g + h;
//   }
  
//   bool operator>(const Node& other) const{
//     return getF() > other.getF();
//   }
// };

// vector<string> reconstruct(Node* node) {
//   vector<string> path;
//   while (node != NULL) {
//     path.push_back(node->name);
//     node = node->parent;
//   }
//   reverse(path.begin(), path.end());
//   return path;
// }

// void printPQ(priority_queue<Node, vector<Node>, greater<Node>> openList) {
//   while(!openList.empty()) {
//     Node node = openList.top();
//     openList.pop();
//     cout << node.name << endl;
//   }
// }

// //graph, heuristic, start, dest
// vector<string> aStarSearch(map<string, vector<Node>> graph, map<string, int> heuristic, string start, string dest) {
//   // open list
//   // open list map
//   // 
  
//   priority_queue<Node, vector<Node>, greater<Node>> openList;
//   map<string, Node*> openListMap;
//   set<string> visited;
  
  
//   Node* startNode = new Node(start, 0, heuristic[start]);
//   openList.push(*startNode);
//   openListMap[start] = startNode;
  
//   cout << "A* search starting from ......" << endl;
  
//   while(!openList.empty()) {
//     cout << "Current state of open list: " << endl;
//     // print priority_queue
//     printPQ(openList);
    
//     Node current = openList.top();
//     openList.pop();
//     openListMap.erase(current.name);
    
//     cout << "Exploring node: " << current.name << endl;
    
//     if(current.name == dest) {
//       return reconstruct(&current);
//     }
    
//     visited.insert(current.name);
    
//     for(Node neighbour : graph[current.name]) {
//       if(visited.find(neighbour.name) != visited.end()) {
//         continue;
//       }
      
//       int tempG = current.g + neighbour.g;
//       cout << "Checking neighbour" << endl;
      
      
//       // for any look up or update operations, use the open list map
      
//       if(openListMap.find(neighbour.name) == openListMap.end() || tempG < openListMap[neighbour.name]->g) {
//         if(openListMap.find(neighbour.name) != openListMap.end()) {
//           cout << "updating the neighbour" << endl;
//         }
        
//         //adding / updating Node
//         Node* newNeighbour = new Node(neighbour.name, tempG, neighbour.h, new Node(current)); // review this constrcutor for parent
//         openList.push(*newNeighbour);
//         openListMap[neighbour.name] = newNeighbour;
        
//         cout << "Added and updated" << endl;
        
//       }
//     }
//   }
//   cout << "No path founnd" << endl;
//   return {};
// }

// int main() 
// {
//     // cout << "Hello, World!";
//     map<string, vector<Node>> graph;
//     map<string, int> heuristic;
    
//     heuristic["Arad"] = 366;
//     heuristic["Zerind"] = 374;
//     heuristic["Oradea"] = 380;
//     heuristic["Sibiu"] = 253;
//     heuristic["Fagaras"] = 178;
//     heuristic["Rimnicu Vilcea"] = 193;
//     heuristic["Pitesti"] = 98;
//     heuristic["Bucharest"] = 0;
    
//     graph["Arad"] = {Node("Zerind", 75, heuristic["Zerind"]), Node("Sibiu", 140, heuristic["Sibiu"])};
//     graph["Zerind"] = {Node("Arad", 75, heuristic["Arad"]), Node("Oradea", 71, heuristic["Oradea"])};
//     graph["Oradea"] = {Node("Zerind", 71, heuristic["Zerind"]), Node("Sibiu", 151, heuristic["Sibiu"])};
//     graph["Sibiu"] = {Node("Arad", 140, heuristic["Arad"]), Node("Oradea", 151, heuristic["Oradea"]), Node("Fagaras", 99, heuristic["Fagaras"]), Node("Rimnicu Vilcea", 80, heuristic["Rimnicu Vilcea"])};
//     graph["Fagaras"] = {Node("Sibiu", 99, heuristic["Sibiu"]), Node("Bucharest", 211, heuristic["Bucharest"])};
//     graph["Rimnicu Vilcea"] = {Node("Sibiu", 80, heuristic["Sibiu"]), Node("Pitesti", 97, heuristic["Pitesti"])};
//     graph["Pitesti"] = {Node("Rimnicu Vilcea", 97, heuristic["Rimnicu Vilcea"]), Node("Bucharest", 101, heuristic["Bucharest"])};
//     graph["Bucharest"] = {};
    
//     vector<string> result = aStarSearch(graph, heuristic, "Arad", "Bucharest");
    
//     for(string city : result) {
//       cout << city << " ->" ;
//     }
//     return 0;
// }