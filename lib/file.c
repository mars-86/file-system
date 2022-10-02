#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "fio.h"

struct _FILEBUF {
    FILE *fd;
    char *name;
    char mode;
    char type;
    size_t size;
};

static void _file_get_mode(int _mode, char *_mode_str)
{
    switch (_mode) {
    case FILE_READ:
        _mode_str[0] = 'r';
        break;
    case FILE_WRITE:
        _mode_str[0] = 'w';
        break;
    case FILE_APPEND:
        _mode_str[0] = 'a';
        break;
    case FILE_READ | FILE_PLUS:
        _mode_str[0] = 'r', _mode_str[1] = '+';
        break;
    case FILE_WRITE | FILE_PLUS:
        _mode_str[0] = 'w', _mode_str[1] = '+';
        break;
    case FILE_APPEND | FILE_PLUS:
        _mode_str[0] = 'a', _mode_str[1] = '+';
        break;
    case FILE_READ | FILE_BINARY:
        _mode_str[0] = 'r', _mode_str[1] = 'b';
        break;
    case FILE_WRITE | FILE_BINARY:
        _mode_str[0] = 'w', _mode_str[1] = 'b';
        break;
    case FILE_APPEND | FILE_BINARY:
        _mode_str[0] = 'a', _mode_str[1] = 'b';
        break;
    default:
        _mode_str[0] = 'r';
    }
}

static int _file_open_base(FILE **__restrict _fd, const char *__restrict _path, const char *__restrict _mode)
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
    if (!(*_fd = fopen(_path, _mode)))
        return 1;
    return 0;
}

int file_read(const char *_path, char *_buff, size_t _size)
{
    FILE *fd;
    if (_file_open_base(&fd, _path, "r") > 0)
        return 1;

    char c; int s;
    for(s = 0; _read_char_neof(c, fd) && s < _size; ++s, ++_buff)
        *_buff = c;
    *_buff = '\0';
    file_close(fd);

    return 0;
}

int file_write(const char *_path, const char *_content)
{
    FILE *fd;
    if (_file_open_base(&fd, _path, "w") > 0)
        return 1;

    while(*_content != '\0')
        _write_char(*_content++, fd);
    file_close(fd);
    return 0;
}

int file_read_f(const char *_path, char *_buff, size_t _size, const char *_encoding)
{
    FILE *fd;
    _file_open_base(&fd, _path, "r");
    return 0;
}

int file_write_f(const char *_path, const char *_content, const char *_encoding)
{
    FILE *fd;
    _file_open_base(&fd, _path, "r");
    return 0;
}

int file_open(FILE **_fd, const char *_path, file_mode_t _mode)
{
    char _mode_s[3];
    _file_get_mode(_mode, _mode_s);
    return _file_open_base(&(*_fd), _path, _mode_s);
}

int is_file_open(FILE *_fd)
{
    return _fd == NULL ? 0 : 1;
}

int is_file_open_fb(FILEBUF *_fb)
{
    return _fb->fd == NULL ? 0 : 1;
}

size_t file_size_d(FILE *_fd)
{
    long fsize;
    fseek(_fd, 0, SEEK_END);
    fsize = ftell(_fd);
    fseek(_fd, SEEK_END, 0);
    return fsize;
}

size_t file_size(const char *_path)
{
    FILE *f;
    long fsize;
    file_open(&f, _path, FILE_READ | FILE_BINARY);
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    file_close(f);
    return fsize;
}

size_t file_size_fb(FILEBUF* _fb)
{
    return _fb->size;
}

int file_open_fb(FILEBUF **_fb, const char *_path, file_mode_t _mode)
{
    if (!(*_fb = (FILEBUF *)malloc(sizeof(FILEBUF)))) {
        perror("malloc");
        return 1;
    }
    char _mode_s[3];
    _file_get_mode(_mode, _mode_s);
    (*_fb)->fd = NULL;
    if (_file_open_base(&((*_fb)->fd), _path, _mode_s) != 0) {
        free(*_fb);
        return 1;
    }
    //fb->name = "";
    (*_fb)->type = 'b';
    (*_fb)->mode = 'r';
    (*_fb)->size = file_size_d((*_fb)->fd);

    return 0;
}

const char file_mode_fb(FILEBUF* _fb)
{
    return _fb->mode;
}

const char file_type_fb(FILEBUF* _fb)
{
    return _fb->type;
}

size_t file_read_binary_(FILE *_fd, unsigned char *_buff, size_t _size)
{
    int i, c;
    for (i = 0; _read_char_neof(c, _fd) && i < _size; ++i)
        *(_buff + i) = (unsigned char)c;
    return i; // bytes read
}

void* file_find(const char* _search)
{
    return NULL;
}

int file_create(const char *_path, unsigned char *_buff, size_t _size)
{
    FILE *f;
    int i;
    if (file_open(&f, _path, FILE_WRITE | FILE_BINARY) > 0) return 1;
    for (i = 0; i < _size; ++i)
        _write_char(*(_buff + i), f);
    file_close(f);
    return 1;
}

int file_copy(const char *_dest, const char *_src)
{
    FILE *fs, *fd;
    int c;
    if (file_open(&fs, _src, FILE_READ | FILE_BINARY) > 0 || file_open(&fd, _dest, FILE_WRITE | FILE_BINARY) > 0)
        return 1;
    while (_read_char_neof(c, fs)) _write_uchar(c, fs);
    file_close(fd), file_close(fs);
    return 0;
}

int file_move(const char *_dest, const char *_src)
{
    return file_copy(_dest, _src);
}

int file_close(FILE *_fd)
{
    return fclose(_fd);
}

int file_close_fb(FILEBUF *_fb)
{
    if (fclose(_fb->fd) != 0) {
        free(_fb);
        return -1;
    }
    free(_fb);
    return 0;
}
