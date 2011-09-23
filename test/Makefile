SOURCES = lxtest.cpp

CFLAGS = -I ../lx
LIBS = -lX11 -lXrender -lImlib2


OBJS = $(SOURCES:%.cpp=%.o)


all: lxtest

lxtest: $(OBJS) ../lx/liblx.a
	g++ $^ -o $@ $(LIBS)

.cpp.o:
	g++ -c $(CFLAGS) $< -o $@

depend: $(SOURCES)
	g++ -M -MM -MG -MP $(CFLAGS) $(SOURCES) >$@

include depend

clean:
	rm -f *.o lxtest *~ depend
