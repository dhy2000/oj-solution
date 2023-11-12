use std::collections::BinaryHeap;

impl Solution {
    pub fn last_stone_weight(stones: Vec<i32>) -> i32 {
        #[derive(Clone, Copy, PartialEq, Eq, PartialOrd)]
        struct Elem(i32);
        impl Ord for Elem {
            fn cmp(&self, other: &Self) -> std::cmp::Ordering {
                self.0.cmp(&other.0)
            }
        }

        impl From<i32> for Elem {
            fn from(n: i32) -> Self {
                Self(n)
            }
        }

        let mut heap = BinaryHeap::<Elem>::new();

        for s in stones.into_iter() {
            heap.push(Elem(s));
        }

        while let Some(s) = heap.pop() {
            let s = s.0;
            if let Some(t) = heap.pop() {
                let t = t.0;
                if s != t {
                    heap.push(Elem(s.max(t) - s.min(t)));
                }
            } else {
                return s;
            }
        }
        0
    }
}

/// END OF SOLUTION

struct Solution;

fn main() {
    let testcases = vec![
        (vec![2, 7, 4, 1, 8, 1], 1),
        (vec![1], 1),
    ];

    for (i, (stones, expect)) in testcases.into_iter().enumerate() {
        let answer = Solution::last_stone_weight(stones);
        assert_eq!(answer, expect);
        println!("[PASSED] {i}");
    }
}