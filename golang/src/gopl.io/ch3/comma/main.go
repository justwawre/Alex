// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 73.

// Comma prints its argument numbers with a comma at each power of 1000.
//
// Example:
// 	$ go build gopl.io/ch3/comma
//	$ ./comma 1 12 123 1234 1234567890
// 	1
// 	12
// 	123
// 	1,234
// 	1,234,567,890
//
package main

import (
	"bytes"
	"fmt"
	"os"
	"strings"
)

func main() {
	for i := 1; i < len(os.Args); i++ {
		fmt.Printf("  %s\n", comma(os.Args[i]))
	}
}

//!+
// comma inserts commas in a non-negative decimal integer string.
func comma(s string) string {
	var buf bytes.Buffer
	var ll, dot int
	var sign byte
	var ss, si, sf string

	if s[0] == '+' || s[0] == '-' {
		sign = s[0]
		ss = s[1:]

	} else {
		ss = s
	}
	if dot = strings.Index(ss, "."); dot >= 0 {
		si = ss[:dot]
		sf = ss[dot+1:]
	} else {
		si = ss
	}
	if len(si) <= 3 && len(sf) <= 3 {
		return s
	}
	ll = len(si) % 3
	buf.WriteByte(sign)
	buf.WriteString(si[:ll]) //fmt.Fprintf(&buf, "%d", v)

	for i := 0; i < (len(si)-ll)/3; i++ {
		buf.WriteByte(',')
		buf.WriteString(si[ll+3*i : ll+3*i+3]) //最后一个index 不像python 需要特殊处理
	}
	if sf != "" {
		buf.WriteByte('.')
		ll = len(sf) % 3
		for i := 0; i < len(sf)/3; i++ {
			buf.WriteString(sf[3*i : 3*i+3]) //最后一个index 不像python 需要特殊处理
			if ll > 0 {
				buf.WriteByte(',')
			}

		}
		if ll > 0 {
			buf.WriteString(sf[len(sf)-ll:])
		}
	}
	return buf.String()
}

//!-
