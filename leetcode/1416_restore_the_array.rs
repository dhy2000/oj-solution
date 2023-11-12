const MOD: i32 = 1000000007;

impl Solution {
    pub fn number_of_arrays(s: String, k: i32) -> i32 {
        // dp[i]: first i digit, dp[-1] = 1
        let mut dp = vec![0; s.len()];

        let lenk = k.to_string().len();

        for i in 0..s.len() {
            let mut len = 1;
            let mut sum = 0;
            while len <= (i + 1).min(lenk) {
                if s.as_bytes()[(i + 1 - len)] as char == '0' {
                    len += 1;
                    continue;
                }
                let last = s.as_str()[(i + 1 - len)..=i].parse::<i32>();
                if last.is_err() {
                    break;
                }
                let last = last.unwrap();
                if 1 <= last && last <= k {
                    sum += if i < len {
                        1
                    } else {
                        dp[i - len]
                    };
                    while sum >= MOD {
                        sum -= MOD;
                    }
                }
                len += 1;
            }
            // eprintln!("dp[{i}] = {sum}");
            dp[i] = sum;
        }
        dp[s.len() - 1]
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    let testcases = vec![
        (("1000", 10000), 1),
        (("1000", 10), 0),
        (("1317", 2000), 8),
        (("2020", 30), 1),
        (
            ("600342244431311113256628376226052681059918526204", 703),
            411743991,
        ),
    ];

    for (i, ((s, k), expect)) in testcases.into_iter().enumerate() {
        let answer = Solution::number_of_arrays(s.to_string(), k);
        assert_eq!(answer, expect);
        println!("[PASSED] {i}");
    }

    let mut big_s = String::from("1");
    for _ in 1..=100000 {
        big_s.push_str("0");
    }
    let big_k = 1000000000;
    let answer = Solution::number_of_arrays(big_s, big_k);
    println!("[FINISH] {answer}");

    let mut big_s = String::from("");
    for _ in 1..=10000 {
        big_s.push_str("1234567890");
    }
    let big_k = 1000000000;
    let answer = Solution::number_of_arrays(big_s, big_k);
    println!("[FINISH] {answer}");
}
