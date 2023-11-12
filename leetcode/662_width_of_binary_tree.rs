use std::cell::RefCell;
use std::rc::Rc;

struct BinaryTreeVisitor {
    pub layers: Vec<(usize, usize)> // i-th layer: (left, right)
}

impl BinaryTreeVisitor {
    pub fn new() -> Self {
        Self { layers: Vec::new() }
    }

    fn _visit(&mut self, node: Rc<RefCell<TreeNode>>, layer: usize, pos: usize) {
        let layer_base = 1usize << layer;
        let layer_offset = pos - layer_base;
        if self.layers.len() <= layer {
            assert_eq!(self.layers.len(), layer);
            self.layers.push((layer_offset, layer_offset));
        } else {
            self.layers[layer].0 = self.layers[layer].0.min(layer_offset);
            self.layers[layer].1 = self.layers[layer].1.max(layer_offset);
        }

        if let Some(left) = node.borrow().left.clone() {
            self._visit(left, layer + 1, pos * 2);
        }

        if let Some(right) = node.borrow().right.clone() {
            self._visit(right, layer + 1, pos * 2 + 1);
        }
    }

    pub fn visit(&mut self, node: Rc<RefCell<TreeNode>>) {
        self._visit(node, 0, 1);
    }
}


impl Solution {
    pub fn width_of_binary_tree(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        if let Some(root) = root {
            let mut visitor = BinaryTreeVisitor::new();
            visitor.visit(root);

            let mut length = 0;

            for (l, r) in visitor.layers.iter() {
                assert!(l <= r);
                length = length.max(r + 1 - l);
            }

            length as i32
        } else {
            0
        }
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
            right: None,
        }
    }
}

fn build_tree_from_vec(v: &Vec<Option<i32>>) -> Option<Rc<RefCell<TreeNode>>> {
    let n = v.len();
    let nodes: Vec<Option<Rc<RefCell<TreeNode>>>> = (0..n)
        .map(|i| match v[i] {
            Some(val) => Some(Rc::new(RefCell::new(TreeNode::new(val)))),
            None => None,
        })
        .collect();
    for i in 0..n {
        if let Some(node) = &nodes[i] {
            let (l, r) = (2 * i + 1, 2 * i + 2);
            if l < n {
                if let Some(left) = &nodes[l] {
                    // eprintln!("{}@{} left {}@{}", node.borrow().val, i, left.borrow().val, l);
                    node.borrow_mut().left = Some(left.clone());
                }
            }
            if r < n {
                if let Some(right) = &nodes[r] {
                    // eprintln!("{}@{} right {}@{}", node.borrow().val, i, right.borrow().val, r);
                    node.borrow_mut().right = Some(right.clone());
                }
            }
        }
    }
    // eprintln!("{:?}", nodes[0]);
    return nodes[0].clone();
}

struct Solution;

fn main() {
    let testcases = vec![
        (
            vec![Some(1), Some(3), Some(2), Some(5), Some(3), None, Some(9)],
            4,
        ),
        (vec![Some(1), Some(3), Some(2), Some(5), None, None, Some(9), Some(6), None, None, None, None, None, Some(7)], 7),
    ];

    for (input, expected) in testcases.iter() {
        let tree = build_tree_from_vec(input);
        assert!(tree.is_some());
        let answer = Solution::width_of_binary_tree(tree);

        println!("{} {}", expected, answer);
        assert_eq!(*expected, answer);
    }
}
