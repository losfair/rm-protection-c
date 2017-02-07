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

int read_line(FILE *src, char *str, size_t max_len) {
    size_t i;
    int ch;

    for(i = 0; i < max_len; i++) {
        ch = fgetc(src);
        if(ch == EOF || ch == '\n') {
            str[i] = 0;
            break;
        }
        str[i] = ch;
    }
    if (i >= max_len) {
        // clear stdin buffer
        while ((ch = fgetc(src)) != '\n' && ch != EOF) { };
        return 0;
    }
    return 1;
}
