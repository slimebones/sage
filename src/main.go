package main

import (
	"sage/lib/bone"
	"sage/src/core"
)

func main() {
	bone.Init(bone.InitArgs{
		Appname: "sage",
	})
	core.Init()
}
