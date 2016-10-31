all: suspend vlock

suspend:
	gcc suspend-to-ram.c -o suspend-to-ram -O2 -W -Wall
	chown root:maxux suspend-to-ram
	chmod +s suspend-to-ram

vlock:
	gcc vlock.c -o vlock -O2 -W -Wall
	chown root:maxux vlock
	chmod +s vlock

clean:
	rm -f vlock suspend-to-ram
