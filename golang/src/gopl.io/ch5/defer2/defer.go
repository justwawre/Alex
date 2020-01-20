// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 151.

// Defer2 demonstrates a deferred call to runtime.Stack during a panic.
package main

import (
	"fmt"
	"os"
	"runtime"
)

//!+
func main() {
	defer printStack()
	f(3)
}

func printStack() {
	var buf [4096]byte
	n := runtime.Stack(buf[:], false) //buf[:]  array->slice
	os.Stdout.Write(buf[:n])
}

//!-

func f(x int) {
	fmt.Printf("f(%d)\n", x)
	_ = 0 / x // panics if x == 0
	defer fmt.Printf("defer %d\n", x)
	f(x - 1)
}
