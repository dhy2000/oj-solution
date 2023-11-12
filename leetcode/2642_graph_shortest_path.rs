use std::collections::{HashMap, HashSet, BinaryHeap};

#[derive(PartialEq, Eq)]
struct Edge {
    to: i32,
    weight: i32,
}

impl PartialOrd for Edge {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for Edge {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.weight.cmp(&other.weight).reverse().then(self.to.cmp(&other.to))
    }
}

struct Graph(HashMap<i32, Vec<Edge>>);

impl Graph {
    fn new(n: i32, edges: Vec<Vec<i32>>) -> Self {
        let mut s = Self(HashMap::<i32, Vec<Edge>>::new());
        for edge in edges.into_iter() {
            s.add_edge(edge);
        }
        assert!(s.0.len() <= n as usize);
        s
    }
    
    fn add_edge(&mut self, edge: Vec<i32>) {
        assert_eq!(edge.len(), 3);
        let (from, to, weight) = (edge[0], edge[1], edge[2]);
        self.0.entry(from).or_insert(Vec::new()).push(Edge { to, weight });
        self.0.entry(to).or_insert(Vec::new());
    }
    
    fn shortest_path(&self, node1: i32, node2: i32) -> i32 {
        if !(self.0.contains_key(&node1) && self.0.contains_key(&node2)) {
            return if node1 == node2 { 0 } else { -1 };
        }
        let mut dist = HashMap::<i32, i32>::new();
        let mut vis = HashSet::<i32>::new();
        let mut pq = BinaryHeap::<Edge>::new();
        dist.insert(node1, 0);
        pq.push(Edge { to: node1, weight: 0 });
        while let Some(cur) = pq.pop() {
            if vis.contains(&cur.to) {
                continue;
            }
            vis.insert(cur.to);
            for next in self.0.get(&cur.to).unwrap().iter() {
                if !dist.contains_key(&next.to) || *dist.get(&next.to).unwrap() > dist.get(&cur.to).unwrap() + next.weight {
                    dist.insert(next.to, dist.get(&cur.to).unwrap() + next.weight);
                    pq.push(Edge { to: next.to, weight: *dist.get(&next.to).unwrap() })
                }
            }
        }
        dist.get(&node2).and_then(|x| Some(*x)).unwrap_or(-1)
    }
}

/* END OF SOLUTION */

impl std::fmt::Debug for Graph {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let elems = self.0.iter().map(|(k, v)| format!("{k}: [{}]", v.iter().map(|e| format!("{}({})", e.to, e.weight)).reduce(|acc, t| acc + ", " + &t).unwrap_or(String::new())));
        write!(f, "[{}\n]", elems.map(|e| format!("  {}", e)).fold(String::from(""), |acc, t| acc + "\n" + &t))
    }
}

fn main() {
    let mut graph = Graph::new(4, vec![
        vec![0, 2, 5], vec![0, 1, 2], vec![1, 2, 1], vec![3, 0, 3]
    ]);
    assert_eq!(graph.shortest_path(3, 2), 6);
    assert_eq!(graph.shortest_path(0, 3), -1);
    graph.add_edge(vec![1, 3, 4]);
    assert_eq!(graph.shortest_path(0, 3), 6);
    println!("{:?}", graph);
    /*
    [
        [6,[[3,5,990551],[1,3,495721],[0,1,985797],[4,5,422863],[4,1,505663]]],
        [0,1],[3,5],[4,4],[0,3],
        [[5,0,250117]],
        [4,5],
        [[3,1,142005]],
        [2,2],
        [4,0],
        [[2,0,124744]],
        [[5,1,74396]],
        [3,3],
        [[3,2,571238]],
        [[1,4,3408]],
        [[0,4,832]],
        [[5,2,417]],
        [2,2],[2,4],
        [[2,3,80]],
        [[5,4,6]],
        [3,4],
        [[4,3,837171]],
        [[1,2,162278]],
        [[3,4,1]],
        [2,0],
        [[0,3,1]],
        [0,4],
        [3,5],
        [1,1],
        [3,4],
        [[4,2,1]],
        [[2,1,1]]
    ]
     */

    let mut graph = Graph::new(6, vec![
        vec![3,5,990551],
        vec![1,3,495721],
        vec![0,1,985797],
        vec![4,5,422863],
        vec![4,1,505663]
    ]);
    println!("{}", graph.shortest_path(0, 1));
    println!("{}", graph.shortest_path(3, 5));
    println!("{}", graph.shortest_path(4, 4));
    println!("{}", graph.shortest_path(0, 3));
    graph.add_edge(vec![5,0,250117]);
    println!("{}", graph.shortest_path(4, 5));
    graph.add_edge(vec![3,1,142005]);
    println!("{} !", graph.shortest_path(2, 2));
    println!("{}", graph.shortest_path(4, 0));
    graph.add_edge(vec![2,0,124744]);
    graph.add_edge(vec![5,1,74396]);
    println!("{}", graph.shortest_path(3, 3));
    graph.add_edge(vec![3,2,571238]);
    graph.add_edge(vec![1,4,3408]);
    graph.add_edge(vec![0,4,832]);
    graph.add_edge(vec![5,2,417]);
    println!("{}", graph.shortest_path(2, 2));
    println!("{}", graph.shortest_path(2, 4));
    graph.add_edge(vec![2,3,80]);
    graph.add_edge(vec![5,4,6]);
    println!("{}", graph.shortest_path(3, 4));
    graph.add_edge(vec![4,3,837171]);
    graph.add_edge(vec![1,2,162278]);
    graph.add_edge(vec![3,4,1]);
    println!("{}", graph.shortest_path(2, 0));
    graph.add_edge(vec![0,3,1]);
    println!("{}", graph.shortest_path(0, 4));
    println!("{}", graph.shortest_path(3, 5));
    println!("{}", graph.shortest_path(1, 1));
    println!("{}", graph.shortest_path(3, 4));
    graph.add_edge(vec![4,2,1]);
    graph.add_edge(vec![2,1,1]);
}