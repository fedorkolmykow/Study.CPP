#!/bin/sh
g++ cgi.cpp cgi_class.cpp DB.cpp -o programm.cgi
scp DB.h cgi_class.h index.html blank.html programm.cgi DB_records.txt fakolmykow@mati.su:~/www/fakolmykow.mati.su
