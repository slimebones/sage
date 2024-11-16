#include "utils.h"

typedef enum BufferMode {
    Normal,
    Insert,
    Visual,
    Command,
} BufferMode;

typedef struct Buffer {
    BufferProcessor Processor;
    BufferMode Mode;
} Buffer;

typedef struct BufferProcessor {
    char Key[32];
    Function* Select;
    Function* Update;
    Function* Deselect;
    Function* SetMode;
} BufferProcessor;

// There are up to 64 buffers.
extern Buffer Buffers[64];

void SelectBuffer(Buffer* buffer);
void UpdateBuffer(Buffer* buffer);
void DeselectBuffer(Buffer* buffer);
void OpenBufferFile(char* path);
void CloseBufferFile();
