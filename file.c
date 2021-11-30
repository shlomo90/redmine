#include "redmine.h"

extern int errno;

void create_mkdir(const char* path, mode_t mode)
{
    if (mkdir(path, 0777) < 0) {
        if (errno != EEXIST) {
            perror(path);
            exit(EXIT_FAILURE);
        }
    }
}

int file_exists(const char* path)
{
    if (access(path, AT_EACCESS) != 0) {
        if (errno == ENOENT) {
            return 0;
        }
        return -1;
    } else {
        return 1;
    }
}
