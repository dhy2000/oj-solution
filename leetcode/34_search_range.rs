impl Solution {
    pub fn search_range(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let n = nums.len();
        if n == 0 {
            return vec![-1, -1];
        }
        let (mut l, mut r): (usize, usize) = (0, n - 1);
        let mut mid = 0;
        // lower-bound: nums[mid] = target && (mid == 0 || nums[mid - 1] < target)
        while l <= r {
            mid = l + (r - l) / 2;

            if nums[mid] < target {
                l = mid + 1;
            }
            else if nums[mid] > target {
                if mid == 0 {
                    l = 1; r = 0;
                    break;
                }
                r = mid - 1;
            }
            else {
                if mid > 0 && nums[mid - 1] == target {
                    if mid == 0 {
                        l = 1; r = 0;
                        break;
                    }
                    r = mid - 1;
                }
                else { break; }
            }
        }
        if l > r {
            return vec![-1, -1];
        }
        let lower_bound = mid;
        // upper-bound
        l = 0;
        r = n - 1;
        while l <= r {
            mid = l + (r - l) / 2;
            if nums[mid] < target {
                l = mid + 1;
            }
            else if nums[mid] > target {
                if mid == 0 {
                    l = 1; r = 0;
                    break;
                }
                r = mid - 1;
            }
            else {
                if mid < n - 1 && nums[mid + 1] == target {
                    l = mid + 1;
                }
                else { break; }
            }
        }
        assert!(l <= r);
        let upper_bound = mid;
        assert!(lower_bound <= upper_bound);
        vec![lower_bound as i32, upper_bound as i32]

    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    assert_eq!(Solution::search_range(vec![5, 7, 7, 8, 8, 10], 8), vec![3, 4]);
    assert_eq!(Solution::search_range(vec![5, 7, 7, 8, 8, 10], 6), vec![-1, -1]);
    assert_eq!(Solution::search_range(vec![], 0), vec![-1, -1]);
    assert_eq!(Solution::search_range(vec![1], 0), vec![-1, -1]);


    assert_eq!(Solution::search_range(vec![1; 100000], 1), vec![0, 99999]);
    

    
}



/*
// Sample 0ms solution

impl Solution {
    pub fn search_range(nums: Vec<i32>, target: i32) -> Vec<i32> {
        
        let pos = nums.binary_search(&target);
        if pos.is_err() {return vec![-1,-1]}
        let pos = pos.unwrap();

        let mut leftmost = pos;
        for i in (0..=pos).rev() {
            if nums[i] != target {break}
            leftmost = i;
        }
        let mut rightmost = pos;
        for i in pos..nums.len() {
            if nums[i] != target {break}
            rightmost = i;
        }
        vec![leftmost as i32,rightmost as i32]
    }
}


 */