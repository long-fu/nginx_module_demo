#!/bin/bash

export LD_LIBRARY_PATH="$(pwd)/app/nginx/modules:$LD_LIBRARY_PATH"

sudo $(pwd)/app/nginx/sbin/nginx -V

sudo $(pwd)/app/nginx/sbin/nginx -g "daemon off;"