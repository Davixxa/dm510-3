#include <fuse.h>
#include "lfs_methods.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if FUSE_USE_VERSION < 25
#define FUSE_USE_VERSION 25
#endif


/* FUSE Things.*/
int lfs_getattr( const char *, struct stat * );
int lfs_readdir( const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info * );
int lfs_open( const char *, struct fuse_file_info * );
int lfs_read( const char *, char *, size_t, off_t, struct fuse_file_info * );
int lfs_release(const char *path, struct fuse_file_info *fi);
int lfs_mkdir(const char *path, mode_t mode);
int lfs_rmdir(const char *path);
int lfs_mknod(const char *path, mode_t mode, dev_t device);
int lfs_write(const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *info);

static struct fuse_operations lfs_oper = {
	.getattr	= lfs_getattr,
	.readdir	= lfs_readdir,
	.mknod = lfs_mknod, // mk file
	.mkdir = lfs_mkdir,
	.unlink = NULL, // rmfile
	.rmdir = lfs_rmdir,
	.truncate = NULL,
	.open	= lfs_open,
	.read	= lfs_read,
	.release = lfs_release,
	.write = lfs_write,
	.rename = NULL,
	.utime = NULL
};

int lfs_getattr( const char *path, struct stat *stbuf ) {
	int res = 0;
	printf("getattr: (path=%s)\n", path);

	memset(stbuf, 0, sizeof(struct stat));
	if( strcmp( path, "/" ) == 0 ) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if(is_file(path) == 1) {
		stbuf->st_mode = S_IFREG | 0777;
		stbuf->st_nlink = 1;
		stbuf->st_size = get_file_size(path);
		stbuf->st_atime = get_file_by_index(get_file_index(path))->last_accessed_timestamp;
		stbuf->st_mtime = get_file_by_index(get_file_index(path))->last_modified_timestamp;

	} else if(is_directory(path) == 1) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else {
		printf("Reaches else");
		res = -ENOENT;
	}
	return res;
}

/*
* Initially, list everything in the root. Later on, if I have time, let the parent directory decide the fate of a file.
*/
int lfs_readdir( const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi ) {
	(void) offset;
	(void) fi;
	printf("readdir: (path=%s)\n", path);

	if(strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);


	for(int i = 0; i < get_current_folder_index(); i++) {
		filler(buf, get_folder_by_index(i)->foldername, NULL, 0);
	}

	for(int i = 0; i < get_current_file_index(); i++) {
		filler(buf, get_file_by_index(i)->filename, NULL, 0);
	}


	return 0;
}

// Theoretically this doesn't really do anything but it does provide the system with a file.
int lfs_open( const char *path, struct fuse_file_info *fi ) {
    printf("open: (path=%s)\n", path);
	fi->fh = get_file_by_index(get_file_index(path))->file_id;
	return 0; 
}



int lfs_read( const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi ) {
    printf("read: (path=%s)\n", path);
	if (path == NULL) 
		return -1;
	int index = get_file_index(path);
		if (index == -1) 
			return -1;
	set_accessed_time_to_now(path);
	char *content = get_file_by_index(index)->file_contents;	
	memcpy( buf, content + offset, size );
	return strlen(content)-offset;
}

int lfs_release(const char *path, struct fuse_file_info *fi) {
	printf("release: (path=%s)\n", path);
	return 0;

}


int lfs_mknod(const char *path, mode_t mode, dev_t device) {
	path++;
	add_file(path);
	return 0;
}

int lfs_mkdir(const char *path, mode_t mode) {
	path++;
	add_directory(path);
	return 0;
}


int lfs_write(const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *info) {
	write_file(path, buffer);
	return size;
}

int lfs_rmdir(const char* dir) {
	return 0;
}

int main( int argc, char *argv[] ) {
	
	// Write binary

	//disk = fopen("lfs_img.img", "r+b");

	

	fuse_main( argc, argv, &lfs_oper );

	return 0;
}
