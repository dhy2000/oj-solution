func countEven(num int) int {
	count := 0
	for i := 1; i <= num; i++ {
		// sum digits of num
		s := 0
		n := i
		for n > 0 {
			s += n % 10
			n /= 10
		}
		if s%2 == 0 {
			count++
		}
	}
	return count
}