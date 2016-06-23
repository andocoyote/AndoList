#Best nmake tutorial: http://www.bogotobogo.com/cplusplus/make.php
CC=cl
EXECUTABLE=AndoList
CFLAGS=/c /EHsc
#LDFLAGS=/link /LIBPATH:$(LIBS)
DBGLAGS=/Zi
SOURCES=Listdriver.cpp List.cpp
OBJECTS=$(SOURCES:.cpp=.obj)

INCS=\

# Specify the location to my SDK libs (e.g. DbgHelp.Lib)
LIBS=\
	"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib" 

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(DBGFLAGS) $(OBJECTS) /Fe: $@ $(LDFLAGS)

.cpp.obj:
	$(CC) $(CFLAGS) $< /Fo: $@

clean:
   del *.exe *.obj *.pdb *.ilk

#------------------------------------------------------------------
# If creating multiple obj files:
#mybuild: main.obj foo.obj
#	cl /o myTest.exe main.obj foo.obj /link  \
#		/LIBPATH:$(LIBS) myLib.lib /NODEFAULTLIB:libcmt.lib

# To create the 2nd target: foo.obj
#foo.obj: foo.cpp
#	cl /c /EHsc foo.cpp -I $(INCS)
 

