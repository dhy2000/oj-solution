use std::collections::HashMap;

impl Solution {
    pub fn find_target_sum_ways(nums: Vec<i32>, target: i32) -> i32 {
        let mut count_sums = HashMap::<i32, i32>::new();
        count_sums.insert(0, 1);
        for n in nums.into_iter() {
            let count_sums_prev = count_sums.clone();
            count_sums.clear();
            for (sum, count) in count_sums_prev.into_iter() {
                *count_sums.entry(sum + n).or_insert(0) += count;
                *count_sums.entry(sum - n).or_insert(0) += count;
            }
        }
        *count_sums.get(&target).unwrap_or(&0)
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    assert_eq!(Solution::find_target_sum_ways(vec![1, 1, 1, 1, 1], 3), 5);
    assert_eq!(Solution::find_target_sum_ways(vec![1], 1), 1);
}