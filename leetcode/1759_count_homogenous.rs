const MOD: i32 = 1000000007;

fn sum(n: i32) -> i32 {
    if n % 2 == 0 {
        ((((n / 2) % MOD) as i64) * ((n + 1) as i64) % (MOD as i64)) as i32
    } else {
        (((((n + 1) / 2) % MOD) as i64) * ((n) as i64) % (MOD as i64)) as i32
    }
}

impl Solution {
    pub fn count_homogenous(s: String) -> i32 {
        let mut ans = 0;
        let mut l = 0;
        for r in 1..s.len() {
            if s.as_bytes()[r] != s.as_bytes()[l] {
                ans += sum((r - l) as i32);
                ans %= MOD;
                l = r;
            }
        }
        ans += sum((s.len() - l) as i32);
        ans %= MOD;
        ans
    }
}

/* END OF SOLUTION */

struct Solution;

macro_rules! solve {
    ($s:expr) => {{
        let ans = Solution::count_homogenous(String::from($s));
        ans
    }};
}

fn main() {
    assert_eq!(solve!("abbcccaa"), 13);
    assert_eq!(solve!("xy"), 2);
    assert_eq!(solve!("zzzzz"), 15);
}
