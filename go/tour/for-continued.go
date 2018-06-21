package main

import "fmt"

func main() {
	sum := 1
	// 初始化语句和后置语句是可选的
	// 跟 while 作用的一样，所以 Go 中没有 while 语句，可以直接用 for 来替代
	for sum < 1000 {
		sum += sum
	}
	fmt.Println(sum)
}
