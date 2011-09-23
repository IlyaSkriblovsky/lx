SOURCES = lxtest.cpp

CFLAGS = -I.. `pkg-config --cflags x11 xrender imlib2`
LIBS = `pkg-config --libs x11 xrender imlib2`


OBJS = $(SOURCES:%.cpp=%.o)


all: lxtest

lxtest: $(OBJS) ../lx/liblx.a ../widgets/liblxwidgets.a
	g++ $^ -o $@ $(LIBS)

.cpp.o:
	g++ -c $(CFLAGS) $< -o $@

depend: $(SOURCES)
	g++ -M -MM -MG -MP $(CFLAGS) $(SOURCES) >$@

include depend

clean:
	rm -f *.o lxtest *~ depend
