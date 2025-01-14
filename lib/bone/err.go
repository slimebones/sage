package bone

import (
	"fmt"
	"strconv"
	"strings"
)

// Note on Errors.
// We only use default Go error, but we write a code as the first number in
// the message: `CODE: MESSAGE...`. This way we integrate nicely without
// creating custom error structs. If an error message does not conform to such
// formatting, we consider it has code 1.

// Convert from one error to another using conversion map.
// If code is not found in the conversion map, default error is created and
// returned.

func ErrorUnwrap(target error) {
	if target != nil {
		panic(target.Error())
	}
}

func ErrorConvert(target error, conversion map[int]int) error {
	r, ok := conversion[ErrorCode(target)]
	if !ok {
		return Error(1)
	}
	return Error(r)
}

func ErrorIs(er error, anycode ...int) bool {
	if er == nil {
		return false
	}
	ecode := ErrorCode(er)
	for _, c := range anycode {
		if ecode == c {
			return true
		}
	}
	return false
}

func ErrorCode(target error) int {
	codeStr, _ := strings.CutPrefix(target.Error(), "ERROR ")
	code, e := strconv.Atoi(codeStr)
	if e != nil {
		return 1
	}
	return code
}

func ErrorArgs(target error) []string {
	parts := strings.SplitN(target.Error(), ":", 1)
	if len(parts) < 2 {
		return nil
	}
	return strings.Split(parts[1], ";")
}

func Error(code int) error {
	if code < 1 {
		code = 1
	}
	return fmt.Errorf("ERROR %d", code)
}
