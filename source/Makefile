LINK    = echo linking $@ && $(COMP)
GCC     = @echo compiling $@ && g++
GC      = @echo compiling $@ && $(COMP)
AR      = @echo generating static library $@ && ar crv
FLAGS   = -Wl,-Bsymbolic -fvisibility=hidden -fPIC	
GCCFLAGS =
DEFINES =
HEADER  = -I../include
LIBS    = -lm
#编译库文件使用
#LINKFLAGS = -shared 

#目标文件名。此处为libcurl.so，动态库一般以lib为前缀
TARGET	= cpp_demo.out

#编译后未连接的中间文件，每一个.c或.cpp对应于这里一个.o文件,多个.o可以用空格分开,也可用"\"换行,然后写在新一行
OBJECT := Cpp_Demo.o SmallBox.o Shape.o PrintData.o Person.o Line.o Box.o

#添加库文件
LIBS    +=  -pthread 

#源码版本
VERSION	=

#源码路径
MSPATH	= /mnt/hgfs/Shared_linux_windows/study/cpp/Cpp_Demo

#编译器
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


	













