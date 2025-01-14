package bone

import (
	"encoding/csv"
	"fmt"
	"os"
	"strings"
)

// {locale: {key: value}}
var translationMap = map[string]map[string]string{}
var translationLocale string = "en"

// Register a translation from a CSV file.
// CSV file structure:
// key(string),text(string)
//
// This function can be called many times, each new call the old matching
// entries will be overwritten.
//
// Text may contain placeholders in form of `%` to accept incoming value,
// which will always be converted to string.
//
// For list of locales refer to https://docs.godotengine.org/en/4.3/tutorials/i18n/locales.html
func TrLoadCsv(path string, locale string, delimiter rune) error {
	locale = strings.ToLower(locale)

	file, e := os.Open(path)
	if e != nil {
		return Error(1)
	}
	defer file.Close()

	reader := csv.NewReader(file)
	reader.Comma = delimiter
	records, e := reader.ReadAll()
	if e != nil {
		return Error(1)
	}

	localeMap, ok := translationMap[locale]
	if !ok {
		localeMap = map[string]string{}
		translationMap[locale] = localeMap
	}

	for i, record := range records {
		if len(record) != 2 {
			return Error(1)
		}
		if i == 0 {
			continue
		}
		localeMap[strings.TrimSpace(record[0])] = strings.TrimSpace(record[1])
	}

	return nil
}

func TrCode(code int) string {
	return Tr(fmt.Sprintf("CODE_%d", code))
}

// Codes are translated using keys `CODE_%`, where `%` is the number.
func TrCodeOrError(code int) (string, error) {
	return TrOrError(fmt.Sprintf("CODE_%d", code))
}

func Tr(key string) string {
	t, e := TrOrError(key)
	if e != nil {
		return key
	}
	return t
}

func TrOrError(key string) (string, error) {
	key = strings.ToUpper(key)
	localeMap, ok := translationMap[translationLocale]
	if !ok {
		return "", Error(1)
	}
	text, ok := localeMap[strings.ToUpper(key)]
	if !ok {
		return "", Error(1)
	}
	return text, nil
}
