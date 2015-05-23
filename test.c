#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char* Xkb_Switch_getXkbLayout(const char*);

int
main() {
    while (1) {
        printf("Result: %s\n", Xkb_Switch_getXkbLayout(""));
        sleep(1);
    }
    return 0;
}
