// Referrred to the sample code

impl Solution {
    pub fn three_sum(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
        nums.sort();

        let mut answer = Vec::<Vec<i32>>::with_capacity(nums.len());

        for i in 0..nums.len() {
            if i > 0 && nums[i] == nums[i - 1] {
                continue;
            }

            let (mut l, mut r) = (i + 1, nums.len() - 1);
            while l < r {
                let s = nums[i] + nums[l] + nums[r];
                if s > 0 {
                    r -= 1;
                } else if s < 0 {
                    l += 1;
                } else {
                    answer.push(vec![nums[i], nums[l], nums[r]]);
                    l += 1;
                    while nums[l] == nums[l - 1] && l < r {
                        l += 1;
                    }
                }
            }
        }

        answer
    }
}

/* END OF SOLUTION */

use std::collections::BTreeSet;

struct Solution;

#[allow(unused_variables)]
fn main() {
    let testcases = vec![
        (
            vec![-1, 0, 1, 2, -1, -4],
            vec![vec![-1, -1, 2], vec![-1, 0, 1]],
        ),
        (vec![0, 1, 1], vec![]),
        (vec![0, 0, 0], vec![vec![0, 0, 0]]),
    ];

    for (i, (input, expect)) in testcases.iter().enumerate() {
        let answer = Solution::three_sum(input.clone());
        let expect = expect
            .iter()
            .map(|x| {
                let mut y = x.clone();
                y.sort();
                y
            })
            .collect::<BTreeSet<Vec<i32>>>();
        let answer = answer
            .iter()
            .map(|x| {
                let mut y = x.clone();
                y.sort();
                y
            })
            .collect::<BTreeSet<Vec<i32>>>();
        assert_eq!(answer, expect);
        println!("[PASSED] {}", i);
    }
}
