func repeatLimitedString(s string, repeatLimit int) string {
	var letterCount [26]int
	for _, c := range s {
		letterCount[c-'a']++
	}
	builder := strings.Builder{}
	c := 'z'
	for builder.Len() < len(s) {
		// find the largest letter
		for ; c >= 'a'; c-- {
			if letterCount[c-'a'] > 0 {
				break
			}
		}
		// fetch and build
		var count int
		if letterCount[c-'a'] <= repeatLimit {
			count = letterCount[c-'a']
		} else {
			count = repeatLimit
		}
		for i := 0; i < count; i++ {
			builder.WriteByte(byte(c))
		}
		letterCount[c-'a'] -= count
		if letterCount[c-'a'] > 0 { // over repeat limit
			// fetch another one
			for c--; c >= 'a'; c-- {
				if letterCount[c-'a'] > 0 {
					break
				}
			}
			if c < 'a' {
				break
			}
			letterCount[c-'a']--
			builder.WriteByte(byte(c))
			c = 'z'
		}
	}
	return builder.String()
}