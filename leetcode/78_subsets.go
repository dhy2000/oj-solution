func subsets(nums []int) [][]int {
	answer := make([][]int, 0)
	fullMask := (1 << len(nums)) - 1
	for mask := 0; mask <= fullMask; mask++ {
		set := make([]int, 0)
		for i := 0; i < len(nums); i++ {
			if mask&(1<<i) != 0 {
				set = append(set, nums[i])
			}
		}
		answer = append(answer, set)
	}
	return answer
}