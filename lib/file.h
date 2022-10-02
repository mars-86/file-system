#ifndef _FILE_SYSTEM_LIB_FILE_INCLUDED_H_
#define _FILE_SYSTEM_LIB_FILE_INCLUDED_H_

#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _FILEBUF FILEBUF;

typedef enum _FILE_MODE {
	FILE_READ = 0x01,
	FILE_WRITE = 0x02,
	FILE_APPEND = 0x04,
	FILE_PLUS = 0x08,
	FILE_BINARY = 0x10
} file_mode_t;

extern int __cdecl file_read(const char *__restrict _path, char *__restrict _buff, size_t _size)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2);

extern int __cdecl file_write(const char *__restrict _path, const char *__restrict _content)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2);

extern int __cdecl file_open(FILE **__restrict _fd, const char *__restrict _path, file_mode_t _mode)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2);

extern int __cdecl file_open_fb(FILEBUF **__restrict _fb, const char *__restrict _path, file_mode_t _mode)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2);

extern int __cdecl is_file_open(FILE* _fd)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1);

extern int __cdecl is_file_open_fb(FILEBUF* _fb)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1);

extern size_t __cdecl file_size(const char *_path)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1);

extern size_t __cdecl file_size_fb(FILEBUF* _fb)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1);

extern const char __cdecl file_mode_fb(FILEBUF* _fb)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1);

extern const char __cdecl file_type_fb(FILEBUF* _fb)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1);

/* check */
extern void* __cdecl file_read_(char* _buff, size_t _size);

extern size_t __cdecl file_read_binary_(FILE *__restrict _fd, unsigned char*__restrict _buff, size_t _size)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2);

extern void* __cdecl file_find(const char* _name)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1);

extern int __cdecl file_create(const char *__restrict _path, unsigned char *__restrict _buff, size_t _size)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2);

extern int __cdecl file_copy(const char *__restrict _dest, const char *__restrict _src)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2);

extern int __cdecl file_move(const char *_dest, const char *_src)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2);

extern int __cdecl file_close(FILE* _fd)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1);

extern int __cdecl file_close_fb(FILEBUF* _fb)
	__MINGW_NOTHROW __MINGW_ATTRIB_NONNULL(1);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _FILE_SYSTEM_LIB_FILE_INCLUDED_H_ */
