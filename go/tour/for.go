package main

import "fmt"

func main() {
	sum := 0
	// 初始化语句; 条件表达式; 后置语句
	for i := 0; i < 10; i++ {
		sum += i
	}
	fmt.Println(sum)
}
