#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "common.h"

void try_protect(const char *path) {
    size_t i;
    const char **p;
    char *buf, full_path[PATH_MAX + 1], *full_dir, cfg_path[PATH_MAX + 65];
    char question[512], answer[512];
    FILE *cfg_file;

    for(p = INVALID_PATH_LIST; *p; p++) {
        if(strcmp(path, *p) == 0) {
            fprintf(stderr, "%s may not be protected\n", path);
            return;
        }
    }

    buf = realpath(path, full_path);
    if(!buf) {
        fprintf(stderr, "Unable to get absolute path for %s\n", path);
        return;
    }

    full_dir = get_dir(full_path);
    sprintf(cfg_path, "%s.%s%s", full_dir, get_filename(full_path), CFG_SUFFIX);

    cfg_file = fopen(cfg_path, "w");
    if(!cfg_file) {
        fprintf(stderr, "Unable to open config file: %s\n", cfg_path);
        return;
    }

    while(1) {
        printf("Question for %s: ", full_path);
        if (!read_line(stdin, question, sizeof(question))) {
            fprintf(stderr, "Question is too long. Try another one.\n");
        } else {
            break;
        }
    }

    while(1) {
        printf("Answer: ");
        if (!read_line(stdin, answer, sizeof(answer))) {
            fprintf(stderr, "Answer is too long. Try another one.\n");
        } else {
            break;
        }
    }

    fprintf(cfg_file, "%s\n%s", question, answer);
    fclose(cfg_file);
}

int main(int argc, char *argv[]) {
    size_t i;

    if(argc < 2) {
        fprintf(stderr, "Nothing to protect\n");
        return 1;
    }

    for(i = 1; i < argc; i++) {
        try_protect(argv[i]);
    }

    return 0;
}
