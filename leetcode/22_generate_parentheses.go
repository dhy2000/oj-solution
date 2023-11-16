func generateParenthesis(n int) []string {
	if n == 0 {
		return []string{""}
	}
	parenthesis := make([]string, 0)
	for left := 0; left < n; left++ {
		right := n - 1 - left
		partLeft := generateParenthesis(left)
		partRight := generateParenthesis(right)
		// cartesian product
		p := make([]string, 0)
		for _, l := range partLeft {
			for _, r := range partRight {
				p = append(p, "("+l+")"+r)
			}
		}
		parenthesis = append(parenthesis, p...)
	}
	return parenthesis
}