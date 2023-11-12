use std::rc::Rc;
use std::cell::RefCell;
impl Solution {
    pub fn is_same_tree(p: Option<Rc<RefCell<TreeNode>>>, q: Option<Rc<RefCell<TreeNode>>>) -> bool {
        match (p, q) {
            (None, None) => true,
            (Some(p), Some(q)) => {
                let (mut p, mut q) = (p.borrow_mut(), q.borrow_mut());
                p.val == q.val &&
                Solution::is_same_tree(p.left.take(), q.left.take()) &&
                Solution::is_same_tree(p.right.take(), q.right.take())
            }
            _ => false
        }
    }
}

/* end of solution */

struct Solution;

#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>
}

impl TreeNode {
    pub fn new(val: i32) -> Self {
        TreeNode { val, left: None, right: None }
    }
}

fn main() {
    type TreeNodeRef = Rc<RefCell<TreeNode>>;
    let tr1: Vec<TreeNodeRef> = (1..=3).map(|i| Rc::new(RefCell::new(TreeNode::new(i)))).collect();
    tr1[0].borrow_mut().left.replace(tr1[1].clone());
    tr1[0].borrow_mut().right.replace(tr1[2].clone());
    let tr2: Vec<TreeNodeRef> = (1..=3).map(|i| Rc::new(RefCell::new(TreeNode::new(i)))).collect();
    tr2[0].borrow_mut().left.replace(tr2[2].clone());
    tr2[0].borrow_mut().right.replace(tr2[1].clone());
    println!("{}", Solution::is_same_tree(Some(tr1[0].clone()), Some(tr2[0].clone())));
}