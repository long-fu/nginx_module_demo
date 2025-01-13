#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include "utils.h"
#include "base64.h"

static char *ngx_http_sig_authentication(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

typedef struct
{
  ngx_flag_t sig_verify;
  ngx_int_t sig_timeout;
  ngx_str_t internal_redirect;
} ngx_http_sig_authentication_conf_t; // 自定义的用于存储配置变量的结构体

static ngx_command_t ngx_http_sig_authentication_commands[] = {
    {ngx_string("sig_authentication"),
     NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,
     ngx_http_sig_authentication,
     0,
     0,
     NULL},
    {
        ngx_string("sig_verify"),                            // 配置指令的名称
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,                  // 只在 location 配置块中，且指令需要一个参数
        ngx_conf_set_flag_slot,                              // 处理函数：
        NGX_HTTP_LOC_CONF_OFFSET,                            // 配置项存储的位置
        offsetof(ngx_http_sig_authentication_conf_t, sig_verify), // 存储偏移量
        NULL                                                 // 默认无额外参数
    },
    {
        ngx_string("sig_timeout"),                            // 配置指令的名称
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,                   // 只在 location 配置块中，且指令需要一个参数
        ngx_conf_set_num_slot,                                // 处理函数：
        NGX_HTTP_LOC_CONF_OFFSET,                             // 配置项存储的位置
        offsetof(ngx_http_sig_authentication_conf_t, sig_timeout), // 存储偏移量
        NULL                                                  // 默认无额外参数
    },
    {
        ngx_string("internal_redirect"),                            // 配置指令的名称
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,                   // 只在 location 配置块中，且指令需要一个参数
        ngx_conf_set_str_slot,                                // 处理函数：将字符串存储到结构体
        NGX_HTTP_LOC_CONF_OFFSET,                             // 配置项存储的位置
        offsetof(ngx_http_sig_authentication_conf_t, internal_redirect), // 存储偏移量
        NULL                                                  // 默认无额外参数
    },    
    ngx_null_command};

static void *ngx_http_sig_authentication_create_conf(ngx_conf_t *cf)
{

  ngx_http_sig_authentication_conf_t *conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_sig_authentication_conf_t));
  if (conf == NULL)
  {
    return NULL;
  }
  conf->sig_verify = NGX_CONF_UNSET;
  conf->sig_timeout = NGX_CONF_UNSET;
  conf->internal_redirect.len = 0;
  conf->internal_redirect.data = NULL;
  return conf;
}

static char *ngx_http_sig_authentication_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
  ngx_http_sig_authentication_conf_t *prev = parent;
  ngx_http_sig_authentication_conf_t *conf = child;

  ngx_conf_merge_value(conf->sig_verify, prev->sig_timeout, 1);
  ngx_conf_merge_value(conf->sig_timeout, prev->sig_timeout, 1800);
  ngx_conf_merge_str_value(conf->internal_redirect, prev->internal_redirect, "/files");
  return NGX_CONF_OK;
}

static ngx_http_module_t ngx_http_sig_authentication_module_ctx = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ngx_http_sig_authentication_create_conf,
    ngx_http_sig_authentication_merge_conf};

ngx_module_t ngx_http_sig_authentication_module = {
    NGX_MODULE_V1,
    &ngx_http_sig_authentication_module_ctx,
    ngx_http_sig_authentication_commands,
    NGX_HTTP_MODULE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NGX_MODULE_V1_PADDING};

static ngx_int_t ngx_http_sig_authentication_handler(ngx_http_request_t *r)
{
  ngx_http_sig_authentication_conf_t *my_ccf = ngx_http_get_module_loc_conf(r, ngx_http_sig_authentication_module);
  printf("read config value: %d\n", my_ccf->sig_verify);
  if (!my_ccf || my_ccf->sig_verify == 0)
  {
    return NGX_DECLINED;
  }

  // TODO: 进行参数处理
  ngx_str_t file_path;
  file_path.data = file_path_data;
  file_path.len = ngx_strlen(file_path_data);

  return ngx_http_internal_redirect(r, &file_path, &r->args); // 默认处理静态文件的请求
}

static char *ngx_http_sig_authentication(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
  ngx_http_core_loc_conf_t *clcf;
  clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
  clcf->handler = ngx_http_sig_authentication_handler;
  return NGX_CONF_OK;
}