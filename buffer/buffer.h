#include "utils.h"
#define MAX_BUFFERS 64

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
    // BufferProcessor* Processor;
    BufferMode Mode;
} Buffer;

extern Buffer* Buffers[MAX_BUFFERS];

void SelectBuffer(Buffer* buffer);
void UpdateBuffer(Buffer* buffer);
void DrawBuffer(Buffer* buffer);
void DeselectBuffer(Buffer* buffer);
void OpenBufferFile(char* path);
void CloseBufferFile();
