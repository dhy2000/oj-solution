impl Solution {
    pub fn is_valid(s: String) -> bool {
        let mut stack = Vec::<char>::new();
        for c in s.chars() {
            match c {
                '(' | '{' | '[' => {
                    stack.push(c);
                },
                ')' | '}' | ']' => {
                    if stack.is_empty() {
                        return false;
                    }
                    let top = stack[stack.len() - 1];
                    if (c == ')' && top == '(') ||
                        (c == '}' && top == '{') ||
                        (c == ']' && top == '[')
                    {
                        stack.resize(stack.len() - 1, '-');
                    } else { return false; }
                },
                _ => {}
            }
        }
        stack.is_empty()
    }
}