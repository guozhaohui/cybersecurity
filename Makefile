SUBDIRS = tcp udp ssl encryption digest

.PHONY: all
all: $(SUBDIRS)

.PHONY: install
install: all

install-dirs = $(patsubst %,install-%,$(SUBDIRS))
clean-dirs = $(patsubst %,clean-%,$(SUBDIRS))

install: $(install-dirs)

.PHONY: clean
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
