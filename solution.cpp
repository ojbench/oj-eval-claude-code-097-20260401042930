#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

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
    vector<TreeNode*> queue;
    queue.push_back(root);

    int i = 1;
    while (i < arr.size()) {
        TreeNode* curr = queue.front();
        queue.erase(queue.begin());

        // Left child
        if (i < arr.size() && arr[i] != -1) {
            curr->left = new TreeNode(arr[i]);
            queue.push_back(curr->left);
        }
        i++;

        // Right child
        if (i < arr.size() && arr[i] != -1) {
            curr->right = new TreeNode(arr[i]);
            queue.push_back(curr->right);
        }
        i++;
    }

    return root;
}

// Reverse in-order traversal to find kth largest
int result = 0;
int count_nodes = 0;

void reverseInorder(TreeNode* node, int k) {
    if (node == nullptr || count_nodes >= k) return;

    // Visit right subtree first (larger values)
    reverseInorder(node->right, k);

    // Visit current node
    count_nodes++;
    if (count_nodes == k) {
        result = node->val;
        return;
    }

    // Visit left subtree (smaller values)
    reverseInorder(node->left, k);
}

int kthLargest(TreeNode* root, int k) {
    count_nodes = 0;
    result = 0;
    reverseInorder(root, k);
    return result;
}

// Parse input array like "root = [12, 5, 18, 2, 9, 15, 20], cnt = 4"
void parseInput(string& line, vector<int>& arr, int& cnt) {
    // Find the array part
    size_t start = line.find('[');
    size_t end = line.find(']');

    if (start != string::npos && end != string::npos) {
        string arrayStr = line.substr(start + 1, end - start - 1);
        stringstream ss(arrayStr);
        string token;

        while (getline(ss, token, ',')) {
            // Trim spaces
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
            // Remove any trailing characters
            cntStr.erase(0, cntStr.find_first_not_of(" \t\n\r"));
            cntStr.erase(cntStr.find_last_not_of(" \t\n\r") + 1);
            cnt = stoi(cntStr);
        }
    }
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

    parseInput(line, arr, cnt);

    TreeNode* root = buildTree(arr);
    int answer = kthLargest(root, cnt);

    cout << answer << endl;

    deleteTree(root);

    return 0;
}
