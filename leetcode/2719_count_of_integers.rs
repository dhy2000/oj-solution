const MOD: i32 = 1000000007;

macro_rules! modp {
    ($x:expr) => {
        ((($x as i32) % MOD) + MOD) % MOD
    }
}

/// Count of `n` digits `00..0` to `99..9` whose digit sum is not greater than `lim`.
/// 
/// Also count of integer solution of $x_1 + x_2 + \cdots + x_n \le lim$ where $0 \le x_i \le 9$.
fn count_n_digits(n: usize, lim: usize) -> i32 {
    if n == 0 {
        return 1;
    }
    let mut dp: Vec<Vec<i32>> = vec![vec![0; (lim + 1) as usize]; n as usize];
    for i in 0..n {
        for j in 0..=lim {
            let mut s = 0;
            for k in 0..=9.min(j) {
                s += if i == 0 { 1 } else { dp[i - 1][j - k] };
                s %= MOD;
            }
            dp[i][j] = s;

        }
    }
    dp[n - 1][lim]
}

/// Count of `0` to `n-1` whose digit sum is not greater than `lim`.
fn count_until_n(n: &str, lim: i32) -> i32 {
    let mut ans = 0;
    for i in 0..n.len() {
        let prefix_sum = n[0..i].bytes().map(|b| (b as i32) - ('0' as i32)).sum::<i32>();
        let cur = n[i..=i].parse::<i32>().unwrap();
        let suffix_len = n.len() - i - 1;
        for c in 0..cur {
            if lim >= prefix_sum + c {
                ans += count_n_digits(suffix_len, (lim - prefix_sum - c) as usize);
                ans %= MOD;
            }
        }
    }
    ans
}

fn add_one(n: String) -> String {
    let mut digits = n.into_bytes().into_iter().map(|b| (b as i32) - ('0' as i32)).collect::<Vec<i32>>();
    digits.reverse();
    digits[0] += 1;
    let mut i = 0;
    while i + 1 < digits.len() && digits[i] >= 10 {
        digits[i] -= 10;
        digits[i + 1] += 1;
        i += 1;
    }
    if i < digits.len() && digits[i] >= 10 {
        assert_eq!(i + 1, digits.len());
        digits[i] -= 10;
        digits.push(1);
    }
    digits.reverse();
    digits.into_iter().map(|d| d.to_string()).collect::<Vec<String>>().join("")
}

impl Solution {
    pub fn count(num1: String, num2: String, min_sum: i32, max_sum: i32) -> i32 {
        let n2 = add_one(num2);
        let s2 = modp!(count_until_n(&n2, max_sum) - count_until_n(&n2, min_sum - 1));
        let s1 = modp!(count_until_n(&num1, max_sum) - count_until_n(&num1, min_sum - 1));
        modp!(s2 - s1)
    }
}

/* END OF SOLUTION */

struct Solution;

macro_rules! solve {
    ($num1:expr,$num2:expr,$min_sum:expr,$max_sum:expr) => {{
        let ans = Solution::count(String::from($num1), String::from($num2), $min_sum, $max_sum);
        println!("{}", ans);
        ans
    }};
}

fn main() {
    assert_eq!(add_one(String::from("1")), String::from("2"));
    assert_eq!(add_one(String::from("9999")), String::from("10000"));
    assert_eq!(count_n_digits(3, 28), 1000);
    assert_eq!(count_until_n("20", 5), 11);
    assert_eq!(solve!("1", "12", 1, 8), 11);
    assert_eq!(solve!("1", "5", 1, 5), 5);
}
