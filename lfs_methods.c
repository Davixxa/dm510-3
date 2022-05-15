#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>












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
    dir_table->file_entries[current_file_index]->last_modified_timestamp = time();
    dir_table->file_entries[current_file_index]->last_accessed_timestamp = time();
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


void export_fs_to_json() {
    // do export logic  
}


