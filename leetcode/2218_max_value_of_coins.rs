#[allow(dead_code, unused_variables)]
impl Solution {
    pub fn max_value_of_coins(piles: Vec<Vec<i32>>, k: i32) -> i32 {
        let n = piles.len();
        let k = k as usize;
        // For each pile i, what will be the total value of coins we can collect if we choose the first j coins?
        let prefix_sum = piles.iter().map(|v| {
            let mut s = vec![0; v.len() + 1];
            for (i, x) in v.iter().enumerate() {
                s[i + 1] = s[i] + *x;
            }
            s
        }).collect::<Vec<Vec<i32>>>();
        // eprintln!("{:?}", prefix_sum);
        // dp[i][j]: first i piles, j coins
        // dp[i][j] = max(dp[i - 1][j - 0] + prefix_sum[i][0], dp[i - 1][j - 1] + prefix_sum[i][1], ...) until j - j or j - numof(pile i)
        let mut dp = (1..=n).map(|_| vec![0; k + 1]).collect::<Vec<Vec<i32>>>();
        dp[0][0] = 0;
        for i in 0..n {
            for j in 0..=k {
                let num_pile_i = piles[i].len();
                dp[i][j] = (0..=j.min(num_pile_i)).map(|k| {
                    assert!(j >= k);
                    assert!(k < prefix_sum[i].len());
                    (if i > 0 { dp[i - 1][j - k] } else { 0 }) + prefix_sum[i][k]
                }).max().unwrap();
            }
        }
        // eprintln!("{:?}", dp);
        dp[n - 1][k]
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    assert_eq!(Solution::max_value_of_coins(vec![
        vec![1, 100, 3], vec![7, 8, 9]
    ], 2), 101);
    assert_eq!(Solution::max_value_of_coins(vec![
        vec![100], vec![100], vec![100], vec![100], vec![100], vec![100], 
        vec![1, 1, 1, 1, 1, 1, 700],
    ], 7), 706);
}