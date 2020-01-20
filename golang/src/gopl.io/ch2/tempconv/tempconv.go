// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

//!+

// Package tempconv performs Celsius and Fahrenheit conversions.
package tempconv

import "fmt"

//Celsius  c
type Celsius float64

//Fahrenheit f
type Fahrenheit float64

//Kelvin  k
type Kelvin float64

const (
	//AbsoluteZeroC  k
	AbsoluteZeroC Celsius = -273.15
	//FreezingC      freezing point 0
	FreezingC Celsius = 0
	//BoilingC        boiling point 100
	BoilingC Celsius = 100
)

func (c Celsius) String() string    { return fmt.Sprintf("%g°C", c) }
func (f Fahrenheit) String() string { return fmt.Sprintf("%g°F", f) }
func (f Kelvin) String() string     { return fmt.Sprintf("%g°K", f) }

//!-
