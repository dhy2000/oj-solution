use std::collections::{VecDeque, HashSet};

impl Solution {
    pub fn num_enclaves(grid: Vec<Vec<i32>>) -> i32 {
        // BFS from boundary
        let m = grid.len();
        assert!(m != 0);
        let n = grid[0].len();
        assert!(n != 0);
        assert!(grid.iter().all(|x| x.len() == n));
        let mut q: VecDeque<(usize, usize)> = VecDeque::new();
        let mut enqueued: HashSet<(usize, usize)> = HashSet::new();
        // add boundary into queue
        for i in 0..m {
            enqueued.insert((i, 0usize));
            q.push_back((i, 0usize));
            enqueued.insert((i, n - 1usize));
            q.push_back((i, n - 1usize));
        }
        for j in 1..n-1 {
            enqueued.insert((0usize, j));
            q.push_back((0usize, j));
            enqueued.insert((m - 1usize, j));
            q.push_back((m - 1usize, j));
        }
        // BFS
        while let Some((x, y)) = q.pop_front() {
            // println!("({}, {})={}", x, y, grid[x][y]);
            for (dx, dy) in vec![(-1, 0), (1, 0), (0, -1), (0, 1)] {
                let (nx, ny) = (x as i32 + dx, y as i32 + dy);
                if nx < 0 || ny < 0 {
                    continue;
                }
                let (nx, ny) = (nx as usize, ny as usize);
                if nx < m && ny < n {
                    if enqueued.contains(&(nx, ny)) {
                        continue;
                    }
                    if grid[x][y] == grid[nx][ny] {
                        // println!("--> ({}, {})={}", nx, ny, grid[nx][ny]);
                        enqueued.insert((nx, ny));
                        q.push_back((nx, ny));
                    }
                }
            }
        }
        let mut count = 0;
        for i in 0..m {
            for j in 0..n {
                if grid[i][j] == 1 && !enqueued.contains(&(i, j)) {
                    count += 1;
                }
            }
        }
        count
    }
}


/* END OF SOLUTION */

struct Solution;

fn main() {
    let grid = vec![
        vec![0, 0, 0, 0],
        vec![1, 0, 1, 0],
        vec![0, 1, 1, 0],
        vec![0, 0, 0, 0],
    ];
    println!("{}", Solution::num_enclaves(grid));
    let grid = vec![
        vec![0, 1, 1, 0],
        vec![0, 0, 1, 0],
        vec![0, 0, 1, 0],
        vec![0, 0, 0, 0],
    ];
    println!("{}", Solution::num_enclaves(grid));

    let grid = vec![
        vec![0,0,0,1,1,1,0,1,0,0],
        vec![1,1,0,0,0,1,0,1,1,1],
        vec![0,0,0,1,1,1,0,1,0,0],
        vec![0,1,1,0,0,0,1,0,1,0],
        vec![0,1,1,1,1,1,0,0,1,0],
        vec![0,0,1,0,1,1,1,1,0,1],
        vec![0,1,1,0,0,0,1,1,1,1],
        vec![0,0,1,0,0,1,0,1,0,1],
        vec![1,0,1,0,1,1,0,0,0,0],
        vec![0,0,0,0,1,1,0,0,0,1],
    ];
    println!("{}", Solution::num_enclaves(grid));
}