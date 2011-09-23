SOURCES = \
    Display.cpp     \
    Exception.cpp   \
    Log.cpp         \
    String.cpp      \
    Widget.cpp      \
    Window.cpp      \
    MainLoop.cpp    \
    Canvas.cpp      \
    TestWidget.cpp  \
    Image.cpp       \
    BorderImage.cpp


CFLAGS = -g `pkg-config --cflags x11`


OBJS = $(SOURCES:%.cpp=%.o)


all: liblx.a

liblx.a: $(OBJS)
	rm -f $@
	ar r $@ $^


.cpp.o:
	g++ -c $(CFLAGS) $< -o $@


depend: $(SOURCES)
	g++ -M -MM -MG -MP $(CFLAGS) $(SOURCES) >$@

include depend

clean:
	rm -f *.o depend *~ *.a
