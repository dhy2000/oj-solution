func gcd(x int, y int) int {
	if x < y {
		x, y = y, x
	}
	for x%y != 0 {
		x, y = y, x%y
	}
	return y
}

var primeTable []int

// genPrimeTable: Euler's linear sieve
func genPrimeTable(lim int) (check map[int]bool, table []int) {
	check = make(map[int]bool)
	table = make([]int, 0)
	check[0], check[1] = false, false
	for i := 2; i <= lim; i++ {
		if _, has := check[i]; !has {
			check[i] = true
			table = append(table, i)
		}
		for _, p := range table {
			if i*p > lim {
				break
			}
			check[i*p] = false
			if i%p == 0 {
				break
			}
		}
	}
	return
}

// factor 对 num 分解质因子
// 返回 map, key 是质因子, value 是这个质因子的次数
func factor(num int) (factors map[int]int) {
	factors = make(map[int]int)
	for _, p := range primeTable {
		if num == 1 {
			break
		}
		if num%p == 0 {
			factors[p] = 0
			for num%p == 0 {
				num /= p
				factors[p]++
			}
		}
	}
	return
}

func iterFactor(factors *map[int]int, primes *[]int, base int, index int, action func(n int)) {
	// primes is keys of factors
	if index >= len(*primes) {
		action(base)
		return
	}
	p := (*primes)[index]
	b := 1
	for i := 0; i <= (*factors)[p]; i++ {
		iterFactor(factors, primes, base*b, index+1, action)
		b *= p
	}
}

func countPairs(nums []int, k int) int64 {
	lim := 100000
	_, primeTable = genPrimeTable(lim)
	offer := make([]int, k+1)
	for i, n := range nums {
		// iterate all n's factor
		nums[i] = gcd(nums[i], k)
		n = nums[i]
		factors := factor(n)
		primes := make([]int, 0)
		for p := range factors {
			primes = append(primes, p)
		}
		iterFactor(&factors, &primes, 1, 0, func(num int) {
			offer[num]++
		})
	}
	count := int64(0)
	for _, n := range nums {
		g := gcd(n, k)
		need := k / g
		count += int64(offer[need])
		if n%need == 0 {
			count--
		}
	}
	return count / 2
}