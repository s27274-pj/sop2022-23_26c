/* clang-format off */
/*----------------------------------------------------------------------------------------------------------*\
 |                                                                                                          |
 | Rozwiń/napisz serwer HTTP tak, aby nadawał się do udostępniania strony WWW. Serwer powinien obsługiwać:  |
 |     lista zabronionych adresów                                                                           |
 |     zapis logów zdarzeń (wraz z informacją kto się podłączył)                                            |
 |                                                                                                          |
 | Dodatkowo niech serwer pozwala na tworzenie wirtualnych hostów.                                          |
 | Niech serwer nie blokuje się w sytuacji kiedy jakiś klient przeciąga połączenie                          |
 | (aby nie blokowało ono innych połączeń).                                                                 |
 |                                                                                                          |
\*----------------------------------------------------------------------------------------------------------*/
/* clang-format on */
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "common.h"
#include "handler.h"

char *find_part(char *buf, struct sop_str *str, bool *res) {
  char *crlf;
  size_t len;

  crlf = strstr(buf, "\r\n\r\n");
  if (crlf) {
    crlf[0] = 0;
    *res = true;
    sop_str_cat(str, buf, crlf - buf);
    return crlf + 2;
  } else {
    len = strlen(buf);
    sop_str_cat(str, buf, len);
    return buf + len;
  }
}

struct sop_str_iter {
  size_t pos;
  struct sop_str *s;
};

void iter_start(struct sop_str_iter *iter, struct sop_str *s) {
  iter->pos = 0;
  iter->s = s;
}

int iter_next(struct sop_str_iter *iter, struct str_view *out) {
  char *start, *end;
  size_t sub_len;

  sub_len = iter->s->len - iter->pos;
  if (sub_len <= 0)
    return 1;
  start = iter->s->buf + iter->pos;
  end = strnstr(start, "\r\n", sub_len);

  out->buf = start;
  if (end) {
    out->len = end - start;
    iter->pos += out->len + 2;
  } else {
    out->len = sub_len;
    iter->pos = iter->s->len;
  }

  return 0;
}

struct str_view_iter {
  size_t pos;
  struct str_view s;
};

void view_iter_start(struct str_view_iter *iter, struct str_view s) {
  iter->pos = 0;
  iter->s = s;
}

int view_iter_next(struct str_view_iter *iter, struct str_view *out) {
  char *start, *end;
  size_t sub_len;

  sub_len = iter->s.len - iter->pos;
  if (sub_len <= 0)
    return 1;
  start = iter->s.buf + iter->pos;
  end = strnstr(start, " ", sub_len);

  out->buf = start;
  if (end) {
    out->len = end - start;
    iter->pos += out->len + 1;
  } else {
    out->len = sub_len;
    iter->pos = iter->s.len;
  }

  return 0;
}

struct header str_to_head(struct str_view str) {
  struct header res;
  char *colon;

  colon = strnstr(str.buf, ":", str.len);

  if (!colon)
    sop_panic();

  res.name.buf = str.buf;
  res.name.len = colon - str.buf;

  res.value.buf = colon + 1;
  res.value.len = str.len - res.name.len - 1;

  res.name = str_trim(res.name);
  res.value = str_trim(res.value);

  return res;
}

int send_header(struct header *head, void *client_fd_ptr) {
  int client = *(int *)client_fd_ptr;
  dprintf(client, "%" STRF ": %" STRF "\r\n", STRFARG(head->name),
          STRFARG(head->value));
  return 0;
}

int main() {
  struct sockaddr_in addr;
  struct sop_str req_str;
  struct sop_str_iter iter;
  struct str_view_iter view_iter;
  struct request req;
  struct str_view tmp;
  struct response resp;
  bool req_end;
  char buf[129];
  char *bufptr;
  int sock;
  int res;
  int client;

  sock = socket(AF_INET, SOCK_STREAM, 0);

  addr.sin_family = AF_INET;
  /* TODO: Configurable port */
  addr.sin_port = htons(PORT);
  /* TODO: Configurable address */
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* TODO: Error handling */
  res = bind(sock, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  res = listen(sock, BACKLOG);
  res = sop_str_init(128, &req_str);
  res = sop_headers_init(10, &req.headers);

  for (;;) {
    client = accept(sock, NULL, NULL);

    if (client == -1)
      sop_panic();

#ifndef SINGLE_PROCESS
    switch (fork()) {
    case -1:
      sop_panic();
    case 0:
      break;
    default:
      continue;
    }
#endif

    signal(SIGALRM, exit);

    res = sop_str_clear(&req_str);
    res = req_clear(&req);
    req_end = false;
    bufptr = buf;

    alarm(60 * 2);
    while ((res = recv(client, buf, 128, 0)) > 0) {
      alarm(0);
      buf[res] = 0;
      if (!req_end) {
        bufptr = find_part(bufptr, &req_str, &req_end);
      }

      if (req_end)
        break;
      else
        alarm(60 * 2);
    }

    iter_start(&iter, &req_str);

    iter_next(&iter, &tmp);
    view_iter_start(&view_iter, tmp);
    view_iter_next(&view_iter, &req.method);
    view_iter_next(&view_iter, &req.target);
    view_iter_next(&view_iter, &req.version);

    while (iter_next(&iter, &tmp) == 0) {
      sop_headers_push(&req.headers, str_to_head(tmp));
    }

    resp = handle_request(req);

    dprintf(client,
            "HTTP/1.1 %d %" STRF "\r\n"
            "Content-Length: %zu\r\n",
            resp.code, STRFARG(resp.status), resp.body.len);
    sop_headers_foreach(&resp.headers, send_header, &client);
    dprintf(client, "\r\n%" STRF, STRFARG(resp.body));
    close(client);

#ifndef SINGLE_PROCESS
    return 0;
#endif
  }

  sop_str_free(&req_str);

  return 0;
}
