/* -*- mode:c -*-

 Copyright (c) 2013 MIYOKAWA, Nobuyoshi (http://www.tempus.org/)

 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define PORT 8080
#define HEADER \
  "HTTP/1.1 200 OK\r\n" \
  "Content-Type: text/plain\r\n" \
  "Connection: close\r\n" \
  "Content-Length: 31\r\n\r\n"
#define HEADER_SLEEP 3
#define BODY1 "hello, world\r\n"
#define BODY1_SLEEP 3
#define BODY2 "good-bye, world\r\n"
#define BODY2_SLEEP 3

static int s, ss;

void
handler(int signum)
{
  close(s);
  close(ss);
}

int
server()
{
  struct sockaddr_in addr;
  const int on = 1;
  struct sigaction sa;

  memset( &sa, 0, sizeof(struct sigaction) );
  sa.sa_handler = handler;
  sigaction(SIGPIPE, &sa, NULL);

  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    return -1;
  }
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

  addr.sin_len = sizeof(addr);
  addr.sin_family = PF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(s, (struct sockaddr *)&addr, sizeof(addr))
      || listen(s, 5)
      || (ss = accept(s, NULL, NULL)) == -1) {
    return -1;
  }
  do {
    char buf[BUFSIZ];
    ssize_t sz = read(ss, buf, BUFSIZ);
    if (sz <= 0
        || strstr(buf, "\r\n\r\n")
        || (buf[0] == '\r' && buf[1] == '\n')) {
      break;
    }
  } while (1);

  sleep(HEADER_SLEEP);
  write(ss, HEADER, sizeof(HEADER)-1);
  sleep(BODY1_SLEEP);
  write(ss, BODY1, sizeof(BODY1)-1);
  sleep(BODY2_SLEEP);
  write(ss, BODY2, sizeof(BODY2)-1);

  close(ss);
  close(s);

  return 0;
}

/* EOF */
