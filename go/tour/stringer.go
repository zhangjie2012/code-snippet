package main

import "fmt"

type Person struct {
	Name string
	Age  int
}

// 类似 Python 中的 __str__ 接口
func (p Person) String() string {
	return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
}

func main() {
	a := Person{"Arthur Dent", 42}
	z := Person{"Zaphod Beeblebrox", 9001}
	fmt.Println(a, z)
}
