#include "utils.h"

typedef struct BufferProcessor {
    char Key[32];
    Function* Select;
    Function* Update;
    Function* Deselect;
    Function* SetMode;
} BufferProcessor;

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

// There are up to 64 buffers.
extern Buffer Buffers[64];

void SelectBuffer(Buffer* buffer);
void UpdateBuffer(Buffer* buffer);
void DrawBuffer(Buffer* buffer);
void DeselectBuffer(Buffer* buffer);
void OpenBufferFile(char* path);
void CloseBufferFile();
