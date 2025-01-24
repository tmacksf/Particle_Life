#ifndef LEAK_HPP
#define LEAK_HPP

#include <cstdlib>
#include <hash_map>

typedef struct alloc {
  const char *file;
  const int line;
} alloc;

static unsigned long id = 0;

#ifdef unix
static __gnu_cxx::hash_map<unsigned long, alloc> m;
#endif

inline void *operator new(size_t size, const char *file, int line) {
  return malloc(size);
}

inline void *operator new[](size_t size, const char *file, int line) {
  return malloc(size);
}

inline void operator delete(void *p, const char *file, int line) { 
  m.find();

  free(p); 
}

#define DEBUG_NEW new (__FILE__, __LINE__)
#define new DEBUG_NEW

#endif
