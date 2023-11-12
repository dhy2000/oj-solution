impl Solution {
    pub fn kids_with_candies(candies: Vec<i32>, extra_candies: i32) -> Vec<bool> {
        let max = candies.iter().max().unwrap();
        candies.iter().map(|x| *x + extra_candies >= *max).collect::<Vec<bool>>()
    }
}


/* END OF SOLUTION */

struct Solution;

fn main() {
    println!("{:?}", Solution::kids_with_candies(vec![2, 3, 5, 1, 3], 3));
    println!("{:?}", Solution::kids_with_candies(vec![4, 2, 1, 1, 2], 1));
    println!("{:?}", Solution::kids_with_candies(vec![12, 1, 12], 10));
}