type LetterTable [26]int

func (letter *LetterTable) Push(c byte) {
	if c >= 26 {
		panic("not a letter")
	}
	letter[c]++
}

func (letter *LetterTable) Pop(c byte) {
	if c >= 26 {
		panic("not a letter")
	}
	if letter[c] <= 0 {
		panic("pop failed")
	}
	letter[c]--
}

func checkInclusion(s1 string, s2 string) bool {
	if len(s1) > len(s2) {
		return false
	}
	var letter1, letter2 LetterTable
	p, q := 0, len(s1)-1
	for i := p; i <= q; i++ {
		letter1.Push(s1[i] - 'a')
		letter2.Push(s2[i] - 'a')
	}
	for q < len(s2) {
		if letter1 == letter2 {
			return true
		}
		letter2.Pop(s2[p] - 'a')
		p++
		q++
		if q >= len(s2) {
			break
		}
		letter2.Push(s2[q] - 'a')
	}
	return false
}