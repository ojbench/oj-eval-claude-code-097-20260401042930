#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

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

vector<int> parseArray(const string& line) {
    vector<int> arr;
    string cleaned = line;

    // Remove "root = " if present
    size_t rootPos = cleaned.find("root");
    if (rootPos != string::npos) {
        size_t equalPos = cleaned.find('=', rootPos);
        if (equalPos != string::npos) {
            cleaned = cleaned.substr(equalPos + 1);
        }
    }

    // Remove brackets if present
    size_t start = cleaned.find('[');
    size_t end = cleaned.find(']');
    if (start != string::npos && end != string::npos) {
        cleaned = cleaned.substr(start + 1, end - start - 1);
    }

    // Parse comma-separated values
    stringstream ss(cleaned);
    string token;

    while (getline(ss, token, ',')) {
        token.erase(0, token.find_first_not_of(" \t\n\r"));
        token.erase(token.find_last_not_of(" \t\n\r") + 1);

        if (token.empty() || token == "null") {
            arr.push_back(-1);
        } else {
            try {
                arr.push_back(stoi(token));
            } catch (...) {
                // Skip invalid tokens
            }
        }
    }

    return arr;
}

int parseCnt(const string& line) {
    string cleaned = line;

    // Check if line contains "cnt ="
    size_t cntPos = cleaned.find("cnt");
    if (cntPos != string::npos) {
        size_t equalPos = cleaned.find('=', cntPos);
        if (equalPos != string::npos) {
            cleaned = cleaned.substr(equalPos + 1);
        }
    }

    cleaned.erase(0, cleaned.find_first_not_of(" \t\n\r"));
    cleaned.erase(cleaned.find_last_not_of(" \t\n\r,") + 1);

    return stoi(cleaned);
}

int main() {
    string line;
    getline(cin, line);

    vector<int> arr;
    int cnt = 0;

    // Check if input is on one line or two
    if (line.find("cnt") != string::npos) {
        // Single line format: root = [12, 5, 18, 2, 9, 15, 20], cnt = 4
        arr = parseArray(line);
        cnt = parseCnt(line);
    } else {
        // Two line format
        arr = parseArray(line);

        string line2;
        if (getline(cin, line2)) {
            cnt = parseCnt(line2);
        }
    }

    TreeNode* root = buildTree(arr);
    int answer = kthLargest(root, cnt);

    cout << answer << endl;

    deleteTree(root);

    return 0;
}
