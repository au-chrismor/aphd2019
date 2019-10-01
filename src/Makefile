CC=gcc -std=c++11 -std=gnu++11
OPENVINODIR=/opt/intel/2019_r1/openvino
INCDIR=$(OPENVINODIR)/opencv/include -I $(OPENVINODIR)/deployment_tools/inference_engine/include
LIBDIR=$(OPENVINODIR)/opencv/lib
LIBS=-lstdc++ -lpthread -lX11 -lopencv_core -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs -lopencv_highgui -lopencv_photo -lopencv_objdetect -lopencv_dnn
DEFS+=-D_HAS_GUI
DEFS+=-D_DEBUG
GLOBALS=Makefile aphd.hpp

all:	main vidrec

main:	main.cpp runthread.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o main main.cpp runthread.cpp $(LIBS)

vidrec:	vidrec.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o vidrec vidrec.cpp $(LIBS)
