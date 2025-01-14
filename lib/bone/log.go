package bone

import "fmt"

// @todo use loguru-like sinks

func Log(message string, args ...any) {
	fmt.Printf(message+"\n", args...)
}

func LogError(message string, args ...any) {
	fmt.Printf("ERROR: "+message+"\n", args...)
}
