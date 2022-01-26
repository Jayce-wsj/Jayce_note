#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr){}
    TreeNode(int val) : val(val), left(nullptr), right(nullptr){}
};

class Tree{
public:
    TreeNode* create(vector<string> &tree, int index){
        TreeNode *newNode = NULL;

        if (tree[index] == "#" || index >= tree.size()) {
            return nullptr;
        } else {
            int value = stoi(tree[index]);
            size++;
            newNode = new TreeNode(value);
            newNode->left = create(tree, index*2+1);
            newNode->right = create(tree, index*2+2);
            return newNode;
        }
    }
private:
    int size = 0;
};

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    TreeNode* cur = root;

    while(cur != nullptr || !st.empty()) {
        if(cur != NULL) {
            st.push(cur);
            cur = cur->left;
        } else {
            cur = st.top();
            st.pop();
            res.push_back(cur->val);
            cur = cur->right;
        }
    }
    return res;
}

int main() {
    Tree tree;
    vector<string> nums = {"1","2","3","4","#","6","7"};
    TreeNode* root = tree.create(nums, 0);
    vector<int>out = inorderTraversal(root);
    for (auto i : out) {
        cout<<i<<" ";
    }

}