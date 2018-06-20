package main

import "fmt"

// 使用 const 关键字声明常量，不能用 `:=` 语法
const Pi = 3.14

func main() {
	const World = "world"
	fmt.Println("Hello", World)
	fmt.Println("Happy", Pi, "Day")

	const Truth = true
	fmt.Println("Go rules?", Truth)
}
