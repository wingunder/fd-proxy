fd-proxy
========

Name
----
fd-proxy - glue for making a tcp proxy, using ucspi-tcp tools

Synopsis
--------

	fd-proxy

Description
-----------
fd-proxy is a very small program, written in C. Its purpose is to connect the
I/Os of a [tcpserver](http://cr.yp.to/ucspi-tcp/tcpserver.html) and
[tcpclient](http://cr.yp.to/ucspi-tcp/tcpclient.html) pair, from the
ucspi-tcp suite, in order to implement a TCP proxy. Setting up such a
proxy can be done in a singe line:

<code>
tcpserver -v 127.0.0.1 8000 tcpclient -v 127.0.0.1 22 ./fd-proxy 2>&1 |tai64n |tai64nlocal
</code>

The above proxy will relay all TCP traffic between port 22 and
port 8000 on localhost. So, as a simple test, you can run:

<code>
ssh -p 8000 localhost
</code>

The advantage of using the tcpserver and tcpclient programs is that all
the related [ucspi-tcp](http://cr.yp.to/ucspi-tcp.html) programs can
be used in combination with tcpserver and tcpclient. One can for example
define access restrictions with [tcprules](http://cr.yp.to/ucspi-tcp/tcprules.html),
define what needs to get looked up via DNS, etc.

The fd-proxy, tcpserver and tcpclient combination supply, even a non-privileged
user with a simple, fast and light-weight way to selectively forward TCP traffic.

At the moment, logging of the data, flowing between server and client is not possible.

Environment
-----------
fd-proxy honors _no_ environment variables.

Return Values
-------------
On success, 0 is returned. On error, errno is returned,
as set by the POSIX calls: open, read, write or select.

Also see
--------
[ucspi-tcp](http://cr.yp.to/ucspi-tcp.html),
[tcpserver](http://cr.yp.to/ucspi-tcp/tcpserver.html),
[tcpclient](http://cr.yp.to/ucspi-tcp/tcpclient.html),
[tcprules](http://cr.yp.to/ucspi-tcp/tcprules.html)

TODO
----
   - Make it possible to override the read buffer size with an environment variable.
   - Let fd-proxy take a single [cdb](http://cr.yp.to/cdb.html)-style
     file name as an argument. This file shall exist and either be
     empty (eg. /dev/null), or contain cdb-style rules. The rules
     can then be used to set up a proxy filter, eg:
     	 - 'ls:regexp' will log all responses that match the regexp, coming from the server-side.
     	 - 'lc:regexp' will log all requests that match the regexp, coming from the client-side.
     	 - 'is:regexp' ignore data that match the regexp, coming from the server.
     	 - 'ts:regexp' terminate the connection to a server that receives data that match the regexp.
   - Use the tcpserver and tcpclient environment variables in the logging, so that it is
     clear from where data comes, and where data goes to.
   - Build at least a Debian package for this.

Alternatives
------------
The only alternative that I could find for fd-proxy, is
[redirfd](http://www.skarnet.org.mirror.dogmap.org/software/execline/redirfd.html).
In order to get redirfd working, follow the instructions in this
[post](http://osdir.com/ml/djb.syslog/2003-05/msg00049.html). You'll need
to install [execline](http://skarnet.org/software/execline/execline-1.3.1.1.tar.gz)
as well.

Copyright
---------
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
