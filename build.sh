#!/bin/bash

cd nginx-1.22.1

make claen
./configure --prefix=$(pwd)/app/nginx \
    --with-http_stub_status_module \
    --with-http_ssl_module \
    --with-http_mp4_module \
    --with-http_v2_module \
    --with-http_gzip_static_module \
    --add-dynamic-module=../ngx_http_sig_authentication  
make -j20
make install