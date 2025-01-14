package bone

func Unwrap(er error) {
	if er != nil {
		panic(er.Error())
	}
}
