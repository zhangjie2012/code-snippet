package main

import (
	"fmt"
	"runtime"
)

func main() {
	fmt.Print("Go runs on ")
	// Go 的 switch 语句类似于 C、C++ 等语言的语法，但是不同点在于只运行选定的
	// case，而非之后所有的 case。C++ 的 switch 只需要一个入口，然后一直执行
	// 直到遇到 break 语句
	// 而且，switch 的 case 无需为常量，且取值不必为整数。
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X.")
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd
		// plan9, windows..
		fmt.Printf("%s.", os)
	}
}
