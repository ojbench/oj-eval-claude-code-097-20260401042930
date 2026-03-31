#include <iostream>
#include <vector>
#include <queue>

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

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int n;
    cin >> n;  // number of elements in the array

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int cnt;
    cin >> cnt;

    TreeNode* root = buildTree(arr);
    int answer = kthLargest(root, cnt);

    cout << answer << endl;

    deleteTree(root);

    return 0;
}
