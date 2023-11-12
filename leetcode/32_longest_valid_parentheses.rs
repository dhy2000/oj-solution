use std::collections::VecDeque;

#[allow(dead_code)]
struct ILinkNode<T> {
    pub val: T,
    pub left: Option<usize>,
    pub right: Option<usize>,
}

#[allow(dead_code)]
struct ILinkList<T> {
    pub head: Option<usize>,
    pub tail: Option<usize>,
    pub vec: Vec<ILinkNode<T>>
}

#[allow(dead_code, unused_variables)]
impl<T> ILinkList<T> {
    #[inline]
    pub fn new() -> Self {
        Self { head: None, tail: None, vec: Vec::new() }
    }

    #[inline]
    pub fn add_node(&mut self, val: T) -> usize {
        if let Some(head) = self.head {
            assert!(self.tail.is_some());
            self.vec.push(ILinkNode { val, left: self.tail, right: None });
            let tail = self.vec.len().saturating_sub(1);
            self.set_right(self.tail.unwrap(), Some(tail));
            self.tail = Some(tail);
        } else {
            assert!(self.tail.is_none());
            self.vec.push(ILinkNode { val, left: None, right: None });
            self.head = Some(self.vec.len() - 1);
            self.tail = self.head;
        }
        self.tail.unwrap()
    }

    #[inline]
    pub fn get_val(&self, key: usize) -> &T {
        assert!(key < self.vec.len());
        &self.vec[key].val
    }

    #[inline]
    pub fn get_left(&self, key: usize) -> Option<usize> {
        self.vec[key].left
    }

    #[inline]
    pub fn get_right(&self, key: usize) -> Option<usize> {
        self.vec[key].right
    }

    #[inline]
    pub fn get_left_val(&self, key: usize) -> Option<&T> {
        if let Some(left) = self.get_left(key) {
            Some(self.get_val(left))
        } else {
            None
        }
    }

    #[inline]
    pub fn get_right_val(&self, key: usize) -> Option<&T> {
        if let Some(right) = self.get_right(key) {
            Some(self.get_val(right))
        } else {
            None
        }
    }

    #[inline]
    fn set_left(&mut self, key: usize, left: Option<usize>) {
        self.vec[key].left = left;
    }

    #[inline]
    fn set_right(&mut self, key: usize, right: Option<usize>) {
        self.vec[key].right = right;
    }

    #[inline]
    pub fn remove(&mut self, key: usize) {
        if let Some(left) = self.get_left(key) {
            assert!(self.head.is_some() && self.head.unwrap() != key);
            self.set_right(left, self.get_right(key));
        } else {
            assert!(self.head.is_some() && self.head.unwrap() == key);
            self.head = self.get_right(key);
        }
        if let Some(right) = self.get_right(key) {
            assert!(self.tail.is_some() && self.tail.unwrap() != key);
            self.set_left(right, self.get_left(key));
        } else {
            assert!(self.tail.is_some() && self.tail.unwrap() == key);
            self.tail = self.get_left(key);
        }
    }

    pub fn iter(&self) -> ILinkListIterator<'_, T> {
        ILinkListIterator::new(&self)
    }
}

impl From<&str> for ILinkList<char> {
    fn from(s: &str) -> Self {
        let mut list = Self::new();
        for c in s.chars() {
            list.add_node(c);
        }
        list
    }
}


struct ILinkListIterator<'a, T> {
    list: &'a ILinkList<T>,
    cur: Option<usize>,
}

impl<'a, T> ILinkListIterator<'a, T> {
    fn new(list: &'a ILinkList<T>) -> Self {
        Self { list, cur: None }
    }
}

impl<T> Iterator for ILinkListIterator<'_, T> {
    type Item = usize;

    fn next(&mut self) -> Option<Self::Item> {
        if let Some(cur) = self.cur {
            self.cur = self.list.get_right(cur);
        } else {
            self.cur = self.list.head;
        }
        self.cur
    }
}

#[allow(dead_code, unused_variables)]
impl Solution {
    pub fn longest_valid_parentheses(s: String) -> i32 {
        let mut list = ILinkList::<char>::from(s.as_str());
        let mut q = VecDeque::<usize>::new(); // position of left parenthesis
        for left in list.iter() {
            if let Some(right) = list.get_right(left) {
                if *list.get_val(left) == '(' && *list.get_val(right) == ')' {
                    q.push_back(left);
                }
            }
        }

        while let Some(left) = q.pop_front() {
            let right = list.get_right(left).unwrap();
            assert!(*list.get_val(left) == '(' && *list.get_val(right) == ')');
            
            let next_left = list.get_left(left);
            let next_right = list.get_right(right);
            list.remove(left);
            list.remove(right);

            match (next_left, next_right) {
                (Some(left), Some(right)) => {
                    if *list.get_val(left) == '(' && *list.get_val(right) == ')' {
                        q.push_back(left);
                    }
                },
                (_, _) => {},
            }
        }
        
        let mut bitmap = vec![true; s.len()];
        for pos in list.iter() {
            bitmap[pos] = false;
        }
        
        let mut length = 0;
        let mut count = 0;

        for b in bitmap.iter() {
            if *b {
                count += 1;
                length = length.max(count);
            } else {
                count = 0;
            }
        }

        length
    }
}

/* END OF SOLUTION */

use std::fmt;

impl<T> fmt::Debug for ILinkList<T> 
where T: fmt::Display
{
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let s = self.iter().map(|x| format!("{}", self.get_val(x)))
            .fold(String::new(), |acc, t| acc + t.as_str());
        write!(f, "{s}")
    }
}


struct Solution;

#[allow(unused_variables)]
fn main() {
    let testcases = vec![
        ("()", 2),
        ("(()", 2),
        (")()())", 4),
        ("", 0),
        ("()(()", 2),
        ("()(())", 6),
        ("(()(((()", 2),
        ("(()())", 6),
    ];

    for &(input, _) in testcases.iter() {
        assert_eq!(format!("{:?}", ILinkList::<char>::from(input)), input);
    }

    for &(input, answer) in testcases.iter() {
        println!("'{}': {}", input, Solution::longest_valid_parentheses(input.to_string()));
        assert_eq!(Solution::longest_valid_parentheses(input.to_string()), answer);
    }
}
