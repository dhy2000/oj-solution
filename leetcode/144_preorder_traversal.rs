use std::rc::Rc;
use std::cell::RefCell;
impl Solution {
    pub fn preorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        match root {
            Some(root) => {
                let mut v = vec![root.borrow().val];
                v.append(&mut Solution::preorder_traversal(root.borrow().left.clone()));
                v.append(&mut Solution::preorder_traversal(root.borrow().right.clone()));
                v
            },
            None => vec![],
        }
    }
}

/* Solution end */

pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode { val, left: None, right: None }
    }
}

struct Solution;

fn main() {
    type TreeNodeType = Rc<RefCell<TreeNode>>;
    let tree = (1..=3)
        .map(|i| Rc::new(RefCell::new(TreeNode::new(i)))).collect::<Vec<TreeNodeType>>();
    tree[0].borrow_mut().left.replace(tree[1].clone());
    tree[1].borrow_mut().right.replace(tree[2].clone());
    println!("{:?}", Solution::preorder_traversal(Some(tree[0].clone())));
}