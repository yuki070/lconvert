SUBDIRS = lua

bin_PROGRAMS = lconvert
lconvert_SOURCES = \
main.cpp \
context.h \
context.cpp \
luahelper.h \
luahelper.cpp \
stringutil.h \
stringutil.cpp \
logger.h \
logger.cpp
lconvert_CPPFLAGS = -I$(BIPROG_ROOT)/include
lconvert_LDFLAGS = -L$(BIPROG_ROOT)/lib
lconvert_LDADD = lua/liblua.a
