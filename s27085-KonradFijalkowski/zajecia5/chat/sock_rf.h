#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/un.h>

#define SV_SOCK_PATH "/tmp/zadanie6.sock"
#define BUF_SIZE 256
#define BACKLOG 5