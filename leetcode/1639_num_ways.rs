use std::fmt;

const MOD: i32 = 1000000007;

macro_rules! mult_mod {
    ($t1:expr,$t2:expr) => {
        ((($t1 as i64) * ($t2 as i64)) % (MOD as i64)) as i32
    };
}

macro_rules! add_mod {
    ($t1:expr,$t2:expr) => {
        ($t1 + $t2) % MOD
    };
}

#[derive(Clone)]
struct FrequencyTable {
    frequency: Vec<usize>,
}

#[allow(dead_code)]
impl FrequencyTable {
    fn new() -> Self {
        Self {
            frequency: vec![0; 26],
        }
    }

    fn add_letter(&mut self, letter: char) {
        assert!(letter >= 'a' && letter <= 'z');
        let idx = (letter as u8 - 'a' as u8) as usize;
        assert!(idx < self.frequency.len());

        self.frequency[idx] += 1;
    }

    fn get(&self, letter: char) -> usize {
        assert!(letter >= 'a' && letter <= 'z');
        let idx = (letter as u8 - 'a' as u8) as usize;
        assert!(idx < self.frequency.len());

        self.frequency[idx]
    }
}

impl ToString for FrequencyTable {
    fn to_string(&self) -> String {
        let content = self.frequency
            .iter()
            .enumerate()
            .filter(|(_, &n)| n > 0)
            .map(|(i, &n)| format!("{}: {}", (i as u8 + 'a' as u8) as char, n))
            .reduce(|acc, t| acc + ", " + t.as_str())
            .unwrap_or(String::new());
        format!("{{{}}}", content)
    }
}

impl fmt::Debug for FrequencyTable {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.to_string())
    }
}

#[allow(unused_variables)]
impl Solution {
    pub fn num_ways(words: Vec<String>, target: String) -> i32 {
        /*
           acca
           bbbb
           caca

           0: {a: 1, b: 1, c: 1}
           1: {a: 1, b: 1, c: 1}
           2: {a: 0, b: 1, c: 2}
           3: {a: 2, b: 1, c: 0}

           dp[i][j]: target first i letters, words index j
           init: dp[-1][-1] = 1
           dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1] * freq_pos[j][target[i]]

        */
        let n = words.len();
        assert!(n > 0);
        let word_len = words[0].len();
        assert!(words.iter().all(|x| x.len() == word_len));

        let mut freq_pos = vec![FrequencyTable::new(); word_len];
        for word in words.iter() {
            for (i, c) in word.chars().enumerate() {
                freq_pos[i].add_letter(c);
            }
        }

        let mut dp = vec![vec![0; word_len]; target.len()];

        for (i, c) in target.chars().enumerate() {
            for j in 0..word_len {
                let v1 = if j >= 1 { dp[i][j - 1] } else { 0 };
                let v2 = mult_mod!((if i == 0 { 1 } else if i >= 1 && j >= 1 { dp[i - 1][j - 1] } else { 0 }), freq_pos[j].get(c) as i32);

                dp[i][j] = add_mod!(v1, v2);
                
            }
        }

        dp[target.len() - 1][word_len - 1]
    }
}

/* END OF SOLUTION */

struct Solution;

fn main() {
    assert_eq!(
        Solution::num_ways(
            vec![
                String::from("acca"),
                String::from("bbbb"),
                String::from("caca"),
            ],
            String::from("aba")
        ),
        6
    );
    assert_eq!(
        Solution::num_ways(
            vec![String::from("abba"), String::from("baab"),],
            String::from("bab")
        ),
        4
    );
}
