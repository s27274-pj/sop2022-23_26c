#include "handler.h"
#include "common.h"

struct response handle_request(__attribute__((unused)) struct request req) {
  struct response res;

  res.code = 200;
  res.status = SOP_STR("OK");
  res.body = SOP_STR("Example body");
  sop_headers_init(10, &res.headers);

  sop_headers_push(&res.headers, make_header("Content-Type", "text/plain"));

  return res;
}
