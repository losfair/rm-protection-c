#ifndef _RMP_COMMON_H_
#define _RMP_COMMON_H_

#include <stdio.h>

#define PATH_MAX 65536
#define CFG_SUFFIX ".rm-protection"
#define RM_PATH "/bin/rm"

extern const char *INVALID_PATH_LIST[];
char * get_filename(const char *abs_path);
char * get_dir(const char *abs_path);
int read_line(FILE *src, char *str, size_t max_len);

#endif
