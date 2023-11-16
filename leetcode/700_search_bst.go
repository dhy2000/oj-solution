/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
 func searchBST(root *TreeNode, val int) *TreeNode {
    switch {
    case val == root.Val:
        return root
    case root.Left != nil && val < root.Val:
        return searchBST(root.Left, val)
    case root.Right != nil && val > root.Val:
        return searchBST(root.Right, val)
    default:
        return nil
    }
}