package main

import "fmt"

type I interface {
	M()
}

func main() {
	var i I
	describe(i)
	i.M() // 因为它并未指向一个函数指针
}

func describe(i I) {
	fmt.Printf("(%v, %T)\n", i, i)
}
