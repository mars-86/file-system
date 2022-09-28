#include <stdio.h>
#include <stdlib.h>
#include "file_manip.h"

struct _FILEBUF {
    FILE *fd;
    char *name;
    char mode;
    char type;
    size_t size;
};

void _file_get_mode(int mode, char *mode_str)
{
    switch (mode) {
    case FILE_MANIP_READ:
        mode_str[0] = 'r';
        break;
    case FILE_MANIP_WRITE:
        mode_str[0] = 'w';
        break;
    case FILE_MANIP_APPEND:
        mode_str[0] = 'a';
        break;
    case FILE_MANIP_READ | FILE_MANIP_PLUS:
        mode_str[0] = 'r', mode_str[1] = '+';
        break;
    case FILE_MANIP_WRITE | FILE_MANIP_PLUS:
        mode_str[0] = 'w', mode_str[1] = '+';
        break;
    case FILE_MANIP_APPEND | FILE_MANIP_PLUS:
        mode_str[0] = 'a', mode_str[1] = '+';
        break;
    case FILE_MANIP_READ | FILE_MANIP_BINARY:
        mode_str[0] = 'r', mode_str[1] = 'b';
        break;
    case FILE_MANIP_WRITE | FILE_MANIP_BINARY:
        mode_str[0] = 'w', mode_str[1] = 'b';
        break;
    case FILE_MANIP_APPEND | FILE_MANIP_BINARY:
        mode_str[0] = 'a', mode_str[1] = 'b';
        break;
    default:
        mode_str[0] = 'r';
    }
}

int _file_open_base(FILE **fd, const char *__restrict__ path, const char *__restrict__ mode)
{
/*
#ifdef _WIN32
    if ((fopen_s(&(*fd), path, mode)) != 0)
        return 1;
#else
    if (!(*fd = fopen(path, mode)))
        return 1;
#endif // __WIN32
*/
    if (!(*fd = fopen(path, mode)))
        return 1;
    return 0;
}

int file_read(const char *__restrict__ path, char *__restrict__ buff, size_t size)
{
    FILE *fd;
    if (_file_open_base(&fd, path, "r") > 0)
        return 1;

    char c; int s;
    for(s = 0; (c = fgetc(fd)) != EOF && s < size; ++s, ++buff)
        *buff = c;
    *buff = '\0';
    file_close(fd);

    return 0;
}

int file_write(const char *__restrict__ path, const char *__restrict__ content)
{
    FILE *fd;
    if (_file_open_base(&fd, path, "w") > 0)
        return 1;

    while(*content != '\0')
        fputc(*content++, fd);
    file_close(fd);
    return 0;
}

int file_read_f(const char *__restrict__ path, char *__restrict__ buff, size_t size, const char *__restrict__ encoding)
{
    FILE *fd;
    _file_open_base(&fd, path, "r");
    return 0;
}

int file_write_f(const char *__restrict__ path, const char *__restrict__ content, const char *__restrict__ encoding)
{
    FILE *fd;
    _file_open_base(&fd, path, "r");
    return 0;
}

int file_open(FILE **fd, const char *path, int mode)
{
    char _mode_s[3];
    _file_get_mode(mode, _mode_s);
    return _file_open_base(&(*fd), path, _mode_s);
}

int is_file_open(FILE *fd)
{
    return fd == NULL ? 0 : 1;
}

int is_file_open_fb(FILEBUF *fb)
{
    return fb->fd == NULL ? 0 : 1;
}

size_t file_size_d(FILE *fd)
{
    long fsize;
    fseek(fd, 0, SEEK_END);
    fsize = ftell(fd);
    fseek(fd, SEEK_END, 0);
    return fsize;
}

size_t file_size(const char *path)
{
    FILE *f;
    long fsize;
    file_open(&f, path, FILE_MANIP_READ | FILE_MANIP_BINARY);
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    file_close(f);
    return fsize;
}

size_t file_size_fb(FILEBUF* fb)
{
    return fb->size;
}

int file_open_fb(FILEBUF **fb, const char *path, int mode)
{
    if (!(*fb = (FILEBUF *)malloc(sizeof(FILEBUF)))) {
        perror("malloc");
        return 1;
    }
    char _mode_s[3];
    _file_get_mode(mode, _mode_s);
    (*fb)->fd = NULL;
    if (_file_open_base(&((*fb)->fd), path, _mode_s) != 0) {
        free(*fb);
        return 1;
    }
    //fb->name = "";
    (*fb)->type = 'b';
    (*fb)->mode = 'r';
    (*fb)->size = file_size_d((*fb)->fd);

    return 0;
}

const char file_mode_fb(FILEBUF* fb)
{
    return fb->mode;
}

const char file_type_fb(FILEBUF* fb)
{
    return fb->type;
}

size_t file_read_binary_(FILE *fd, unsigned char *fbuff, long buff_size)
{
    int i, c;
    for (i = 0; (c = fgetc(fd)) != EOF && i < buff_size; ++i)
        *(fbuff + i) = (unsigned char)c;
    return i; // bytes read
}

void* file_find(const char* search)
{
    return NULL;
}

int file_create(const char *path, unsigned char *buff, size_t size)
{
    FILE *f;
    int i;
    if (file_open(&f, path, FILE_MANIP_WRITE | FILE_MANIP_BINARY) > 0) return 1;
    for (i = 0; i < size; ++i)
        fputc(buff[i], f);
    file_close(f);
    return 1;
}

int file_dup(const char *__restrict__ path_dest, const char *__restrict__ path_src)
{
    FILE *fs, *fd;
    int c;
    if (file_open(&fs, path_src, FILE_MANIP_READ | FILE_MANIP_BINARY) > 0) return 1;
    if (file_open(&fd, path_dest, FILE_MANIP_WRITE | FILE_MANIP_BINARY) > 0) return 1;
    while ((c = fgetc(fs)) != EOF) fputc((unsigned char)c, fd);
    file_close(fd);
    file_close(fs);
    return 1;
}

int file_close(FILE *fd)
{
    return fclose(fd);
}

int file_close_fb(FILEBUF *fb)
{
    if (fclose(fb->fd) != 0) {
        free(fb);
        return -1;
    }
    free(fb);
    return 0;
}
