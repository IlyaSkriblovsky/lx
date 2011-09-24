SOURCES = \
    ScalableButton.cpp  \
    Slider.cpp          \
    SimpleButton.cpp


CFLAGS = -g -I.. `pkg-config --cflags x11`

OBJS = $(SOURCES:%.cpp=%.o)

all: liblxwidgets.a

liblxwidgets.a: $(OBJS)
	rm -f $@
	ar r $@ $^


.cpp.o:
	g++ -c $(CFLAGS) $< -o $@


depend: $(SOURCES)
	g++ -M -MM -MG -MP $(CFLAGS) $(SOURCES) >$@

include depend

clean:
	rm -f *.o depend *~ *.a
