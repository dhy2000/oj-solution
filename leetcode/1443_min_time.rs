use std::collections::HashSet;
use std::convert::TryFrom;

/* Tree Structure */
type Edges = Vec<usize>;
type Tree = Vec<Edges>;

struct Solver {
    visited: HashSet<usize>
}

impl Solver {
    fn new() -> Self {
        Self { visited: HashSet::new() }
    }

    fn solve(&mut self, id: usize, tree: &Tree, has_apple: &Vec<bool>) -> Option<i32> {
        println!("visit: {}", id);
        match tree[id].len() {
            0 => if has_apple[id] { Some(1) } else { None },
            _ => {
                self.visited.insert(id);
                let mut need_down = false;
                let mut cost = 0;
                for e in tree[id].iter() {
                    if self.visited.contains(e) {
                        continue;
                    }
                    let r = self.solve(*e, tree, has_apple);
                    match r {
                        Some(r) => {
                            cost += 2 + r;
                            need_down = true;
                        },
                        None => ()
                    }
                }
                if has_apple[id] || need_down {
                    Some(cost)
                } else {
                    None
                }
            }
        }
    }
}


impl Solution {
    pub fn min_time(n: i32, edges: Vec<Vec<i32>>, has_apple: Vec<bool>) -> i32 {
        // build tree
        let mut tree: Tree = (0..n).map(|_| Edges::new()).collect();
        edges.iter().for_each(|edge| {
            let (left, right) = (edge[0], edge[1]);
            let (left, right) = (usize::try_from(left).unwrap(), usize::try_from(right).unwrap());
            tree[left].push(right);
            tree[right].push(left);
        });
        Solver::new().solve(0usize, &tree, &has_apple).unwrap_or(0)
    }
}

/* end of solution */

struct Solution;

fn main() {
    println!("{}", Solution::min_time(7, vec![
        vec![0, 1], vec![0, 2], vec![1, 4], vec![1, 5], vec![2, 3], vec![2, 6]
    ], vec![false, false, true, false, true, true, false]));
    println!("{}", Solution::min_time(7, vec![
        vec![0, 1], vec![0, 2], vec![1, 4], vec![1, 5], vec![2, 3], vec![2, 6]
    ], vec![false, false, true, false, false, true, false]));
    println!("{}", Solution::min_time(7, vec![
        vec![0, 1], vec![0, 2], vec![1, 4], vec![1, 5], vec![2, 3], vec![2, 6]
    ], vec![false, false, false, false, false, false, false]));
}

/*
use std::borrow::BorrowMut;
use std::hash::{Hash, Hasher};
use std::rc::Rc;
use std::cell::RefCell;
use std::convert::TryFrom;

struct TreeNode {
    id: i32,
    children: Vec<Option<Tree>>,
    has_apple: RefCell<bool>, // self and children
    cost: RefCell<i32>
}

type Tree = Rc<RefCell<TreeNode>>;

impl Hash for TreeNode {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

impl PartialEq for TreeNode {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }

    fn ne(&self, other: &Self) -> bool {
        self.id != other.id
    }
}

impl TreeNode {
    fn new(id: i32, has_apple: bool) -> Self {
        Self { id, children: vec![], has_apple: RefCell::new(has_apple), cost: RefCell::new(0) }
    }

    fn resolve(&self) {
        self.children.iter().for_each(|child| {
            if let Some(child) = child {
                child.borrow().resolve();
                if *child.borrow().has_apple.borrow() {
                    self.has_apple.replace(true);
                    let cost = *self.cost.borrow();
                    self.cost.replace(cost + 2 + *child.borrow().cost.borrow());
                }
            }
        });
    }
}

impl Solution {
    pub fn min_time(n: i32, edges: Vec<Vec<i32>>, has_apple: Vec<bool>) -> i32 {
        assert_eq!(usize::try_from(n).unwrap(), has_apple.len());
        // build tree node
        let tree: Vec<Tree> = (0..n).zip(has_apple.into_iter()).map(|(id, has_apple)| {
            Rc::new(RefCell::new(TreeNode::new(id, has_apple)))
        }).collect();
        // setup edge
        edges.into_iter().for_each(|edges| {
            assert_eq!(edges.len(), 2);
            let (left, right) = (usize::try_from(edges[0]).unwrap(), usize::try_from(edges[1]).unwrap());
            // tree[left].borrow().children.borrow_mut().push(Some(tree[right].clone()));
            // tree[right].borrow().children.borrow_mut().push(Some(tree[left].clone()));
            let mut t = &tree[left].borrow().children;
            t.push(Some(tree[right].clone()));
            t.push(value)
        });


        0
    }
}

*/