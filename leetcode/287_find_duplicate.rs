use std::collections::HashMap;

impl Solution {
    pub fn find_duplicate(nums: Vec<i32>) -> i32 {
        let mut cnt_nums = HashMap::<i32, usize>::new();
        for n in nums.into_iter() {
            cnt_nums.entry(n).and_modify(|x| *x += 1).or_insert(1);
        }
        cnt_nums.iter().filter(|&(_, v)| *v >= 2).map(|(k, _)| *k).next().unwrap()
    }
}

/* END OF SOLUTION */

/*
 Assume n = 4, n + 1 = 5
 1, 2, 2, 3, 4 => min = 1, max = 4, sum = 12
 1, 2, 3, 3, 4 => min = 1, max = 4, sum = 13
 1, 2, 3, 3, 3 => min = 1, max = 3, sum = 12
 1, 2, 2, 2, 4 => min = 1, max = 4, sum = 11
 1, 1, 2, 3, 4 => min = 1, max = 4, sum = 11

 // repeat 1: [1, 1, 1, 1, 1], [1, 1, 2, 3, 4]
 // repeat 2: [2, 2, 2, 2, 2], [1, 2, 2, 3, 4]
 // repeat 3: [3, 3, 3, 3, 3], [1, 2, 3, 3, 4]
 // repeat 4: [4, 4, 4, 4, 4], [1, 2, 3, 4, 4]
 */

fn eval_sum2(nums: Vec<i32>) {
    let n2 = nums.clone();
    eprintln!("({}, {})", nums.into_iter().sum::<i32>(), n2.into_iter().map(|x| x * x).sum::<i32>())
}

struct Solution;

fn main() {
    eval_sum2(vec![1, 2, 3, 3, 4]); // 13, 39
    eval_sum2(vec![1, 2, 2, 3, 4]); // 12, 34
    eval_sum2(vec![1, 2, 2, 2, 4]); // 11, 29
    eval_sum2(vec![1, 1, 2, 3, 4]); // 11, 31
    eval_sum2(vec![1, 3, 3, 3, 4]); // 14, 44
    eval_sum2(vec![1, 1, 1, 1, 2]); // 6, 8
    eval_sum2(vec![1, 1, 1, 1, 4]); // 8, 20
    println!("{}", Solution::find_duplicate(vec![1, 3, 4, 2, 2]));
    println!("{}", Solution::find_duplicate(vec![3, 1, 3, 4, 2]));
}