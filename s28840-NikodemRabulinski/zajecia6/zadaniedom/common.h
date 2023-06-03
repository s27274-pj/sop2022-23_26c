#ifndef COMMON_H
#define COMMON_H

#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* TODO: Clang support? */
#ifdef __clang__
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif

typedef unsigned short bool;
#define true 1
#define false 0

#define BACKLOG 128
#define PORT 8080

static inline void sop_panic() {
  fprintf(stderr, "Fatal error, exiting\n");
  exit(1);
}

struct str_view {
  char *buf;
  size_t len;
};

struct header {
  struct str_view name, value;
};

static inline struct header make_header(char *name, char *value) {
  struct header res;

  res.name.buf = name;
  res.name.len = strlen(name);
  res.value.buf = value;
  res.value.len = strlen(value);

  return res;
}

#define define_arr(name, typ, ...)                                             \
  struct name {                                                                \
    typ *buf;                                                                  \
    size_t len, cap;                                                           \
  };                                                                           \
                                                                               \
  static inline int name##_init(size_t cap, struct name *out) {                \
    typ *buf = calloc(cap, sizeof(typ));                                       \
    if (buf == NULL)                                                           \
      return 1;                                                                \
    out->buf = buf;                                                            \
    out->len = 0;                                                              \
    out->cap = cap;                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  static inline int name##_extend(struct name *arr) {                          \
    size_t new_cap = arr->cap * 2;                                             \
    typ *new_buf = realloc(arr->buf, new_cap);                                 \
    if (new_buf == NULL)                                                       \
      return 1;                                                                \
    arr->buf = new_buf;                                                        \
    arr->cap = new_cap;                                                        \
    memset(&arr->buf[arr->len], 0, sizeof(typ) * (arr->cap - arr->len));       \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  static inline int name##_cat(struct name *arr, typ *other,                   \
                               size_t other_len) {                             \
    if (other_len > (arr->cap - arr->len)) {                                   \
      name##_extend(arr);                                                      \
    }                                                                          \
    memcpy(&arr->buf[arr->len], other, sizeof(typ) * other_len);               \
    arr->len += other_len;                                                     \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  static inline int name##_push(struct name *arr, typ val) {                   \
    return name##_cat(arr, &val, 1);                                           \
  }                                                                            \
                                                                               \
  static inline int name##_foreach(struct name *arr, int (*f)(typ *, void *),  \
                                   void *data) {                               \
    size_t i;                                                                  \
    int res;                                                                   \
    typ *curr;                                                                 \
    for (i = 0; i < arr->len; i += 1) {                                        \
      curr = &arr->buf[i];                                                     \
      res = (f)(curr, data);                                                   \
      if (res)                                                                 \
        return res;                                                            \
    }                                                                          \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  static inline int name##_clear(struct name *arr) {                           \
    arr->len = 0;                                                              \
    memset(arr->buf, 0, sizeof(typ));                                          \
    __VA_OPT__(name##_foreach(arr, __VA_ARGS__, NULL);)                        \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  static inline int name##_free(struct name *arr) {                            \
    __VA_OPT__(name##_foreach(arr, __VA_ARGS__, NULL);)                        \
    free(arr->buf);                                                            \
    return 0;                                                                  \
  }

define_arr(sop_str, char)
define_arr(sop_headers, struct header)

static inline struct sop_str sop_str_from_lit(const char *s) {
  struct sop_str res;
  size_t len = strlen(s);
  sop_str_init(len, &res);
  sop_str_cat(&res, (char*)s, len);
  return res;
}

#define SOP_STR(lit) sop_str_from_lit(lit)

#define STRF ".*s"
#define STRFARG(str) (int)str.len, str.buf

static inline struct str_view str_trim(struct str_view s) {
  struct str_view res = s;

  while (res.buf[0] == ' ' || res.buf[0] == '\t' || res.buf[0] == '\n') {
    res.len -= 1;
    res.buf += 1;
  }

  while (res.buf[res.len - 1] == ' ' || res.buf[res.len - 1] == '\t' ||
         res.buf[res.len - 1] == '\n') {
    res.len -= 1;
  }

  return res;
}

struct request {
  struct str_view method, target, version;
  struct sop_headers headers;
  /* TODO: Body? */
};

static inline int req_clear(struct request *req) { return sop_headers_clear(&req->headers); }

struct response {
  int code;
  struct sop_str status;
  struct sop_headers headers;
  struct sop_str body;
};

#endif
