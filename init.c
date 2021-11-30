#include "redmine.h"

static char user_path[MAX_PATH_LENGTH] = {0,};

static void init_user_dir(const char* home, const char* name)
{
    char  path[MAX_PATH_LENGTH] = {0,};

    if (MAX_PATH_LENGTH < strlen(home) 
            + 1 /*slash*/
            + strlen(REDMINE_DB)
            + 1 /*slash*/
            + strlen(name)) {
        fprintf(stderr, "Over MAX_PATH_LENGTH (%d)\n", MAX_PATH_LENGTH);
        exit(EXIT_FAILURE);
    }
    // TODO: check current path already exists.
    strncat(path, home, MAX_PATH_LENGTH);
    strncat(path, "/", MAX_PATH_LENGTH);
    strncat(path, REDMINE_DB, MAX_PATH_LENGTH);
    create_mkdir(path, 0777);

    // TODO: check current path already exists.
    strncat(path, "/", MAX_PATH_LENGTH);
    strncat(path, name, MAX_PATH_LENGTH);
    create_mkdir(path, 0777);

    memcpy(user_path, path, MAX_PATH_LENGTH);
}

static void save_remote_url(const char* url)
{
    char    path[MAX_PATH_LENGTH] = {0,};
    int     fd, cnt, is_file;

    if (MAX_PATH_LENGTH < strlen(user_path)
            + 1 /*slash*/
            + strlen(ORIGIN_URL)) {
        fprintf(stderr, "Over MAX_PATH_LENGTH\n");
        exit(EXIT_FAILURE);
    }

    strncat(path, user_path, MAX_PATH_LENGTH);
    strncat(path, "/", MAX_PATH_LENGTH);
    strncat(path, ORIGIN_URL, MAX_PATH_LENGTH);

    is_file = file_exists(path);
    if (is_file == 1) {
        fprintf(stderr, "ORIGIN File already exists.\n");
        exit(EXIT_FAILURE);
    } else if (is_file == -1) {
        fprintf(stderr, "ORIGIN File Check error.\n");
        exit(EXIT_FAILURE);
    }

    fd = open(path, O_WRONLY|O_CREAT, 0777);
    if (fd == -1) {
        fprintf(stderr, "ORIGIN File open error.\n");
        exit(EXIT_FAILURE);
    }

    cnt = write(fd, url, strlen(url));
    printf("DEBUG: write:%d\n", cnt);

    close(fd);
}

int main(int argc, char* argv[])
{
    char *home;

    home = getenv("HOME");
    if (home == NULL) {
        fprintf(stderr, "There is no HOME environment.\n");
        return EXIT_FAILURE;
    }

    // init lim "http://redmine.piolink.com"
    if (argc != 3) {
        fprintf(stderr, "init name remote_url.\n");
        return EXIT_FAILURE;
    }

    init_user_dir(home, argv[1]);

    // TODO: check url is available.
    save_remote_url(argv[2]);
    return EXIT_SUCCESS;
}
