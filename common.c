#include <stdio.h>
#include <string.h>
#include "common.h"

const char *INVALID_PATH_LIST[] = {
    ".",
    "..",
    "./",
    "../",
    NULL
};

char * get_filename(const char *abs_path) {
    static char filename[PATH_MAX + 1];
    size_t len, i;
    
    len = strlen(abs_path);
    strcpy(filename, abs_path);
    for(i = len - 1; i >= 0; i--) {
        if(filename[i] == '/') {
            return &filename[i + 1];
        }
    }

    return filename;
}

char * get_dir(const char *abs_path) {
    static char dir[PATH_MAX + 1];
    size_t len, i;
    
    len = strlen(abs_path);
    strcpy(dir, abs_path);
    for(i = len - 1; i >= 0; i--) {
        if(dir[i] == '/') {
            dir[i + 1] = 0;
            break;
        }
    }

    return dir;
}

void read_line(FILE *src, char *str, int max_len) {
    int i;

    for(i = 0; i < max_len; i++) {
        str[i] = fgetc(src);
        if(str[i] <= 0 || str[i] == '\n') break;
    }
    str[i] = 0;
}
