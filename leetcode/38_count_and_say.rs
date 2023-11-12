impl Solution {
    fn partition(s: String) -> Vec<String> {
        let mut parts: Vec<String> = Vec::new();
        let transactions = s.chars().enumerate()
            .zip(s.chars().enumerate().skip(1).chain(std::iter::once((s.len(), ' '))))
        .filter(|((_, c1), (_, c2))| c1 != c2)
        .map(|((_, _), (i, _))| i).collect::<Vec<usize>>();
        transactions.iter().fold(usize::MIN, |acc, i| {
            parts.push(s.as_str()[acc..*i].to_string());
            *i
        });
        parts
    }

    fn join(parts: Vec<String>) -> String {
        parts.iter().map(|s| s.len().to_string() + s.chars().nth(0).unwrap().to_string().as_str())
            .fold("".to_string(), |acc, s| acc + s.as_str())
    }

    pub fn count_and_say(n: i32) -> String {
        let mut say = "1".to_string();
        for _ in 1..n {
            say = Solution::join(Solution::partition(say));
        }
        say
    }
}

/* Solution end */

struct Solution;

fn main() {
    // Solution::count_and_say(1);
    (1..=5).for_each(|x| println!("{}: {}", x, Solution::count_and_say(x)))
}