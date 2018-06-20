package main

import "fmt"

func main() {
	var i, j int = 1, 2
	k := 3
	// 在函数中，类型明确的地方可以使用 := 代替 var
	// 在函数外，不可使用 := 结构
	c, python, java := true, false, "no!"

	fmt.Println(i, j, c, k, python, java)
}
