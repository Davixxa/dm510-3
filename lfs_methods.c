#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#define DEFAULT_TABLE_SIZE 256
#define NUM_DATA_POINTERS 27
#define DIRECTORY 1
#define FILE 2

typedef struct folder_list_entry {
    char foldername[256];
    uint64_t parent_folder_id; // NULL if root

    
};


typedef struct file_list_entry {
    char filename[256]; // Filepath length
    uint64_t parent_folder_id; // NULL if root
    uint64_t file_id;
    uint64_t file_size;
    time_t last_modified_timestamp;
    time_t last_accessed_timestamp;
    char file_contents[1024];
};

typedef struct Directory_Table {

    struct folder_list_entry folder_entries[DEFAULT_TABLE_SIZE];
    struct file_list_entry file_entries[DEFAULT_TABLE_SIZE];


};











char dir_list[256][256];
int current_dir_index = -1;

struct file_list_entry file_list[256];
int current_file_index = -1;

char file_content[256][256];
int current_file_content_index = -1;

struct Directory_Table dir_table;


int get_current_folder_index() {
    return current_dir_index;
}

int get_current_file_index() {
    return current_file_index;
}

/* Attempt to find the file in the file index array. If it's there, return the index. Otherwise return -1. */
int get_file_index(const char *path) {
    path++;

    for (int i = 0; i < current_file_index; i++) {
        if (strcmp(path, dir_table->file_entries[i]) == 0) {
            return i;
        }

    }

    return -1;

}

struct file_list_entry get_file_by_index(int index) {
    if (index > current_file_index) 
        return;

    return dir_table->file_entries[index];
}


struct folder_list_entry get_folder_by_index(int index) {
    if (index > current_dir_index) 
        return;

    return dir_table->folder_entries[index];
}

void create_empty_directory_table() {


}



/*
* Set the folder name and get the parent. Currently that is root level only.
*
*/
void add_directory(const char *dir_name) {
    current_dir_index++;
    
    strcpy(dir_table->folder_entries[current_dir_index], dir_name);
    dir_table->folder_entries[current_dir_index] = NULL; 


}


void add_file(const char *file_name) {

    current_file_index++;
    strcpy(dir_table->file_entries[current_file_index]->filename, file_name);
    dir_table->file_entries[current_file_index]->parent_folder_id = NULL; // Root only for now
    dir_table->file_entries[current_file_index]->file_size = 0;
    dir_table->file_entries[current_file_index]->last_modified_timestamp = time(NULL);
    dir_table->file_entries[current_file_index]->last_accessed_timestamp = time(NULL);
    strcpy(dir_table->file_entries[current_file_index]->file_contents, "");


}





/* 
* Checks if the name given is in the directory list. If it is, return true, if not, return false.
*
*/
int is_directory(const char *path) {
    path++; // Eliminate first / in path

    for ( int i = 0; i < current_dir_index; i++) {
        struct folder_list_entry current_folder = dir_table->folder_entries[i];
        if (strcmp(path, current_folder->foldername) == 0) {
            return 1;
        }

    }

    return 0;
}


int is_file(const char *path) {
    path++; // Eliminate /

    for (int i = 0; i < current_file_index; i++) {
        struct file_list_entry current_file = dir_table->file_entries[i];
        if (strcmp(path, current_file->filename) == 0) {
            return 1;
        }
    }

    return 0;

}


int get_file_size(const char *path) {

        path++; // Eliminate /

    for (int i = 0; i < current_file_index; i++) {
        struct file_list_entry current_file = dir_table->file_entries[i];
        if (strcmp(path, current_file->filename) == 0) {
            return current_file->file_size;
        }
    }

    return 0;

}


void write_file(const char *path, const char *content) {
    int file_index = get_file_index(path);

    if (file_index == -1) {
        return -ENOENT;
    }

    strcpy(dir_table->file_entries[file_index]->file_contents, content);
    dir_table->file_entries[file_index]_file_size = strlen(content));

}






void export_fs_to_json() {
    // do export logic  
}


