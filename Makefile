SUBDIRS = tcp udp ssl encryption

install-dirs = $(patsubst %,install-%,$(SUBDIRS))
clean-dirs = $(patsubst %,clean-%,$(SUBDIRS))

install: $(install-dirs)
clean: $(clean-dirs)

install-%:
	make -C $$(echo $@ | sed 's/install-//') install

clean-%:
	make -C $$(echo $@ | sed 's/clean-//') clean

all:
	for dir in $(SUBDIRS); \
	do \
		make -C $$dir all; \
	done
