/* ------------------------------------------------------------------------- *\
 * Standard Includes
 * ------------------------------------------------------------------------- */
#include <unistd.h>
#include <dirent.h>

/* ------------------------------------------------------------------------- *\
 * Espressif specific includes
 * ------------------------------------------------------------------------- */
#include "argtable3/argtable3.h"
#include "esp_console.h"
#include "esp_log.h"

/* ------------------------------------------------------------------------- *\
 * MbedCraft includes
 * ------------------------------------------------------------------------- */
#include "mc_assert.h"

/* ------------------------------------------------------------------------- *\
 * Type definitions
 * ------------------------------------------------------------------------- */
static struct {
    struct arg_str *path;
    struct arg_end *end;
} ls_args;

/* ------------------------------------------------------------------------- *\
 * Private function definitions
 * ------------------------------------------------------------------------- */
static int __ls_cmd(int argc, char **argv);

/* ------------------------------------------------------------------------- *\
 * Public function implementations
 * ------------------------------------------------------------------------- */
void mc_cmd_fs_register(void)
{
    ls_args.path = arg_str1(NULL, NULL, "<path>",
            "The list informations will be retrieved about this path");
    ls_args.end = arg_end(1);

    const esp_console_cmd_t ls_cmd = {
        .command = "ls",
        .help = "Lists information about the FILEs.\n",
        .hint = NULL,
        .func = &__ls_cmd,
        .argtable = &ls_args
    };

    ESP_ERROR_CHECK(esp_console_cmd_register(&ls_cmd));
}

/* ------------------------------------------------------------------------- *\
 * Private function implementations
 * ------------------------------------------------------------------------- */
static int __ls_cmd(int argc, char **argv) {
    DIR * dp;

    ASSERTW_RET(2 == argc, -1, "Internal error");

    dp = opendir(argv[1]);
    if(!dp) {
        perror(argv[1]);
        return -1;
    }
    struct dirent * ep;

    while((ep = readdir(dp))) {
        printf("\t%s\n", ep->d_name);
    }

    closedir(dp);

    return 0;
}
