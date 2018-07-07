package main

import "fmt"

// f(x) = f(x-1) + f(x-2)

// 闭包
func fibonacci() func() int {
	t1, t2 := 0, 1
	return func() int {
		v := t1 + t2
		t1 = t2
		t2 = v
		return v
	}
}

// 递归
func fibonacci1(x int) int {
	if x == 0 {
		return 0
	}
	if x == 1 {
		return 1
	}
	return fibonacci1(x-1) + fibonacci1(x-2)
}

// 迭代
func fibonacci2(count int) {
	x, y := 0, 1
	for i := 0; i < count; i++ {
		v := x + y
		x = y
		y = v
		fmt.Println(v)
	}
}

func main() {
	// f := fibonacci()
	// for i := 0; i < 10; i++ {
	// 	fmt.Println(f())
	// }
	// for i := 0; i < 10; i++ {
	// 	fmt.Println(fibonacci1(i))
	// }
	fibonacci2(10)
}
