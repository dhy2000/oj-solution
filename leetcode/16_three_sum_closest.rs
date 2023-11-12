use std::collections::{BTreeMap, HashSet};

impl Solution {
    pub fn three_sum_closest(nums: Vec<i32>, target: i32) -> i32 {
        // pre-process
        let mut sum_pairs = BTreeMap::<i32, HashSet<(usize, usize)>>::new();
        for i in 0..nums.len() {
            for j in (i + 1)..nums.len() {
                sum_pairs
                    .entry(nums[i] + nums[j])
                    .or_insert(HashSet::new())
                    .insert((i, j));
            }
        }
        let mut closest_sum = None::<i32>;
        let mut update = |sum: i32| {
            if let Some(closest) = closest_sum {
                if (sum - target).abs() < (closest - target).abs() {
                    closest_sum = Some(sum);
                }
            } else {
                closest_sum = Some(sum);
            }
        };
        for i in 0..nums.len() {
            let sums = sum_pairs
                .iter()
                .filter_map(|(k, v)| v.iter().any(|p| p.0 != i && p.1 != i).then(|| *k))
                .collect::<Vec<i32>>();
            let expect = target - nums[i];
            assert!(!sums.is_empty());
            if sums[0] >= expect {
                update(sums[0] + nums[i]);
            } else if sums[sums.len() - 1] <= expect {
                update(sums[sums.len() - 1] + nums[i]);
            } else {
                assert!(sums.len() >= 2);
                let (mut l, mut r) = (0, sums.len() - 2);
                while l <= r {
                    let mid = (l + r) / 2;
                    // sums[mid] <= expect && sums[mid + 1] > expect
                    if sums[mid] > expect {
                        r = mid - 1;
                    } else if sums[mid + 1] < expect {
                        l = mid + 1;
                    } else {
                        update(sums[mid] + nums[i]);
                        update(sums[mid + 1] + nums[i]);
                        break;
                    }
                }
            }
        }
        closest_sum.unwrap()
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    assert_eq!(Solution::three_sum_closest(vec![-1, 2, 1, -4], 1), 2);
    assert_eq!(Solution::three_sum_closest(vec![0, 0, 0], 1), 0);
    assert_eq!(Solution::three_sum_closest(vec![0, 1, 2], 0), 3);
}
