AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=hello
hello_SOURCES=hello.cpp tree.cpp td/td.cpp log.cpp tconn.cpp task.cpp 
INCLUDES=-I./snslib -I/usr/local/include

hello_CPPFLAGS= -g -Wall -Wextra -O3 -pipe -fno-omit-frame-pointer
#noinst_HEADERS=hello.h

#hello_LDADD=lib/libudp_client.a snslib/libsns.a -lprofiler -lunwind
##-ltcmalloc_and_profiler #-lprofiler -lunwind
include_HEADERS= hello.h test.h tree.h Net.h td/td.h SingletonHolder.h log.h task.h tconn.h student.h
