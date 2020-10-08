//Naive, only compare with its left and right children
//WA: 70 / 75 test cases passed.
//[10,5,15,null,null,6,20]
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        if(root->left && root->left->val >= root->val) return false;
        if(root->right && root->right->val <= root->val) return false;
        
        return isValidBST(root->left) && isValidBST(root->right);
    }
};

//Recursion
//Runtime: 8 ms, faster than 99.49% of C++ online submissions for Validate Binary Search Tree.
//Memory Usage: 22.2 MB, less than 5.05% of C++ online submissions for Validate Binary Search Tree.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root, int& minv, int& maxv) {
        if(!root) return true;
        if(!root->left && !root->right){
            minv = maxv = root->val;
            return true;
        }else if(root->left && root->right){
            int minl = INT_MAX, maxl = INT_MIN;
            //if subtree is invalid, return immediately!!
            if(!isValidBST(root->left, minl, maxl)) return false;
            if(maxl >= root->val) return false;
            
            int minr = INT_MAX, maxr = INT_MIN;
            if(!isValidBST(root->right, minr, maxr)) return false;
            if(minr <= root->val) return false;
            
            minv = minl;
            maxv = maxr;
            
            return true;
        }else if(!root->right){
            //left subtree is not empty
            int minl = INT_MAX, maxl = INT_MIN;
            if(!isValidBST(root->left, minl, maxl)) return false;
            if(maxl >= root->val) return false;
            maxv = root->val;
            minv = minl;
            return true;
        }else/* if(!root->left)*/{
            //right subtree is not empty
            int minr = INT_MAX, maxr = INT_MIN;
            if(!isValidBST(root->right, minr, maxr)) return false;
            if(minr <= root->val) return false;
            minv = root->val;
            maxv = maxr;
            return true;
        }
    }
    
    bool isValidBST(TreeNode* root) {
        int rootmin = INT_MAX, rootmax = INT_MIN;
        return isValidBST(root, rootmin, rootmax);
    }
};

//Approach 1: Recursion(cleaner)
//Runtime: 16 ms, faster than 82.11% of C++ online submissions for Validate Binary Search Tree.
//Memory Usage: 22 MB, less than 15.55% of C++ online submissions for Validate Binary Search Tree.
//time: O(N), space: O(N)
class Solution {
public:
    bool recurse(TreeNode* node, long long lower, long long upper){
        if(!node) return true;
        
        if(node->val <= lower) return false;
        if(node->val >= upper) return false;
        
        if(!recurse(node->left, lower, node->val)) return false;
        if(!recurse(node->right, node->val, upper)) return false;
        
        return true;
    }
    
    bool isValidBST(TreeNode* root) {
        // cout << LLONG_MIN << endl;
        // cout << LLONG_MAX << endl;
        return recurse(root, LLONG_MIN, LLONG_MAX);
    }
};