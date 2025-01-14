package bone

type InitArgs struct {
	Appname string
}

// Init all bone stuff. Should be called at startup in main-like function.
func Init(args InitArgs) {
	appInit(args.Appname)
}
