type LetterTable [128]int

func BuildLetterTable(s string) *LetterTable {
	var table LetterTable
	for _, ch := range s {
		table[ch]++
	}
	return &table
}

func (table *LetterTable) Push(ch byte) {
	table[ch]++
}

func (table *LetterTable) Pop(ch byte) {
	if table[ch] <= 0 {
		panic("table not contains " + string(ch))
	}
	table[ch]--
}

func (table *LetterTable) Contains(another *LetterTable) bool {
	for i := 0; i < 128; i++ {
		if table[i] < another[i] {
			return false
		}
	}
	return true
}

func minWindow(s string, t string) string {
	if len(s) < len(t) { // edge case
		return ""
	}
	tablet := BuildLetterTable(t)
	if !BuildLetterTable(s).Contains(tablet) {
		return ""
	}
	// Slide Window
	p, q := 0, 0
	ans := s
	tables := BuildLetterTable("")
	for {
		// extend window to contain t
		for q < len(s) && !tables.Contains(tablet) {
			tables.Push(s[q])
			q++
		}
		// failed to make it
		if !tables.Contains(tablet) {
			break
		}
		// minify the window
		for p < q && tables.Contains(tablet) {
			if q-p < len(ans) {
				ans = s[p:q]
			}
			tables.Pop(s[p])
			p++
		}
	}
	return ans
}