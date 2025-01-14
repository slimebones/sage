package bone

import (
	"os"
	"strings"
)

// Needs to be modified at testing to point to proper CWD.
var CwdDepth int = 0

func Cwd(pathParts ...string) string {
	// Secure
	path := strings.Join(pathParts, "/")
	path = strings.ReplaceAll(path, "\\", "/")
	path = strings.ReplaceAll(path, "../", "/")

	cwd, e := os.Getwd()
	if e != nil {
		panic("Cannot retrieve current working directory.")
	}
	for i := 0; i < CwdDepth; i++ {
		cwd += "/.."
	}
	return cwd + "/" + path
}

// Access var directory contents.
func Vardir(pathParts ...string) string {
	// @todo modify to work in prod with appdata
	// Secure
	path := strings.Join(pathParts, "/")
	path = strings.ReplaceAll(path, "\\", "/")
	path = strings.ReplaceAll(path, "../", "/")
	return Cwd("var", path)
}

func Mkdir(dir string) error {
	return os.MkdirAll(dir, 0755)
}
