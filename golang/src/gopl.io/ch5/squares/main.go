// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 135.

// The squares program demonstrates a function value with state.
package main

import "fmt"

//!+
// squares returns a function that returns
// the next square number each time it is called.
func squares() func() int {
	var x int
	return func() int {
		x++
		return x * x
	}
}

var sqrs []func()

func main() {
	f := squares()
	fmt.Println(f()) // "1"
	fmt.Println(f()) // "4"

	var sqrs []func() int
	for i := 10; i < 13; i++ {
		i := i
		f = func() int {
			return i * i
		}
		sqrs = append(sqrs, f)
	}
	for _, f := range sqrs {
		fmt.Println(f())
	}

}

//!-
