/* 
235. Lowest Common Ancestor of a Binary Search Tree
Medium

Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.
Example 2:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [2,1], p = 2, q = 1
Output: 2
 

Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
p and q will exist in the BST.

END.

Interesting problem. My solution holds a couple of class data members to track the LCA. Logic is a little convoluted. Could use some cleaning up.


*/

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        node_one = p;
        node_two = q;
        look_for_nodes(root);
        return lowest_node;
    }
private:
    TreeNode* node_one{};
    TreeNode* node_two{};
    int lowest_val = INT_MAX;
    TreeNode* lowest_node{};

    int look_for_nodes(TreeNode* root) {
        if (!root || lowest_val == 0) return 0;
        int left = look_for_nodes(root->left);
        int right = look_for_nodes(root->right);
        if (left > 0) left++;
        if (right > 0) right++;

        if (right && left) {
            int minimum = std::max(right, left);
            if (minimum < lowest_val) {
                lowest_val = minimum;
                lowest_node = root;
            }
            return 0;
        } else if (right || left) {
            if (root == node_one || root == node_two) {
                lowest_val = 0;
                lowest_node = root;
                return 0;
            }
            return std::max(right, left);
        } else if (root == node_one || root == node_two) {
            return 1;
        } else {
            return 0;
        }
    }
};
