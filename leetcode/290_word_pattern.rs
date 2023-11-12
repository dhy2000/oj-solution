struct Solution {}

/* Solution begin */
use std::collections::HashMap;
use std::collections::hash_map::Entry::*;

macro_rules! fail_if_false {
    ($l: expr) => {
        if !($l) {
            return false
        }
    };
}

impl Solution {
    pub fn word_pattern(pattern: String, s: String) -> bool {
        let words = s.split(" ").collect::<Vec<&str>>();
        if words.len() != pattern.len() {
            return false;
        }
        let mut pattern_to_word: HashMap<char, &str> = HashMap::new();
        let mut word_to_pattern: HashMap<&str, char> = HashMap::new();
        for i in 0..words.len() {
            let pattern = pattern.chars().nth(i).unwrap();
            let word = words[i];
            match (pattern_to_word.entry(pattern), word_to_pattern.entry(word)) {
                (Occupied(p2w), Occupied(w2p)) => {
                    fail_if_false!(*p2w.get() == *w2p.key() && *p2w.key() == *w2p.get());
                },
                (Occupied(_), Vacant(_)) => {
                    return false;
                },
                (Vacant(_), Occupied(_)) => {
                    return false;
                },
                (Vacant(p2w), Vacant(w2p)) => {
                    p2w.insert(word);
                    w2p.insert(pattern);
                },
            }
        }
        true
    }
}
/* Solution end */

fn main() {
    // 'read_input: loop {
    //     let mut input = String::new();
    //     match io::stdin().read_line(&mut input) {
    //         Err(e) => panic!("{}", e),
    //         Ok(bytes) => {
    //             if bytes == 0 {
    //                 break 'read_input;
    //             }
    //             if let Some((pattern, s)) = input.split_once(" ") {
    //                 println!("{}", Solution::word_pattern(pattern.trim().to_string(), s.trim().to_string()));
    //             } else {
    //                 println!("invalid input!");
    //             }
    //         }
    //     }
    // }
    println!("{}", Solution::word_pattern("abba".to_string(), "dog cat cat dog".to_string()));
    println!("{}", Solution::word_pattern("abba".to_string(), "dog cat cat fish".to_string()));
    println!("{}", Solution::word_pattern("aaaa".to_string(), "dog cat cat dog".to_string()));
    println!("{}", Solution::word_pattern("abba".to_string(), "dog dog dog dog".to_string()));
    println!("{}", Solution::word_pattern("abc".to_string(), "dog cat dog".to_string()));
}

/*
// A sample 0ms submission

use std::collections::HashMap;

impl Solution {
    pub fn word_pattern(pattern: String, s: String) -> bool {
        let mut map_s2i: HashMap<&str, usize> = HashMap::new();
        let mut map_c2i: HashMap<char, usize> = HashMap::new();
        let arr_patterns: Vec<_> = pattern.chars().collect();
        let arr_strings: Vec<_> = s.split(" ").collect();

        if arr_strings.len() != arr_patterns.len() {
            return false;
        }

        for (i, str) in arr_strings.into_iter().enumerate() {
            let c = arr_patterns[i];

            match (map_s2i.get(str), map_c2i.get(&c)) {
                (Some(si), Some(ci)) => {
                    if si != ci {
                        return false;
                    }
                }
                (Some(si), None) => return false,
                (None, Some(ci)) => return false,
                (None, None) => {
                    map_s2i.insert(str, i);
                    map_c2i.insert(c, i);
                }
            }
        }
        true
    }
}

*/