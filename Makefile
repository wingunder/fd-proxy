all: fd-proxy

clean:
	rm -rf fd-proxy fd-proxy.html rules.cdb

fd-proxy.html: README.md
	pandoc -f markdown -t html $< >$@

fd-proxy: fd-proxy.c
	gcc -Wall -O3 -o $@ $<

rules.cdb: rules.txt
	cat $< |tcprules $@ tmp

test: fd-proxy rules.cdb
	@echo "\tYou can test the proxy, by running: ssh -p 8000 127.0.0.1"
	@echo "\tHit CTRL-C to terminate."
	tcpserver -p -R -x rules.cdb -v 127.0.0.1 8000 tcpclient -v 127.0.0.1 22 ./fd-proxy 2>&1 |tai64n |tai64nlocal
