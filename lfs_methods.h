#ifndef LFS_METHODS_H
#define LFS_METHODS_H

#include <stdint.h>
#include <time.h>

#define DEFAULT_TABLE_SIZE 256
#define NUM_DATA_POINTERS 27
//#define DIRECTORY 1
//#define FILE 2

struct folder_list_entry {
    char foldername[256];
    uint64_t parent_folder_id; // -1 if root
    time_t last_modified_timestamp;
    time_t last_accessed_timestamp;
};

struct file_list_entry {
    char filename[256]; // Filepath length
    uint64_t parent_folder_id; // -1 if root
    uint64_t file_id;
    uint64_t file_size;
    time_t last_modified_timestamp;
    time_t last_accessed_timestamp;
    char file_contents[1024];
};

struct Directory_Table {
    struct folder_list_entry folder_entries[DEFAULT_TABLE_SIZE];
    struct file_list_entry file_entries[DEFAULT_TABLE_SIZE];
};


int get_current_folder_index();

int get_current_file_index();

/* Attempt to find the file in the file index array. If it's there, return the index. Otherwise return -1. */
int get_file_index(const char *path);

int get_folder_index(const char *path);

struct file_list_entry* get_file_by_index(int index);
struct folder_list_entry* get_folder_by_index(int index);

void create_empty_directory_table();

/*
 * Set the folder name and get the parent. Currently that is root level only.
 *
 */
void add_directory(const char *dir_name);
void add_file(const char *file_name);

/*
 * Checks if the name given is in the directory list. If it is, return true, if not, return false.
 *
 */
int is_directory(const char *path);
int is_file(const char *path);
int get_file_size(const char *path);
int write_file(const char *path, const char *content, size_t size);
int set_accessed_time_to_now(const char *path);

#endif
