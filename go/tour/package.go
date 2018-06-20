// 按照约定包名与导入路径的最后一个元素一致。例如 "math/rand" 中的
// 源码均以 package rand 语句开始。

package main

import (
	"fmt"
	"math/rand"
)

func main() {
	fmt.Println("My favorite number is ", rand.Intn(10))
}
