use std::cell::RefCell;
use std::ops::{AddAssign, Sub};

struct BrowserHistory {
    sites: RefCell<Vec<String>>,
    pos: RefCell<usize>,
}

/** 
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl BrowserHistory {

    fn new(homepage: String) -> Self {
        Self { sites: RefCell::new(vec![homepage]), pos: RefCell::new(0usize) }
    }
    
    fn visit(&self, url: String) {
        self.pos.borrow_mut().add_assign(1);
        self.sites.borrow_mut().splice(*self.pos.borrow().., std::iter::once(url));
        assert_eq!(*self.pos.borrow() + 1, self.sites.borrow().len());
    }
    
    fn back(&self, steps: i32) -> String {
        let target = self.pos.borrow().saturating_sub(steps as usize);
        *self.pos.borrow_mut() = target;
        self.sites.borrow()
            .get(*self.pos.borrow() as usize).unwrap().clone()
        
    }
    
    fn forward(&self, steps: i32) -> String {
        let steps = steps.min(self.sites.borrow().len().sub(*self.pos.borrow() + 1) as i32);
        self.pos.borrow_mut().add_assign(steps as usize);
        self.sites.borrow()
            .get(*self.pos.borrow() as usize).unwrap().clone()
    }
}

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * let obj = BrowserHistory::new(homepage);
 * obj.visit(url);
 * let ret_2: String = obj.back(steps);
 * let ret_3: String = obj.forward(steps);
 */


/* ------ END OF SOLUTION ------ */

fn main() {
    let history = BrowserHistory::new("leetcode.com".to_string());
    history.visit("google.com".to_string());
    history.visit("facebook.com".to_string());
    history.visit("youtube.com".to_string());
    println!("{}", history.back(1));
    println!("{}", history.back(1));
    println!("{}", history.forward(1));
    history.visit("linkedin.com".to_string());
    println!("{}", history.forward(2));
    println!("{}", history.back(2));
    println!("{}", history.back(7));
}