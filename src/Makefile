CC=gcc
OPENVINODIR=/opt/intel/2019_r1.1/openvino
INCDIR=$(OPENVINODIR)/opencv/include
LIBDIR=$(OPENVINODIR)/opencv/lib
LIBS=-lstdc++ -lpthread -lopencv_core -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs
DEFS+=-D_HAS_GUI
DEFS+=-D_DEBUG
GLOBALS=Makefile aphd.hpp

all:	threadtester main

main:	main.cpp runthread.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o main main.cpp runthread.cpp $(LIBS)

threadtester:	threadtester.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o threadtester threadtester.cpp $(LIBS)
