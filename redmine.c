#include "redmine.h"

typedef int (*func_ptr)(int argc, char* argv[]);


struct route_s {
    char           *name;
    func_ptr        func;
};

typedef struct route_s route_t;


static route_t router[] = {
    {"init", init_main},
    {"open", open_main}
};

static int      save_argc;
static char   **save_argv;


func_ptr get_function(const char *feature)
{
    int     i;

    if (feature == NULL) {
        return NULL;
    }

    for (i=0; i<NUMELEM(router); i++) {
        if (strcmp(router[i].name, feature) == 0) {
            return router[i].func;
        }
    }
    return NULL;
}

static void redmine_help(void)
{
    const char      *help = "Redmine Help Message.\n"
                            "ex: redmine init <name> <remote_url>\n";

    printf("%s", help);
}


int main(int argc, char* argv[])
{
    int         ret = 0;
    func_ptr    func = NULL;

    if (argc == 1) {
        redmine_help();
        exit(1);
    }

    func = get_function(argv[1]);
    if (func == NULL) {
        redmine_help();
        exit(1);
    }

    save_argc = argc--;
    save_argv = &argv[1];
    ret = func(argc, &argv[1]);
    return ret;
}
