package main

import "fmt"

func main() {
	fmt.Println("counting")

	// 函数会被压栈
	for i := 0; i < 10; i++ {
		defer fmt.Println(i)
	}

	fmt.Println("done")
}
