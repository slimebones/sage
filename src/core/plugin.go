package core

// Plugin boot:
// * Load plugins
// * Init plugins
// * Enable plugins that should be enabled
//
// Plugin shutdown:
// * Disable enabled plugins
// * Deinit plugins
// * Unload plugins
type Plugin interface {
	// Key of a plugin which must be unique across all loaded plugins.
	Key() string
	// Friendly name of a plugin.
	Name() string
	// Types that plugin work with. If there is multiple enabled plugins with
	// the same handled types, the core will sent calls only to the first
	// enabled one.
	Types() []string

	Init(args *PluginInitArgs) bool
	Deinit() bool
	Call(c *PluginContext) bool
}

// Messages from core to plugin.
const (
	Core_Enable int = iota
	Core_Disable

	// Execution of a command, directed to this buffer.
	// Data: array of 2 strings - command itself and arguments
	Core_ExecuteCommand
	// Buffer type and/or body has been changed.
	// Data: null
	Core_Updated
)

// Messages from plugin to core.
const (
	// Write body of buffer starting from offset.
	// Data: []byte
	Plugin_Write int = iota
	// Response to last successfully executed command.
	// Data: string
	Plugin_CommandResponse
)

type PluginInitArgs struct {
	// Id of the plugin amongst loaded ones.
	Id       int
	Response func(callback int, data any) bool
}

type PluginContext struct {
	// Code of core event.
	CoreEvent int
	// Data specific to the call.
	Data any

	BufferId   *int
	BufferType *string
	BufferBody *[]byte
}
