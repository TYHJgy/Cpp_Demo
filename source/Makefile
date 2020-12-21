LINK    = echo linking $@ && $(COMP)
GCC     = @echo compiling $@ && g++
GC      = @echo compiling $@ && $(COMP)
AR      = @echo generating static library $@ && ar crv
FLAGS   = -Wl,-Bsymbolic -fvisibility=hidden -fPIC 
GCCFLAGS = -fpermissive
DEFINES =
HEADER  = -I../include
LIBS    = -lm
#LINKFLAGS = -shared #编译动态库

TARGET	= cpp_demo.out

OBJECT := 	Cpp_Demo.o \
			SmallBox.o \
			Shape.o \
			PrintData.o \
			Person.o \
			Line.o \
			Box.o \
			TestThread.o \
			TestThread_std.o\
			TestVector.o

LIBS    +=  -pthread 
FLAGS	+=  -std=gnu++11 #c++11
VERSION	=

MSPATH	= /mnt/hgfs/Shared_linux_windows/study/cpp/Cpp_Demo

COMP	= g++


$(TARGET): $(OBJECT)
	$(LINK) $(FLAGS) $(LINKFLAGS) -o $@ $^ $(LIBS)
	rm -rf *.o

.cpp.o:
	$(GCC) -c $(HEADER) $(FLAGS) $(GCCFLAGS) -o $@ $<

.c.o:
	$(GC) -c $(HEADER) $(FLAGS) -o $@ $<


run:$(TARGET)
	./$(TARGET)

clean:
	rm -rf *.out *.o *.so
	
update:
	cp -rf $(MSPATH)$(VERSION)/ ../../

export:
	cp -rf ../../$(VERSION) $(MSPATH) 


	













