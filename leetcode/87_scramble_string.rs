impl Solution {
    pub fn is_scramble(s1: String, s2: String) -> bool {
        assert_eq!(s1.len(), s2.len());
        let len = s1.len();
        // dp[l][i][j]: is_scramble(s1[i +: l], s2[j +: l])
        let mut dp = vec![vec![vec![false; len]; len]; len + 1];

        for (i, c1) in s1.chars().enumerate() {
            for (j, c2) in s2.chars().enumerate() {
                dp[1][i][j] = c1 == c2;
            }
        }

        for l in 2..=len {
            for i in 0..(len + 1 - l) {
                for j in 0..(len + 1 - l) {
                    dp[l][i][j] = (1..l)
                        .map(|nl| {
                            (dp[nl][i][j] && dp[l - nl][i + nl][j + nl])
                                || (dp[nl][i][j + l - nl] && dp[l - nl][i + nl][j])
                        })
                        .fold(false, |acc, t| acc || t);
                }
            }
        }

        dp[len][0][0]
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    let testcases = vec![
        (("great", "rgeat"), true),
        (("abcde", "caebd"), false),
        (("a", "a"), true),
        (("abcde", "cabed"), true),
    ];

    for (i, &((s1, s2), expect)) in testcases.iter().enumerate() {
        let answer = Solution::is_scramble(s1.to_string(), s2.to_string());
        assert_eq!(answer, expect);
        println!("[PASSED] {}", i);
    }
}
