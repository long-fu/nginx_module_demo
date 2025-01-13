# nginx_module_demo

```sh
|-- nginx-1.22.1 # 源码
├── nginx.conf # demo配置文件
├── ngx_http_sig_authentication # 参数签名验证模块
│   ├── base64.c
│   ├── base64.h
│   ├── config # nginx 模块开发标准配置
│   ├── ngx_http_sig_authentication_module.c # 源代码
│   ├── utils.c
│   └── utils.h
├── README.md
|-- build.sh #编译脚本
└── run.sh # 运行脚本
```