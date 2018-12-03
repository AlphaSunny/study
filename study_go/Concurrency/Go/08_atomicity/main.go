package main

//通过原子数的方式来解决race
//原子性不论是多核还是单核，具有原子性的量，同一时刻只能有一个线程来对它进行操作！
import (
	"fmt"
	"math/rand"
	"sync"
	"sync/atomic"
	"time"
)

var wg sync.WaitGroup
var counter int64

func main() {
	wg.Add(2)
	go incrementor("Foo:")
	go incrementor("Bar:")
	wg.Wait()
	fmt.Println("Final Counter:", counter)
}

func incrementor(s string) {
	for i := 0; i < 20; i++ {
		time.Sleep(time.Duration(rand.Intn(3)) * time.Millisecond)
		atomic.AddInt64(&counter, 1)
		fmt.Println(s, i, "Counter:", atomic.LoadInt64(&counter)) // access without race
	}
	wg.Done()
}

// go run -race main.go
// vs
// go run main.go
