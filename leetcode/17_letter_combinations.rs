impl Solution {
    pub fn letter_combinations(digits: String) -> Vec<String> {
        // digit -> choices
        // fold by cartesian product
        if digits.is_empty() {
            return vec![];
        }
        digits.chars().map(|c| match c {
            '2' => vec!["a", "b", "c"],
            '3' => vec!["d", "e", "f"],
            '4' => vec!["g", "h", "i"],
            '5' => vec!["j", "k", "l"],
            '6' => vec!["m", "n", "o"],
            '7' => vec!["p", "q", "r", "s"],
            '8' => vec!["t", "u", "v"],
            '9' => vec!["w", "x", "y", "z"],
            _ => vec![]
        }).fold(vec!["".to_string()], |acc, l| {
            let mut v: Vec<String> = Vec::new();
            for lhs in acc.iter() {
                for rhs in l.iter() {
                    v.push(lhs.to_owned() + *rhs);
                }
            }
            v
        })
    }
}

struct Solution;

fn main() {
    println!("{:?}", Solution::letter_combinations("23".to_string()));
    println!("{:?}", Solution::letter_combinations("".to_string()));
}