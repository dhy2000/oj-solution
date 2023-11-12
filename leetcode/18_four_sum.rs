use std::collections::{HashSet, HashMap};
use std::convert::TryFrom;

#[allow(dead_code, unused_variables)]
impl Solution {
    pub fn four_sum(nums: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
        let n = nums.len();
        let mut value_map: HashMap<i32, Vec<usize>> = HashMap::new(); // value -> Vec<index>

        for (i, n) in nums.iter().enumerate() {
            value_map.entry(*n).and_modify(|v| v.push(i)).or_insert(vec![i]);
        }

        let mut answer: HashSet<Vec<i32>> = HashSet::new();
        for i in 0..n {
            for j in (i+1)..n {
                for k in (j+1)..n {
                    if i32::try_from((nums[i] as i64) + (nums[j] as i64) + (nums[k] as i64)).is_err() {
                        continue;
                    }
                    let r = target - nums[i] - nums[j] - nums[k];
                    if let Some(v) = value_map.get(&r) {
                        if v.iter().any(|l| *l > k) {
                            let mut v = vec![nums[i], nums[j], nums[k], r];
                            v.sort();
                            answer.insert(v);
                        }   
                    }
                }
            }
        }
        answer.into_iter().collect::<Vec<Vec<i32>>>()
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    // assert_eq!(
    //     Solution::four_sum(vec![1, 0, -1, 0, -2, 2], 0),
    //     vec![vec![-2, -1, 1, 2], vec![-2, 0, 0, 2], vec![-1, 0, 0, 1]]
    // );
    // assert_eq!(
    //     Solution::four_sum(vec![2, 2, 2, 2, 2], 8),
    //     vec![vec![2, 2, 2, 2]]
    // );
    println!("{:?}", Solution::four_sum(vec![1, 0, -1, 0, -2, 2], 0));
    println!("{:?}", Solution::four_sum(vec![2, 2, 2, 2, 2], 8));
    println!("{:?}", Solution::four_sum(vec![2; 200], 8));
    println!("{:?}", Solution::four_sum(vec![1000000000; 4], -294967296));
    println!("{:?}", Solution::four_sum(vec![-1000000000; 4], 294967296));
}
