func isValid(s string) bool {
	stack := make([]int32, 0, len(s))
	for _, ch := range s {
		switch ch {
		case '(', '[', '{':
			stack = append(stack, ch)
		case ')', ']', '}':
			if len(stack) == 0 {
				return false
			}
			left := stack[len(stack)-1]
			if (left == '(' && ch == ')') || (left == '[' && ch == ']') || (left == '{' && ch == '}') {
				stack = stack[:len(stack)-1]
			} else {
				return false
			}
		}
	}
	return len(stack) == 0
}