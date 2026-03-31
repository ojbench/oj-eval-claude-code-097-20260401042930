#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build tree from level-order array
TreeNode* buildTree(const vector<int>& arr) {
    if (arr.empty() || arr[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;
    q.push(root);

    size_t i = 1;
    while (!q.empty() && i < arr.size()) {
        TreeNode* curr = q.front();
        q.pop();

        // Left child
        if (i < arr.size()) {
            if (arr[i] != -1) {
                curr->left = new TreeNode(arr[i]);
                q.push(curr->left);
            }
            i++;
        }

        // Right child
        if (i < arr.size()) {
            if (arr[i] != -1) {
                curr->right = new TreeNode(arr[i]);
                q.push(curr->right);
            }
            i++;
        }
    }

    return root;
}

// Reverse in-order traversal to find kth largest
int result = 0;
int count_nodes = 0;

void reverseInorder(TreeNode* node, int k) {
    if (node == nullptr || count_nodes >= k) return;

    reverseInorder(node->right, k);

    count_nodes++;
    if (count_nodes == k) {
        result = node->val;
        return;
    }

    reverseInorder(node->left, k);
}

int kthLargest(TreeNode* root, int k) {
    count_nodes = 0;
    result = 0;
    reverseInorder(root, k);
    return result;
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string line;
    getline(cin, line);

    vector<int> arr;
    int cnt = 0;

    // Parse: root = [12, 5, 18, 2, 9, 15, 20], cnt = 4
    size_t arrayStart = line.find('[');
    size_t arrayEnd = line.find(']');

    if (arrayStart != string::npos && arrayEnd != string::npos) {
        string arrayStr = line.substr(arrayStart + 1, arrayEnd - arrayStart - 1);
        stringstream ss(arrayStr);
        string token;

        while (getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t\n\r"));
            token.erase(token.find_last_not_of(" \t\n\r") + 1);

            if (!token.empty() && token != "null") {
                arr.push_back(stoi(token));
            } else {
                arr.push_back(-1);
            }
        }
    }

    // Find cnt value
    size_t cntPos = line.find("cnt");
    if (cntPos != string::npos) {
        size_t equalPos = line.find('=', cntPos);
        if (equalPos != string::npos) {
            string cntStr = line.substr(equalPos + 1);
            cntStr.erase(0, cntStr.find_first_not_of(" \t\n\r"));
            cntStr.erase(cntStr.find_last_not_of(" \t\n\r") + 1);
            cnt = stoi(cntStr);
        }
    }

    TreeNode* root = buildTree(arr);
    int answer = kthLargest(root, cnt);

    cout << answer << endl;

    deleteTree(root);

    return 0;
}
