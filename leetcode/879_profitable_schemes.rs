#[allow(dead_code, unused_variables)]
const MOD: u64 = 1000000007;

struct Searcher {
    num_people: usize,
    min_profit: usize,
    crimes: Vec<(usize, usize)>,
    memo: Vec<Vec<Vec<Option<u64>>>>,
}

impl Searcher {
    pub fn new(num_people: usize, min_profit: usize, crimes: Vec<(usize, usize)>) -> Self {
        let num_crimes = crimes.len();
        Self {
            num_people,
            min_profit,
            crimes,
            memo: vec![vec![vec![None; min_profit + 1]; num_people + 1]; num_crimes + 1],
        }
    }

    fn visit(&mut self, index: usize, people: usize, profit: usize) -> u64 {
        assert!(people <= self.num_people);

        if index >= self.crimes.len() {
            return if profit >= self.min_profit { 1 } else { 0 } 
        }

        if let Some(m) = self.memo[index][people][profit] {
            return m;
        }

        let mut sum = self.visit(index + 1, people, profit);
        let (g, p) = self.crimes[index];
        if people + g <= self.num_people {
            sum += self.visit(index + 1, people + g, (profit + p).min(self.min_profit));
        }

        sum = sum % MOD;
        self.memo[index][people][profit] = Some(sum);
        sum
    }
}

#[allow(dead_code, unused_variables, unused_mut)]
impl Solution {
    pub fn profitable_schemes(n: i32, min_profit: i32, group: Vec<i32>, profit: Vec<i32>) -> i32 {
        let n = n as usize;
        let min_profit = min_profit as usize;
        let sum_profit = profit.iter().sum::<i32>() as usize; // max 100 * 100 = 10000
        assert_eq!(group.len(), profit.len());
        let crimes = group
            .iter()
            .map(|x| *x as usize)
            .zip(profit.iter().map(|x| *x as usize))
            .collect::<Vec<(usize, usize)>>(); // (group, profit)
        let mut searcher = Searcher::new(n, min_profit, crimes);
        searcher.visit(0, 0, 0) as i32
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    let testcases = vec![
        ((5, 3, vec![2, 2], vec![2, 3]), 2),
        ((10, 5, vec![2, 3, 5], vec![6, 7, 8]), 7),
        ((64, 0, vec![80, 40], vec![88, 88]), 2),
    ];

    for (i, ((n, min_profit, group, profit), expected)) in testcases.into_iter().enumerate() {
        let answer = Solution::profitable_schemes(n, min_profit, group, profit);
        assert_eq!(answer, expected);
        println!("passed {}", i);
    }
}
