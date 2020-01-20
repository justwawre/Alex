package geometry

import "fmt"

func Example_one() {
	p := Point{1, 1}
	q := Point{4, 5}
	fmt.Println(p.Distance(q))
	// Output: 6
}
