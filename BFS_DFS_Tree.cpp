#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node(int val) {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }

};

// void BFS(Node* root) {
//     queue<Node*> q;
//     q.push(root);

//     while(!q.empty()) {
//         Node* curr = q.front();
//         q.pop();

//         if(curr->left) {
//             q.push(curr->left);
//         }
//         if(curr->right) {
//             q.push(curr->right);
//         }

//         cout << curr->val << " ";
//     }
// }

vector<vector<int>> BFS(Node* root) {
    vector<vector<int>> result;

    if(root == NULL) {
        return result;
    }

    queue<Node*> q;

    q.push(root);

    while(!q.empty()) {
        int size = q.size();
        vector<int> level;

        for(int i = 0; i < size; i++) {
            Node* temp = q.front();
            q.pop();
            if(temp->left != nullptr) {
                q.push(temp->left);
            }
            if(temp->right != nullptr) {
                q.push(temp->right);
            }
            level.push_back(temp->val);
        }

        result.push_back(level);
    }
    return result;
}

void DFS (Node* root) {
    //preorder logic
    if(root == nullptr) return;
    cout << root->val << " ";
    DFS(root->left);
    DFS(root->right);
}


void DFS(Node* root) {
    //same preorder logic, but iterative instead of recursion
    if(root == NULL) {
        return;
    }

    stack<Node*> s;
    s.push(root);

    while(!s.empty()) {
        Node* temp = s.top();
        s.pop();

        if(temp->right != NULL) s.push(temp->right);
        if(temp->left != NULL) s.push(temp->left);

        cout << temp->val << " ";
    }

}


int main() {

    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);

    root->left->left = new Node(40);
    root->left->right = new Node(50);

    root->right->left = new Node(60);
    root->right->right = new Node(70);

    vector<vector<int>>result = BFS(root);
    cout << "BFS Traversal: " << endl;
    for(auto& it : result) {
        for(int& i : it) {
            cout << i << " ";
        }

        cout << endl;
    }

    cout << "DFS Traversal: " << endl;

    DFS(root);

    return 0;
}