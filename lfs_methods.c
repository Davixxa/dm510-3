#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_TABLE_SIZE 8
#define NUM_DATA_POINTERS 27


typedef struct struct_table_entry {
    char filename[256]; // Filepath length
    lfs_file_id file_id;
    uint64_t file_size;
    lfs_sector_offset data_pointer[NUM_DATA_POINTERS]
};

typedef struct Directory_Table {

    struct struct_table_entry entries[DEFAULT_TABLE_SIZE];


};




struct Directory_Table *lfs_find_directory(const char *path, bool drop_filename)
{
    struct Directory_Table *dir_table = calloc(1, sizeof(struct Directory_Table));

}