#ifndef _FILE_SYSTEM_LIB_FIO_INCLUDED_H_
#define _FILE_SYSTEM_LIB_FIO_INCLUDED_H_

#include <stdio.h>

#define __read_char_base(d) (fgetc(d))
#define __write_char_base(c, d) (fputc(c, d))

#define _read_char(c, d) (c = __read_char_base(d))
#define _read_uchar(c, d) ((c = (unsigned char) __read_char_base(d))

#define _write_char(c, d) (__write_char_base(c, d))
#define _write_uchar(c, d) (__write_char_base((unsigned char)c, d))

#define _read_char_neof(c, d) (_read_char(c, d) != EOF)

#endif /* _FILE_SYSTEM_LIB_FIO_INCLUDED_H_ */
