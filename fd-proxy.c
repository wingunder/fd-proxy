/*
Copyright (C) 2014 Pieter du Preez <pdupreez+remove_this_and_the_preceeding_plus@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

This program does the following:
- copy data from fd 0 to fd 6
- copy data from fd 7 to fd 1

*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int copyData(int fromFd, int toFd, char* buf, ssize_t len) {
  int retVal = -1;
  ssize_t rdSize = read(fromFd, buf, len);
  if (rdSize > 0) {
    ssize_t wrSize = write(toFd, buf, rdSize);
    if (wrSize == -1) {
      fprintf(stderr, "fd-proxy: write failure errno=%d %s\n", errno, strerror(errno));
    }
    else if (wrSize != rdSize) {
      fprintf(stderr, "fd-proxy: wrote only %lu of %lu bytes.", wrSize, rdSize);
    }
    else if (wrSize > 0) {
      retVal = 0;
    }
  }
  else if (rdSize == -1) {
    fprintf(stderr, "fd-proxy: read failure errno=%d %s\n", errno, strerror(errno));
  }
  return retVal;
}

int main(void) {
  const int bufSize = 2048;
  fd_set fdSet;
  FD_ZERO(&fdSet);
  FD_SET(0, &fdSet);
  FD_SET(7, &fdSet);
  const int max_fd = 7;
  char buf[bufSize];
  while (1) {
    fd_set dup = fdSet;
    if (select(max_fd+1, &dup, NULL, NULL, NULL) <= 0) {
      fprintf(stderr, "fd-proxy: select failure errno=%d %s\n", errno, strerror(errno));
      break;
    }
    else {
      if ((FD_ISSET(0, &dup) && copyData(0, 6, buf, bufSize)) ||
	  (FD_ISSET(7, &dup) && copyData(7, 1, buf, bufSize))) {
	break;
      }
    }
  }
  return errno;
}
