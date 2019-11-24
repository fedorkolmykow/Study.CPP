#!/bin/sh
g++ cgi.cpp cgi_class.cpp DB.cpp -o programm.cgi
scp DB.h cgi_class.h start.html blank.html programm.cgi fakolmykow@mati.su:~/www/fakolmykow.mati.su
