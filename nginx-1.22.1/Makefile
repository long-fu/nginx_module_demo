
default:	build

clean:
	rm -rf Makefile objs

.PHONY:	default clean

build:
	$(MAKE) -f objs/Makefile

install:
	$(MAKE) -f objs/Makefile install

modules:
	$(MAKE) -f objs/Makefile modules

upgrade:
	/home/haoshuai/code/docker_nginx/app/nginx/sbin/nginx -t

	kill -USR2 `cat /home/haoshuai/code/docker_nginx/app/nginx/logs/nginx.pid`
	sleep 1
	test -f /home/haoshuai/code/docker_nginx/app/nginx/logs/nginx.pid.oldbin

	kill -QUIT `cat /home/haoshuai/code/docker_nginx/app/nginx/logs/nginx.pid.oldbin`

.PHONY:	build install modules upgrade
