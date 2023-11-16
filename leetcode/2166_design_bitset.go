type Bitset struct {
	size   int    // assume len(bitmap) * 8 <= size < (len(bitmap) + 1) * 8
	bitmap []byte // bitmap[i] contains 8*i to 8*i+7
	count  int
}

func Constructor(size int) Bitset {
	length := size / 8
	if size%8 != 0 {
		length += 1
	}
	return Bitset{size: size, bitmap: make([]byte, length), count: 0}
}

func (this *Bitset) Fix(idx int) {
	i := idx / 8
	mask := byte(1 << (idx % 8))
	if (this.bitmap[i] & mask) == 0 {
		this.count++
	}
	this.bitmap[i] |= mask
}

func (this *Bitset) Unfix(idx int) {
	i := idx / 8
	mask := byte(1 << (idx % 8))
	if (this.bitmap[i] & mask) != 0 {
		this.count--
	}
	this.bitmap[i] &^= mask
}

func (this *Bitset) Flip() {
	// flip whole bytes
	for i := 0; (i+1)*8 <= this.size; i++ {
		this.bitmap[i] = ^this.bitmap[i]
	}
	lastBits := this.size % 8
	mask := byte(1<<lastBits) - 1
	this.bitmap[len(this.bitmap)-1] ^= mask
	this.count = this.size - this.count
}

func (this *Bitset) All() bool {
	return this.count == this.size
}

func (this *Bitset) One() bool {
	return this.count > 0
}

func (this *Bitset) Count() int {
	return this.count
}

func (this *Bitset) ToString() string {
	sb := strings.Builder{}
	sb.Grow(this.size)
	for i := 0; (i+1)*8 <= this.size; i++ {
		b := this.bitmap[i]
		for j := 7; j >= 0; j-- {
			if (b & 1) != 0 {
				sb.WriteString("1")
			} else {
				sb.WriteString("0")
			}
			b >>= 1
		}
	}
	lastBits := this.size % 8
	if lastBits > 0 {
		b := this.bitmap[len(this.bitmap)-1]
		for lastBits > 0 {
			if (b & 1) != 0 {
				sb.WriteString("1")
			} else {
				sb.WriteString("0")
			}
			b >>= 1
			lastBits--
		}
	}
	return sb.String()
}

/**
 * Your Bitset object will be instantiated and called as such:
 * obj := Constructor(size);
 * obj.Fix(idx);
 * obj.Unfix(idx);
 * obj.Flip();
 * param_4 := obj.All();
 * param_5 := obj.One();
 * param_6 := obj.Count();
 * param_7 := obj.ToString();
 */
