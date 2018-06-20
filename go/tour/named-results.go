package main

import "fmt"

// 命名返回值，可以被视为定为为在函数顶部的变量
// 返回值的名称应当具有一定的意义，它可以作为文档使用
// 没有参数的 return 语句返回已命名的返回值。也就是直接返回
// 直接返回语句应当用在下面这样的短函数中。在长函数中它们会影响代码的可读性
func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

func main() {
	fmt.Println(split(7))
}
