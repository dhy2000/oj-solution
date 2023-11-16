const Mod int = 1000000007

func countOrders(n int) int {
	prod := 1
	for i := 1; i <= 2*n; i++ {
		if i%2 == 0 {
			prod *= i / 2
		} else {
			prod *= i
		}
		prod %= Mod
	}
	return prod
}