package main

import (
	"fmt"
	"math"
)

func Pic(dx, dy int) [][]uint8 {
	p := make([][]uint8, dy)
	for i := 0; i < dy; i++ {
		p[i] = make([]uint8, dx)
	}

	for i := 0; i < dy; i++ {
		for j := 0; j < dx; j++ {
			p[i][j] = uint8(math.Pow(float64(i), float64(j)))
		}
	}
	return p
}

func main() {
	fmt.Printf("%v", Pic(5, 4))
}
