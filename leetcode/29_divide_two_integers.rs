use std::{convert::TryFrom, cmp::Ordering};

// Do not use mult, div, mod

fn mult_cmp(base: i32, repeat: i32, other: i32) -> Ordering {
    // eprintln!("{}, {}, {}", base, repeat, other);
    assert!(base >= 0 && repeat >= 0 && other >= 0);
    let mut repeat = repeat as i64;
    let mut base = base as i64;
    let mut ans = 0i64;
    while repeat != 0 {
        if (repeat & 1) != 0 {
            ans += base;
        }
        base += base;
        repeat >>= 1;
    }
    
    match i32::try_from(ans) {
        Ok(num) => num.cmp(&other),
        Err(_) => Ordering::Greater,
    }
}

fn divide_helper(dividend: i32, divisor: i32) -> i32 {
    assert!(dividend >= 0 && divisor > 0 && dividend != i32::MIN);
    let (mut l, mut r) = (0, dividend);
    let mut mid = 0;
    while l <= r {
        
        mid = l + ((r - l) >> 1);
        // eprintln!("{}, {} -> {}", l, r, mid);
        match mult_cmp(divisor, mid, dividend) {
            Ordering::Less | Ordering::Equal => match mult_cmp(divisor, mid + 1, dividend) {
                Ordering::Less | Ordering::Equal => { l = mid + 1; },
                Ordering::Greater => { break; }
            },
            Ordering::Greater => { r = mid - 1; },
        }
    }
    assert!(l <= r);
    mid
}

macro_rules! signed {
    ($e:expr,$s:expr) => {
        if ($s < 0) { -$e } else { $e }
    };
}

impl Solution {
    pub fn divide(dividend: i32, divisor: i32) -> i32 {
        match (dividend, divisor) {
            (_, 1) => dividend,
            (i32::MIN, -1) => i32::MAX,
            (_, -1) => -dividend,
            (i32::MIN, i32::MIN) => 1,
            (_, i32::MIN) => 0,
            (i32::MIN, _) => {
                let sign_divisor = divisor.signum();
                let mut divisor = divisor.abs();
                if (divisor & (divisor - 1)) == 0 {
                    let mut dividend = dividend;
                    // is power of 2
                    while divisor > 1 {
                        divisor >>= 1;
                        dividend >>= 1;
                    }
                    dividend
                } else {
                    signed!(divide_helper((dividend + 1).abs(), divisor), -sign_divisor)
                }
            },
            (_, _) => {
                let sign_dividend = dividend.signum();
                let sign_divisor = divisor.signum();
                let dividend = dividend.abs();
                let divisor = divisor.abs();

                signed!(divide_helper(dividend, divisor), signed!(sign_dividend, sign_divisor))
            }
        }
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    // assert_eq!(Solution::divide(10, 3), 3);
    // assert_eq!(Solution::divide(7, -3), -2);
    // assert_eq!(Solution::divide(1, 2), 0);
    // assert_eq!(Solution::divide(-2147483648, 2), -1073741824);
    // assert_eq!(Solution::divide(-2147483648, 4), -536870912);
    // assert_eq!(Solution::divide(-2147483648, 3), -715827882);
    // assert_eq!(Solution::divide(-1010369383, -2147483648), 0);
    assert_eq!(Solution::divide(2147483647, -1), -2147483647);
}