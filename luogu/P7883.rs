/// My rust IO library for Online-Judge problems
#[allow(dead_code, unused_macros)]
mod rio {
    use std::{io, str::FromStr};

    /// Read a list of elements with the same type from stdin with space delimeter.
    ///
    /// # Example
    ///
    /// Enter `2 -1 3 -5 4` from stdin, and use the following code to read them:
    ///
    /// ```
    /// let list = rio::read_list::<i32>();
    ///
    /// assert_eq!(list, [2, -1, 3, -5, 4]);
    /// ```
    pub fn read_list<T>() -> Vec<T>
    where
        T: FromStr,
    {
        let mut line = String::new();
        match io::stdin().read_line(&mut line) {
            Ok(bytes) => match bytes {
                0 => vec![],
                _ => line
                    .trim()
                    .split(" ")
                    .map(str::trim)
                    .filter_map(|x| (!x.is_empty()).then(|| x.parse::<T>().ok().unwrap()))
                    .collect::<Vec<T>>(),
            },
            Err(e) => panic!("{}", e),
        }
    }

    /// Read one element from stdin.
    ///
    /// # Returns
    ///
    /// `Some(...)` if something is read, otherwise `None`.
    ///
    /// # Examples
    ///
    /// Input a single `5` to stdin and use the following code to read it:
    ///
    /// ```
    /// let n = rio::read_one::<i32>();
    ///
    /// assert_eq(n, Some(5));
    /// ```
    ///
    /// ---
    ///
    /// Read a series of `u64` numbers from stdin until EOF is reached.
    ///
    /// Input from stdin (Press `Ctrl+D` for EOF):
    ///
    /// ```
    /// 3
    /// 1
    /// 2
    /// 5
    /// 4
    /// ```
    ///
    /// Code:
    ///
    /// ```
    /// let mut nums = Vec::<u64>::new();
    /// while let Some(n) = rio::read_one::<u64>() {
    ///     nums.push(n);
    /// }
    ///
    /// assert_eq!(nums, [3u64, 1u64, 2u64, 5u64, 4u64]);
    /// ```
    pub fn read_one<T>() -> Option<T>
    where
        T: FromStr,
    {
        let mut iter = read_list::<T>().into_iter();
        match iter.next() {
            Some(t) => {
                assert!(iter.next().is_none());
                Some(t)
            }
            None => None,
        }
    }

    /// Read a tuple of given types in one line from stdin with space delimeter.
    ///
    /// # Returns
    ///
    /// `Some(...)` if the input line matches the tuple, `None` if EOF reached.
    ///
    /// # Panics
    ///
    /// There is content in the input line, but the format mismatch.
    ///
    /// # Examples
    ///
    /// Input from stdin:
    ///
    /// ```
    /// 3 -5 aaa
    /// ```
    ///
    /// Code to read them:
    ///
    /// ```
    /// let (a, b, c) = read_tuple!(u64, i32, String).unwrap();
    /// assert_eq!(a, 3u64);
    /// assert_eq!(b, -5);
    /// assert_eq!(c, "aaa");
    /// ```
    #[macro_export]
    macro_rules! read_tuple {
        ( $( $t:ty ),* ) => {
            {
                let mut line = String::new();
                match std::io::stdin().read_line(&mut line) {
                    Ok(bytes) => match bytes {
                        0 => None,
                        _ => {
                            let mut iter = line.trim().split(" ").map(str::trim);
                            let r = (
                                // `$( ... )*` : https://doc.rust-lang.org/book/ch19-06-macros.html
                                $(
                                    iter.next().unwrap().parse::<$t>().ok().unwrap(),
                                )*
                            );
                            assert!(iter.next().is_none());
                            Some(r)
                        }
                    },
                    Err(e) => panic!("{}", e),
                }
            }
        }
    }
}

/* END OF MY RUST IO LIB */

// Reference: https://oi-wiki.org/geometry/nearest-points/

use std::ops::Sub;

#[derive(PartialEq, Eq, Clone, Copy)]
struct Point {
    x: i64,
    y: i64,
}

#[allow(dead_code)]
impl Point {
    fn new(x: i64, y: i64) -> Self {
        Self { x, y }
    }

    fn dist(&self, other: &Point) -> i64 {
        self.x.sub(other.x).pow(2) + self.y.sub(other.y).pow(2)
    }
}

#[allow(dead_code)]
fn nearest_points(points: &[Point]) -> i64 {
    match points.len() {
        1 => unreachable!("Only 1 point!"),
        2 => {
            // points.sort_by(|p1, p2| p1.y.cmp(&p2.y));
            points[0].dist(&points[1])
        }
        3 => {
            // points.sort_by(|p1, p2| p1.y.cmp(&p2.y));
            [(0, 1), (1, 2), (2, 0)]
                .into_iter()
                .map(|(i, j)| points[i].dist(&points[j]))
                .reduce(i64::min)
                .unwrap()
        }
        _ => {
            let mid = points.len() / 2;
            assert!(mid >= 2 && points.len() - mid >= 2);
            let x_mid = points[mid].x;
            let h1 = nearest_points(&points[0..mid]); // nearest dist of left
            let h2 = nearest_points(&points[mid..]); // nearest dist of right
            let h = h1.min(h2);
            let (mut l, mut r) = (mid, mid);
            loop {
                assert!(x_mid.sub(points[l].x).pow(2) <= h);
                if l > 0 && (x_mid.sub(points[l - 1].x).pow(2) <= h) {
                    l -= 1;
                } else {
                    break;
                }
            }
            loop {
                assert!(points[r].x.sub(x_mid).pow(2) <= h);
                if r + 1 < points.len() && points[r + 1].x.sub(x_mid).pow(2) <= h {
                    r += 1;
                } else {
                    break;
                }
            }

            // sort set_b
            let mut set_b = points[l..=r].to_vec();
            set_b.sort_by(|p1, p2| p1.y.cmp(&p2.y));
            let mut ans = h;
            for i in 0..set_b.len() {
                for j in (i + 1)..set_b.len() {
                    if set_b[j].y.sub(set_b[i].y).pow(2) >= ans {
                        break;
                    }
                    ans = ans.min(set_b[i].dist(&set_b[j]));
                }
            }

            ans
        }
    }
}

fn main() {
    while let Some(n) = rio::read_one::<usize>() {
        let mut points = Vec::<Point>::new();
        for _ in 0..n {
            let (x, y) = read_tuple!(i64, i64).unwrap();
            points.push(Point::new(x, y));
        }
        points.sort_by(|p1, p2| p1.x.cmp(&p2.x).then(p1.y.cmp(&p2.y)));
        let ans = nearest_points(&points);
        // println!("{:.4}", (ans as f64).sqrt());
        println!("{}", ans);
    }
}
