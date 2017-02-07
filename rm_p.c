#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "common.h"

inline void strtolower(char *str) {
    char *c;
    for(c = str; *c; c++) {
        *c = tolower(*c);
    }
}

unsigned char input_and_verify() {
    char input[4];
    int i;


    if (!read_line(stdin, input, sizeof(input))) {
        return 0;
    }
    strtolower(input);

    if(
        strcmp(input, "yes") == 0
        || strcmp(input, "y") == 0
    ) {
        return 1;
    }

    return 0;
}

unsigned char ends_with(const char *str, const char *suffix)
{
    size_t len_str, len_suffix;
    if(!str || !suffix) return 0;

    len_str = strlen(str);
    len_suffix = strlen(suffix);

    if(len_suffix > len_str) return 0;
    return strncmp(str + len_str - len_suffix, suffix, len_suffix) == 0;
}


int main(int argc, char *argv[], char *envp[]) {
    size_t i, j, suffix_length, args_buf_pos;
    unsigned char option_ended = 0;
    unsigned char *args_to_remove;
    char path_buf[PATH_MAX + 1], *buf, *dir_buf, cfg_path[PATH_MAX + 65];
    char **args_buf;
    FILE *cfg_file;
    char question[512], answer[512], user_answer[512];

    if(argc < 2) {
        fprintf(stderr, "Nothing to remove\n");
    }

    args_to_remove = malloc(sizeof(unsigned char) * argc);
    for(i = 0; i < argc; i++) args_to_remove[i] = 0;

    suffix_length = strlen(CFG_SUFFIX);

    for(i = 1; i < argc; i++) {
        if(!option_ended && argv[i][0] == '-') {
            if(strcmp(argv[i], "--") == 0) {
                option_ended = 1;
            }
            continue;
        }
        buf = realpath(argv[i], path_buf);
        if(!buf) {
            fprintf(stderr, "Warning: File not found: %s\n", argv[i]);
            continue;
        }
        if(ends_with(path_buf, CFG_SUFFIX)) {
            printf("%s is a protection file\n", path_buf);
            printf("Do you want to remove it? (y/n) ");
            if(!input_and_verify()) {
                printf("%s will not be removed\n", path_buf);
                args_to_remove[i] = 1;
                continue;
            }
        }

        dir_buf = get_dir(path_buf);
        sprintf(cfg_path, "%s.%s%s", dir_buf, get_filename(path_buf), CFG_SUFFIX);
        cfg_file = fopen(cfg_path, "r");

        if(cfg_file) {
            if (!read_line(cfg_file, question, sizeof(question)) || !read_line(cfg_file, answer, sizeof(answer))) {
                fprintf(stderr, "Error: File %s is coruptted!\n", cfg_path);
                fclose(cfg_file);
                continue;
            }
            fclose(cfg_file);

            printf("%s: %s\n", path_buf, question);
            printf("Answer: ");
            
            if(!read_line(stdin, user_answer, sizeof(user_answer)) || strcmp(user_answer, answer) != 0) {
                printf("Wrong answer! %s will not be removed\n", path_buf);
                printf("The correct answer is stored in %s\n", cfg_path);
                args_to_remove[i] = 1;
                continue;
            }
        }
    }

    args_buf = malloc(sizeof(char *) * (argc + 1));
    args_buf[0] = RM_PATH;
    args_buf_pos = 1;

    for(i = 1; i < argc; i++) {
        if(!args_to_remove[i]) {
            args_buf[args_buf_pos] = argv[i];
            args_buf_pos++;
        }
    }
    args_buf[args_buf_pos] = NULL;

    execve(RM_PATH, args_buf, envp);

    free(args_buf);
    free(args_to_remove);

    fprintf(stderr, "Failed to execute %s\n", RM_PATH);

    return 1;
}
