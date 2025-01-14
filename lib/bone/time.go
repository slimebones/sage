package bone

import "time"

type Time = int64

// We consider standard time.Time as a Date, other mentions of Time are unix
// timestamps.
type Date = time.Time

func TimeToDate(t int64) Date {
	return time.Unix(t, 0)
}

func TimeNowSec() int64 {
	return DateNow().Unix()
}

func DateNow() Date {
	return time.Now()
}

func TimeSleep(duration int64) {
	time.Sleep(time.Duration(duration * 1000))
}
