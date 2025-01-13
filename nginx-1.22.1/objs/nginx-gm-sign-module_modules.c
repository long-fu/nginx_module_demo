
#include <ngx_config.h>
#include <ngx_core.h>

extern ngx_module_t  -gm-sign-module_MODULES;

ngx_module_t *ngx_modules[] = {
    &-gm-sign-module_MODULES,
    NULL
};

char *ngx_module_names[] = {
    "-gm-sign-module_MODULES",
    NULL
};

char *ngx_module_order[] = {
    "-gm-sign-module_ORDER",
    NULL
};

