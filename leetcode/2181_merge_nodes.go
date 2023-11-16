/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
 func mergeNodes(head *ListNode) *ListNode {
	// first skip zeros
	for head != nil && head.Val == 0 {
		head = head.Next
	}
	cur := head
	for cur != nil {
		front := cur.Next
		for front != nil && front.Val != 0 {
			cur.Val += front.Val
			front = front.Next
		}
		// skip zeros
		for front != nil && front.Val == 0 {
			front = front.Next
		}
		cur.Next = front
		cur = front
	}
	return head
}