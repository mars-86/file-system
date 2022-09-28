#ifndef _FILE_SYSTEM_LIB_FILE_MANIP_INCLUDED_H_
#define _FILE_SYSTEM_LIB_FILE_MANIP_INCLUDED_H_

#include <stdio.h>

typedef struct _FILEBUF FILEBUF;
typedef struct FILEBUF** FILEBUFL;

enum _FILE_MANIP_MODES {
	FILE_MANIP_READ = 0x01,
	FILE_MANIP_WRITE = 0x02,
	FILE_MANIP_APPEND = 0x04,
	FILE_MANIP_PLUS = 0x08,
	FILE_MANIP_BINARY = 0x10
};

int file_read(const char *__restrict__ path, char *__restrict__ buff, size_t size);
int file_write(const char *__restrict__ path, const char *__restrict__ content);
int file_open(FILE** fd, const char* path, int mode);
int file_open_fb(FILEBUF** fb, const char* path, int mode);
int is_file_open(FILE* fd);
int is_file_open_fb(FILEBUF* fb);
size_t file_size(const char *path);
size_t file_size_fb(FILEBUF* fb);
const char file_mode_fb(FILEBUF* fb);
const char file_type_fb(FILEBUF* fb);
void* file_read_(char* buff, long buff_size);
size_t file_read_binary_(FILE* fd, unsigned char* fbuff, long buff_size);
void* file_find(const char* search);
int file_create(const char *path, unsigned char *buff, size_t size);
int file_dup(const char *__restrict__ path_dest, const char *__restrict__ path_src);
int file_close(FILE* fd);
int file_close_fb(FILEBUF* fb);

#endif // _FILE_SYSTEM_LIB_FILE_MANIP_INCLUDED_H_
