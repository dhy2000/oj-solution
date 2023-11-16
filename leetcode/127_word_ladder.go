func isNext(beginWord string, endWord string) bool {
	length := len(beginWord)
	count := 0
	for i := 0; i < length; i++ {
		if beginWord[i] != endWord[i] {
			count++
		}
	}
	return count == 1
}

func ladderLength(beginWord string, endWord string, wordList []string) int {
	distance := make(map[string]int)  // bfs
	edge := make(map[string][]string) // build graph
	// step 1: build undirected graph
	for i := range wordList {
		edge[wordList[i]] = make([]string, 0)
		for j := range wordList {
			if isNext(wordList[i], wordList[j]) {
				edge[wordList[i]] = append(edge[wordList[i]], wordList[j])
			}
		}
	}
	if _, has := edge[endWord]; !has {
		return 0
	}
	if _, has := edge[beginWord]; !has {
		edge[beginWord] = make([]string, 0)
		for j := range wordList {
			if isNext(beginWord, wordList[j]) {
				edge[beginWord] = append(edge[beginWord], wordList[j])
			}
		}
	}
	// step 2: breadth-first-search from beginWord
	distance[beginWord] = 1
	queue := list.New()
	queue.PushBack(beginWord)
	for queue.Len() > 0 {
		// pop element from queue
		elem := queue.Front()
		word := elem.Value.(string)
		queue.Remove(elem)
		for _, another := range edge[word] {
			if _, has := distance[another]; !has {
				distance[another] = distance[word] + 1
				queue.PushBack(another)
			}
		}
	}
	return distance[endWord]
}