#include "raylib.h"
#include <stdio.h>
#include "utils.h"

typedef struct Layout {
    LayoutWritables* writables;
} Layout;

typedef struct LayoutWritables {
    char* tilde;
    char* k1;
    char* k2;
    char* k3;
    char* k4;
    char* k5;
    char* k6;
    char* k7;
    char* k8;
    char* k9;
    char* k0;
    char* hyphen;
    char* equal;

    char* q;
    char* w;
    char* e;
    char* r;
    char* t;
    char* y;
    char* u;
    char* i;
    char* o;
    char* p;
    char* bracket_right;
    char* bracket_left;
    char* backslash;
    char* a;
    char* s;
    char* d;
    char* f;
    char* g;
    char* h;
    char* j;
    char* k;
    char* l;
    char* semicolon;
    char* z;
    char* x;
    char* c;
    char* v;
    char* b;
    char* n;
    char* m;

    char* comma;
    char* dot;
    char* slash;
    char* space;
    char* apostrophe;
} LayoutWritables;

void UpdateInput();
