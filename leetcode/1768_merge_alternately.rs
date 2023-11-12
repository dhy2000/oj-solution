impl Solution {
    pub fn merge_alternately(word1: String, word2: String) -> String {
        let (shared_len, remain): (usize, &str) = if word1.len() == word2.len() {
            (word1.len(), "")
        } else if word1.len() < word2.len() {
            (word1.len(), &word2.as_str()[word1.len()..word2.len()])
        } else {
            (word2.len(), &word1.as_str()[word2.len()..word1.len()])
        };

        word1.as_str()[0..shared_len]
            .to_string()
            .chars()
            .zip(word2.as_str()[0..shared_len].to_string().chars())
            .map(|(c1, c2)| c1.to_string() + c2.to_string().as_str())
            .reduce(|acc, t| acc + t.as_str())
            .unwrap_or(String::new())
            + remain
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    println!(
        "{}",
        Solution::merge_alternately("abc".to_string(), "pqr".to_string())
    );
    println!(
        "{}",
        Solution::merge_alternately("ab".to_string(), "pqrs".to_string())
    );
    println!(
        "{}",
        Solution::merge_alternately("abcd".to_string(), "pq".to_string())
    );
}
