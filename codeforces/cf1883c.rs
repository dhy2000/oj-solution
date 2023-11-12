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

macro_rules! map_to_mod {
    ($v:expr,$m:expr) => {
        ($v).iter().map(|x| match *x % ($m) { 0 => 0, m @ _ => ($m) - m})  
    }
}



fn main() {
    let t = rio::read_one::<i32>().unwrap();
    for _ in 0..t {
        let (n, k) = read_tuple!(i32, i32).unwrap();
        let a = rio::read_list::<i32>();
        assert_eq!(a.len(), n as usize);
        let ans = match k {
            2 => map_to_mod!(a, 2).reduce(i32::min).unwrap(),
            3 => map_to_mod!(a, 3).reduce(i32::min).unwrap(),
            5 => map_to_mod!(a, 5).reduce(i32::min).unwrap(),
            4 => {
                // only one odd: +1 or +3
                // all odds: +1 (mod=3) or +2 (two even)
                // only one even: +0 or +2 or +1 (use odd)
                // multiple evens: +0
                let mut mods = [0; 4];
                for n in a.iter() {
                    mods[(n % 4) as usize] += 1;
                }
                if mods[0] > 0 || mods[2] >= 2 {
                    0
                } else if mods[3] > 0 || mods[2] == 1 {
                    1
                } else if (mods[1] + mods[3]) >= 2 {
                    2
                } else {
                    3
                }
            }
            _ => unreachable!("k should in range 2..=5")
        };
        println!("{}", ans);
    }
}
