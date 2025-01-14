package bone

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestCombstringCapitalize(t *testing.T) {
	var cs *Combstring

	cs = New("")
	assert.Equal(t, "", cs.Capitalize().Value)

	cs = New("h")
	assert.Equal(t, "H", cs.Capitalize().Value)

	cs = New("he")
	assert.Equal(t, "He", cs.Capitalize().Value)

	cs = New("hello world")
	assert.Equal(t, "Hello world", cs.Capitalize().Value)
}
