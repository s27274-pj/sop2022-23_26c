#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#ifdef __linux__
#include <bsd/string.h>
#endif

#define _STRINGIFY(x) #x

#define BACKLOG 128
#define BUFSZ 1024
#define BUFSZ_STR _STRINGIFY(1023)

const char *path = "/tmp/zadanie6.sock";
char buf[BUFSZ + 1];

int read_msg(int fd) {
  int len; 
  printf("Them: ");
  fflush(stdout);

  /* TODO: Messages longer than BUFSZ */
  len = read(fd, buf, BUFSZ);

  if (len == 0)
    return -1;

  buf[len] = '\0';
  printf("%s\n", buf);
  fflush(stdout);

  return 0;
}

int send_msg(int fd) {
  int len;

  printf("You: ");
  fflush(stdout);

  scanf("%" BUFSZ_STR "s", buf);
  len = strlen(buf);

  if (write(fd, buf, len + 1) == -1)
    return -1;

  return 0;
}

int server(const struct sockaddr_un *addr) {
  int sock;
  int client;
  int res;

  sock = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock == -1) {
    fprintf(stderr, "[ERROR] Socket error\n");
    return 1;
  }

  /* TODO: Error handling */
  res = bind(sock, (const struct sockaddr *)addr, sizeof(struct sockaddr_un));
  res = listen(sock, BACKLOG);

  printf("[INFO] Socket started, waiting for connection...\n");
  fflush(stdout);

  client = accept(sock, NULL, NULL);
  printf("[INFO] Clinet joined, waiting for their message...\n");

  for (;;) {
    if (read_msg(client) || send_msg(client))
      break;
  }

  printf("[INFO] Client exited, closing the server\n");
  close(sock);

  return 0;
}

int client(const struct sockaddr_un *addr) {
  int sock;

  sock = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock == -1) {
    fprintf(stderr, "[ERROR] Socket error\n");
    return 1;
  }

  printf("[INFO] Trying to connect to the server\n");

  if(connect(sock, (const struct sockaddr *)addr, sizeof(struct sockaddr_un))) {
    switch (errno) {
      /* File does not exist. */
      case ENOENT:
      /* Connection refused means no server is listening. */
      case ECONNREFUSED:
        printf("[INFO] Server doesn't exist\n");
        /* Return -1 to signal that the server should be started instead. */
        close(sock);
        unlink(path);
        return -1;
      default:
        return errno;
    }
  }

  printf("[INFO] Succesfully connected\n");

  for (;;) {
    if (send_msg(sock) || read_msg(sock))
      break;
  }

  printf("[INFO] Server closed, exiting\n");
  close(sock);

  return 0;
}

int main() {
  const uint8_t path_len = strlen(path);
  struct sockaddr_un addr;
  int res;

  addr.sun_family = AF_UNIX;
  strlcpy(addr.sun_path, path, sizeof(addr.sun_path));
  addr.sun_len = path_len;

  /* Try to run the client code and hope for the best */
  res = client(&addr);
  if (res == -1)
    /* Running the client failed which means the server is not listening */
    return server(&addr);
  else
    return res;
}
