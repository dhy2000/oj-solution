fn longest_common_subsequence<T>(input1: &[T], input2: &[T]) -> usize
where T: Eq + PartialEq
{
    let len1 = input1.len();
    let len2 = input2.len();
    let mut dp = vec![vec![0usize; len2]; len1];

    for (i, c1) in input1.iter().enumerate() {
        for (j, c2) in input2.iter().enumerate() {
            let mut ans = 0;
            if c1.eq(c2) {
                if i > 0 && j > 0 {
                    ans = ans.max(dp[i - 1][j - 1] + 1);
                } else {
                    ans = ans.max(1);
                }
            }
            if i > 0 {
                ans = ans.max(dp[i - 1][j]);
            }
            if j > 0 {
                ans = ans.max(dp[i][j - 1]);
            }
            dp[i][j] = ans;
        }
    }

    dp[len1 - 1][len2 - 1]
}


impl Solution {
    pub fn min_insertions(s: String) -> i32 {
        // answer = len(s) - len(longest palindrome substring)
        // LCS(s, s.rev)

        let mut vr = s.as_bytes().to_vec();
        vr.reverse();

        let lcs = longest_common_subsequence(s.as_bytes(), &vr);

        assert!(s.len() >= lcs);
        
        (s.len() - lcs) as i32
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    let testcases = vec![
        ("zzazz", 0),
        ("mbadm", 2),
        ("leetcode", 5),
    ];

    for &(s, expect) in testcases.iter() {
        let answer = Solution::min_insertions(s.to_string());
        assert_eq!(answer, expect);
        println!("[PASSED] '{s}': {answer}");
    }
}