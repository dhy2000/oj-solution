impl Solution {
    pub fn roman_to_int(s: String) -> i32 {
        let mut num: i32 = 0;
        let s = s.as_str();
        let mut pos = 0;
        while pos < s.len() {
            let (n, p) =
            match s[pos.into()..s.len()].chars().collect::<Vec<char>>()[..] {
                ['M', ..] => (1000, 1),
                ['C', 'M', ..] => (900, 2),
                ['D', ..] => (500, 1),
                ['C', 'D', ..] => (400, 2),
                ['C', ..] => (100, 1),
                ['X', 'C', ..] => (90, 2),
                ['L', ..] => (50, 1),
                ['X', 'L', ..] => (40, 2),
                ['X', ..] => (10, 1),
                ['I', 'X', ..] => (9, 2),
                ['V', ..] => (5, 1), 
                ['I', 'V', ..] => (4, 2),
                ['I', ..] =>  (1, 1),
                _ => (0, 1)
            };
            num += n;
            pos += p;
        }
        num
    }
}

/* Solution end */

struct Solution {}

fn main() {
    println!("{}", Solution::roman_to_int("III".to_string()));
    println!("{}", Solution::roman_to_int("LVIII".to_string()));
    println!("{}", Solution::roman_to_int("MCMXCIV".to_string()));
}


// impl Solution {
//     pub fn roman_to_int(s: String) -> i32 {
//         s.chars()
//             .zip(s.chars().skip(1).chain(std::iter::once(' ')))
//             .fold(0, |acc, t| match t {
//                 ('I', 'V' | 'X') => acc - 1,
//                 ('I', _) => acc + 1,
//                 ('V', _) => acc + 5,
//                 ('X', 'L' | 'C') => acc - 10,
//                 ('X', _) => acc + 10,
//                 ('L', _) => acc + 50,
//                 ('C', 'D' | 'M') => acc - 100,
//                 ('C', _) => acc + 100,
//                 ('D', _) => acc + 500,
//                 ('M', _) => acc + 1000,
//                 _ => panic!("invalid input string"),
//             })
//     }
// }
