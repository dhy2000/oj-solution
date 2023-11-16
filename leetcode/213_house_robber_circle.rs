impl Solution {
    fn rob_range(nums: &[i32]) -> i32 {
        assert!(!nums.is_empty());
        let n = nums.len();
        let mut dp = vec![0; n];
        for (i, v)in nums.into_iter().enumerate() {
            let last1 = (i >= 1).then(|| dp[i - 1]).unwrap_or(0);
            let last2 = (i >= 2).then(|| dp[i - 2]).unwrap_or(0);
            dp[i] = last1.max(last2 + v);
        }
        dp[n - 1]
    }

    pub fn rob(nums: Vec<i32>) -> i32 {
        match nums.len() {
            1 => nums[0],
            n @ _ => Self::rob_range(&nums[1..]).max(Self::rob_range(&nums[..(n-1)])),
        }
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    assert_eq!(Solution::rob(vec![2, 3, 2]), 3);
    assert_eq!(Solution::rob(vec![1, 2, 3, 1]), 4);
    assert_eq!(Solution::rob(vec![1, 2, 3]), 3);
}