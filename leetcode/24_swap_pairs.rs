impl Solution {
    pub fn swap_pairs(mut head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        if let Some(mut head) = head {
            if let Some(mut next) = head.next {
                let inner = Self::swap_pairs(next.next);
                head.next = inner;
                next.next = Some(head);
                Some(next)
            } else {
                Some(head)
            }
        } else {
            None
        }
    }
}

/* END OF SOLUTION */

struct Solution;

#[derive(PartialEq, Eq, Clone)]
pub struct ListNode {
  pub val: i32,
  pub next: Option<Box<ListNode>>
}

impl ListNode {
  #[inline]
  fn new(val: i32) -> Self {
    ListNode {
      next: None,
      val
    }
  }
}

impl std::fmt::Debug for ListNode {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if let Some(ref next) = self.next {
            write!(f, "{}->{:?}", self.val, next.as_ref())
        } else {
            write!(f, "{}", self.val)
        }
    }
}

fn main() {
    // case 1
    let list = Some(Box::new(ListNode {
        val: 1,
        next: Some(Box::new(ListNode { 
            val: 2, 
            next: Some(Box::new(ListNode { 
                val: 3, 
                next: Some(Box::new(ListNode { val: 4, next: None }))
            }))
        })),
    }));
    eprintln!("{:?}", Solution::swap_pairs(list));
}