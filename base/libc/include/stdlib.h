#ifndef __CRT_STDLIB_H
#define __CRT_STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((noreturn)) void abort();

// TODO: we do not want to define malloc() on libk

#ifdef __cplusplus
}
#endif

#endif