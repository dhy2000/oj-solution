use std::rc::Rc;
use std::cell::RefCell;
impl Solution {

    fn zig_zag_helper(node: Rc<RefCell<TreeNode>>) -> (i32, i32, i32) {
        // returns: (longest path from left, longest path from right, max of sub tree)
        // return.0 and return.1 **includes** itself, a leaf node returns (val, val, 0)
        // e.g. 1-(2, 3) returns (1, 1, _)
        // let val = node.borrow().val;
        let val = 1;
        let ret = 
        match (node.borrow().left.clone(), node.borrow().right.clone()) {
            (Some(left), Some(right)) => {
                let z_left = Self::zig_zag_helper(left.clone());
                let z_right = Self::zig_zag_helper(right.clone());
                let (l, r) = (val + z_left.1, val + z_right.0);
                (l, r, z_left.2.max(z_right.2).max(l).max(r))
            },
            (Some(left), None) => {
                let z_left = Self::zig_zag_helper(left.clone());
                let (l, r) = (val + z_left.1, val);
                (l, r, z_left.2.max(l).max(r))
            },
            (None, Some(right)) => {
                let z_right = Self::zig_zag_helper(right.clone());
                let (l, r) = (val, val + z_right.0);
                (l, r, z_right.2.max(l).max(r))
            },
            (None, None) => {
                (val, val, val)
            },
        };
        eprintln!("{}: ({}, {}, {})", val, ret.0, ret.1, ret.2);
        ret
    }

    pub fn longest_zig_zag(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        if let Some(root) = root {
            Self::zig_zag_helper(root.clone()).2
        } else { 0 }
    }
}

/* END OF SOLUTION */

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
  pub val: i32,
  pub left: Option<Rc<RefCell<TreeNode>>>,
  pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
  #[inline]
  pub fn new(val: i32) -> Self {
    TreeNode {
      val,
      left: None,
      right: None
    }
  }
}

// impl fmt::Debug for TreeNode {
//     fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
//         write!(f, "{} -> ({}, {})", self.val, 
//             match self.left { Some(left) => left.borrow().val.to_string() , None => "null".to_string() },
//             match self.right { Some(right) => right.borrow().val.to_string() , None => "null".to_string() },
//         )
//     }
// }

fn build_tree_from_vec(v: Vec<Option<i32>>) -> Option<Rc<RefCell<TreeNode>>> {
    let n = v.len();
    let nodes: Vec<Option<Rc<RefCell<TreeNode>>>> = (0..n).map(|i| {
        match v[i] {
            Some(val) => Some(Rc::new(RefCell::new(TreeNode::new(val)))),
            None => None,
        }
    }).collect();
    for i in 0..n {
        if let Some(node) = &nodes[i] {
            let (l, r) = (2 * i + 1, 2 * i + 2);
            if l < n {
                if let Some(left) = &nodes[l] {
                    eprintln!("{} left {}", i, l);
                    node.borrow_mut().left = Some(left.clone());
                }
            }
            if r < n {
                if let Some(right) = &nodes[r] {
                    eprintln!("{} right {}", i, r);
                    node.borrow_mut().right = Some(right.clone());
                }
            }
        }
    }
    eprintln!("{:?}", nodes[0]);
    return nodes[0].clone()
}

struct Solution;

fn main() {
    let tr = build_tree_from_vec(vec![
        Some(1), None, Some(1), Some(1), Some(1), None, None, Some(1), Some(1), None, Some(1), None, None, None, Some(1), None, Some(1)
    ]);
    assert_eq!(Solution::longest_zig_zag(tr), 3);
}