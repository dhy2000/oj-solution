use std::collections::{HashSet, HashMap};
use std::{rc::Rc, cell::RefCell, fmt};
use std::convert::TryFrom;

struct Node {
    id: usize,
    label: char,
    links: Vec<Rc<RefCell<Node>>>
}

impl fmt::Display for Node {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "node [<{}, {}>, ({})]", self.id, self.label, self.links.iter().map(|node| node.borrow().id.to_string()).reduce(|acc, t| acc + ", " + t.as_str()).unwrap_or("".to_string()))
    }
}

impl Node {
    fn new(id: usize, label: char) -> Self {
        Self { id, label, links: Vec::new() }
    }

    fn build(n: usize, edges: Vec<Vec<usize>>, labels: &String) -> Rc<RefCell<Node>> {
        let nodes: Vec<Rc<RefCell<Node>>> = (0..n).map(|x| usize::try_from(x).unwrap())
            .zip(labels.chars()).map(|(i, label)| Rc::new(RefCell::new(Node::new(i, label))))
            .collect();
        for edge in edges.iter() {
            let (left, right) = (
                usize::try_from(edge[0]).unwrap(),
                usize::try_from(edge[1]).unwrap()
            );
            nodes[left].borrow_mut().links.push(nodes[right].clone());
            nodes[right].borrow_mut().links.push(nodes[left].clone());
        }
        nodes[0].clone()
    }
}

struct Visitor
{
    _visited: HashSet<usize>,
    trace: Vec<Rc<RefCell<Node>>>,
}

impl Visitor {
    fn new() -> Self {
        Self { _visited: HashSet::new(), trace: Vec::new() }
    }
    fn visit(&mut self, node: Rc<RefCell<Node>>)
    {
        self._visited.insert(node.borrow().id);
        self.trace.push(node.clone());
        let to_visit: Vec<Rc<RefCell<Node>>> = node.borrow().links.iter()
            .filter(|n| !self._visited.contains(&n.borrow().id))
            .map(|x| x.clone())
            .collect();
        for next in to_visit.iter() {
            self.visit(next.clone())
        }
    }
}

impl Solution {
    pub fn count_sub_trees(n: i32, edges: Vec<Vec<i32>>, labels: String) -> Vec<i32> {
        let root = Node::build(
            usize::try_from(n).unwrap(), 
            edges.iter().map(|v| v.iter().map(|i| usize::try_from(*i).unwrap()).collect()).collect(), 
            &labels);
        let mut v = Visitor::new();
        v.visit(root.clone());
        let subtrees: Vec<RefCell<HashMap<char, i32>>> = vec![RefCell::new(HashMap::new()); usize::try_from(n).unwrap()];
        for node in v.trace.iter().rev() {
            let (id, label) = (node.borrow().id, node.borrow().label);
            let mut subtrees_this = subtrees[id].borrow_mut();
            for next in node.borrow().links.iter() {
                let subtrees_that = &subtrees[next.borrow().id].borrow_mut();
                for (k, v) in subtrees_that.iter() {
                    subtrees_this.entry(*k).and_modify(|v0| *v0 += v).or_insert(*v);
                }
            }
            subtrees_this.entry(label).and_modify(|v0| *v0 += 1).or_insert(1);
        }
        subtrees.iter().enumerate()
            .map(|(i, m)| *m.borrow().get(&labels.as_bytes()[i].into()).unwrap_or(&0))
            .collect()
    }
}

/* end of solution */
use std::{fs, io, time};
use std::io::{Write, BufRead};
struct Solution;

#[allow(dead_code)]
fn test_input(filename: String) {
    let timer = time::Instant::now();
    let file = fs::File::open(filename).expect("Failed to open file!");
    let mut reader = io::BufReader::new(file);
    let mut line = String::new();
    reader.read_line(&mut line).expect("Error input!");
    let n: i32 = line.trim().parse().expect("n should be number!");
    line.clear();
    println!("[{}] n = {}", timer.elapsed().as_millis(), n);
    let mut edges: Vec<Vec<i32>> = vec![];
    for _ in 1..n {
        reader.read_line(&mut line).expect("Error input!");
        edges.push(line.split_whitespace().map(|s| s.trim().parse::<i32>().unwrap()).collect::<Vec<i32>>());
        line.clear();
    }
    reader.read_line(&mut line).expect("Error Input!");
    let labels: String = line.clone();
    println!("[{}] input finished.", timer.elapsed().as_millis());
    io::stdout().flush().unwrap();
    println!("{:?}", Solution::count_sub_trees(n, edges, labels));
}

fn main() {
    println!("{:?}", Solution::count_sub_trees(7, vec![
        vec![0, 1], vec![0, 2], vec![1, 4], vec![1, 5], vec![2, 3], vec![2, 6]
    ], "abaedcd".to_string()));
    println!("{:?}", Solution::count_sub_trees(4, vec![
        vec![0, 1], vec![1, 2], vec![0, 3]
    ], "bbbb".to_string()));
    println!("{:?}", Solution::count_sub_trees(5, vec![
        vec![0, 1], vec![0, 2], vec![1, 3], vec![0, 4]
    ], "aabab".to_string()));
    println!("{:?}", Solution::count_sub_trees(7, vec![
        vec![0, 1], vec![1, 2], vec![2, 3], vec![3, 4], vec![4, 5], vec![5, 6]
    ], "aaabaaa".to_string()));
}
