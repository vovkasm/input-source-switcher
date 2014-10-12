#include <stdio.h>
#include <stdlib.h>

const char* Xkb_Switch_getXkbLayout(const char*);

int
main() {
    printf("Result: %s\n", Xkb_Switch_getXkbLayout(""));
    return 0;
}
