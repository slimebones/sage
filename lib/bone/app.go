package bone

import (
	"os"
	"strings"

	"github.com/go-ini/ini"
)

type ConfigKey = ini.Key

type AppConfig struct {
	data *ini.File
}

// Returns nil if not found.
func (cfg *AppConfig) Get(module string, key string) *ConfigKey {
	moduleData, e := cfg.data.GetSection(Mode() + "." + module)
	if e != nil {
		return nil
	}
	value, e := moduleData.GetKey(key)
	if e != nil {
		return nil
	}
	return value
}

var Config *AppConfig
var appname string = "app"
var mode string = "default"

func Mode() string {
	return mode
}

func Appname() string {
	return appname
}

var SANITIZED_APPNAME_ALLOWED_SYMBOLS = []rune{
	'_',
}

func SanitizedAppname() string {
	return StrSanitizeAlnumAllowed(appname, SANITIZED_APPNAME_ALLOWED_SYMBOLS)
}

func appInit(appname_ string) {
	appname = appname_
	mode = os.Getenv(strings.ToUpper(SanitizedAppname()) + "_" + "MODE")
	if mode == "" {
		mode = "default"
	}

	c, e := ini.Load(Vardir("app.cfg"))
	// @todo create on missing
	if e != nil {
		panic(e.Error())
	}
	Config = &AppConfig{
		data: c,
	}
}
