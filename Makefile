GCC = gcc
SOURCES = lfs.c lfs_methods.c
OBJS := $(patsubst %.c,%.o,$(SOURCES))
CFLAGS = -O2 -Wall -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=25

.PHONY: lfs

##
# Libs 
##
LIBS := fuse 
LIBS := $(addprefix -l,$(LIBS))

all: lfs

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

lfs: $(OBJS)
	$(GCC) $(OBJS) $(LIBS) $(CFLAGS) -o lfs

clean:
	rm -f $(OBJS) lfs
