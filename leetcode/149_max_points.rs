#[allow(dead_code, unused_variables)]
pub struct Solution {}

/* Solution begin */
use std::fmt;
use std::collections::HashMap;

fn gcd(a: i32, b: i32) -> i32 {
    match b {
        0 => a,
        _ => gcd(b, a % b)
    }
}

#[derive(Hash, PartialEq, Eq, Clone, Copy)]
struct Point {
    x: i32, y: i32
}

impl fmt::Display for Point {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

impl From<&Vec<i32>> for Point {
    fn from(v: &Vec<i32>) -> Self {
        assert!(v.len() >= 2);
        Self { x: v[0], y: v[1] }
    }
}

#[derive(Hash, PartialEq, Eq, Clone, Copy)]
struct StraightLine {
    a: i32, b: i32, c: i32
}

impl fmt::Display for StraightLine {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "({}, {}, {})", self.a, self.b, self.c)
    }
}

impl StraightLine {
    fn new(ends: (Point, Point)) -> Self {
        if ends.0.x == ends.1.x {
            // (x1 == x2) -> x - x1 = 0
            Self {a: 1, b: 0, c: -ends.0.x}
        } else if ends.0.y == ends.1.y {
            // (y1 == y2) -> y - y1 = 0
            Self {a: 0, b: 1, c: -ends.0.y}
        } else {
            // (x - x1) / (x2 - x1) = (y - y1) / (y2 - y1)
            // (y2 - y1)x - (x2 - x1)y + (x2 - x1)y1 - (y2 - y1)x1 = 0
            let a = ends.1.y - ends.0.y;
            let b = ends.0.x - ends.1.x;
            let c = (ends.1.x - ends.0.x) * ends.0.y + (ends.0.y - ends.1.y) * ends.0.x;
            // println!("{}, {}, {}", a, b, c);
            assert_ne!(a, 0);
            assert_ne!(b, 0);
            let g = gcd(a.abs(), b.abs());
            let a = a / g;
            let b = b / g;
            let c = c / g;
            if a < 0 {
                Self {a: -a, b: -b, c: -c}
            } else {
                Self {a, b, c}
            }
        }
    }
}

impl Solution {
    pub fn max_points(points: Vec<Vec<i32>>) -> i32 {
        let mut ans = 0;
        let points = points.iter().map(|v| Point::from(v)).collect::<Vec<Point>>();
        if points.len() == 1 {
            return 1;
        }
        for i in 0..points.len() {
            let mut line_count: HashMap<StraightLine, i32> = HashMap::new();
            for j in (i+1)..points.len() {
                let l = StraightLine::new((points[i], points[j]));
                // println!("{}, {} => {}", points[i], points[j], l);
                line_count.entry(l).and_modify(|v| *v += 1).or_insert(2);
            }
            // Debug
            // line_count.iter().for_each(|(k, v)| println!("{}: {}", *k, *v));
            if let Some(x) = line_count.values().max() {
                if *x > ans {
                    ans = *x
                }
            }
        }
        ans
    }
}

/* Solution end */

fn main() {
    let points = vec![
        vec![1, 1], vec![2, 2], vec![3, 3]
    ];
    println!("{}", Solution::max_points(points));
    let points = vec![
        vec![1, 1], vec![3, 2], vec![5, 3], vec![4, 1], vec![2, 3], vec![1, 4]
    ];
    println!("{}", Solution::max_points(points));
    let points = vec![
        vec![1, 1]
    ];
    println!("{}", Solution::max_points(points));
}
