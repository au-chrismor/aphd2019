CC=gcc
OPENVINODIR=/opt/intel/2019_r1.1/openvino
INCDIR=$(OPENVINODIR)/opencv/include
LIBDIR=$(OPENVINODIR)/opencv/lib
LIBS=-lstdc++ -lopencv_core -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs
DEFS+=-D_HAS_GUI
GLOBALS=Makefile

main:	main.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o main main.cpp $(LIBS)

