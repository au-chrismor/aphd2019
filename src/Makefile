CC=gcc
OPENVINODIR=/opt/intel/2019_r1/openvino
INCDIR=$(OPENVINODIR)/opencv/include
LIBDIR=$(OPENVINODIR)/opencv/lib
LIBS=-lstdc++ -lpthread -lX11 -lopencv_core -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs -lopencv_highgui -lopencv_photo -lopencv_objdetect -lopencv_dnn
DEFS+=-D_HAS_GUI
DEFS+=-D_DEBUG
GLOBALS=Makefile aphd.hpp

all:	main

main:	main.cpp runthread.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o main main.cpp runthread.cpp $(LIBS)

