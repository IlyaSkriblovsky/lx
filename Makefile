SUBDIRS = lx test

all:
	@for i in $(SUBDIRS); do \
	(cd $$i; $(MAKE) $(MFLAGS) all); done

clean:
	@for i in $(SUBDIRS); do \
	(cd $$i; $(MAKE) $(MFLAGS) $@); done


.PHONY: all
