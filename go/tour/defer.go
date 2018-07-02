package main

import "fmt"

func main() {
	// 推迟调用的函数其参数会立即求职，但直到外层函数返回前该函数都不会被调用
	defer fmt.Println("world")
	fmt.Println("Hello")
}
