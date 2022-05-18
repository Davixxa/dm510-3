#ifndef LFS_METHODS_H
#define LFS_METHODS_H

#include <stdint.h>
#include <time.h>

// Amount of files and folders the file system supports.
#define DEFAULT_TABLE_SIZE 256
#define MAX_FILE_SIZE 1024


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
    char file_contents[MAX_FILE_SIZE];
};

struct Directory_Table {
    struct folder_list_entry folder_entries[DEFAULT_TABLE_SIZE];
    struct file_list_entry file_entries[DEFAULT_TABLE_SIZE];
};

/* Confusingly named, it gets the current largest set index value of the folder array. */
int get_current_folder_index();

/* Confusingly named, it gets the current largest set index value of the file array. */
int get_current_file_index();

/* Attempt to find the file in the file index array. If it's there, return the index. Otherwise return -1. */
int get_file_index(const char *path);

/* Attempt to find the file in the folder index array. If it's there, return the index. Otherwise return -1. */
int get_folder_index(const char *path);


/* 
* Return pointer to file at given index in the folder array.
* If out of bounds, return a null pointer.
*/
struct file_list_entry* get_file_by_index(int index);

/* 
* Return pointer to folder at given index in the folder array.
* If out of bounds, return a null pointer.
*/
struct folder_list_entry* get_folder_by_index(int index);


/* Set the folder name and get the parent. Currently that is root level only. */
void add_directory(const char *dir_name);

/* Creates a new empty file with the given name. */
void add_file(const char *file_name);

/* Checks if the name given is in the directory list. If it is, return true, if not, return false. */
int is_directory(const char *path);

/* Checks if the name given is in the files list. If it is, return true. If not, false. */
int is_file(const char *path);

/* Auxilliary function to help with displaying values without having to pass through the entire file.*/
int get_file_size(const char *path);

/* Writes size amount of bytes from buffer "content" to file at "path". */
int write_file(const char *path, const char *content, size_t size);

/* Auxillary function, used as a quick shortcut to set accessed time when reading a file. */
int set_accessed_time_to_now(const char *path);

#endif
