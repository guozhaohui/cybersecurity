SUBDIRS = tcp udp ssl

all:
	for d in $(SUBDIRS); \
	do \
		(cd $$d && (MAKE) $(MFLAGS) all); \
	done
