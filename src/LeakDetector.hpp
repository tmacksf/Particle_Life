#ifndef LEAK_HPP
#define LEAK_HPP

#include <cstdlib>

void *operator new(size_t size, const char *file, int line);
void *operator new[](size_t size, const char *file, int line);
#define DEBUG_NEW new (__FILE__, __LINE__)
#define new DEBUG_NEW

#endif
