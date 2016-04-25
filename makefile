#Best nmake tutorial: http://www.bogotobogo.com/cplusplus/make.php
INCS=\

# Specify the location to my SDK libs (e.g. DbgHelp.Lib)
LIBS=\
	"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib" 

mybuild: ListDriver.obj List.obj
	cl /Zi /o AndoList.exe ListDriver.obj List.obj /link \
		LIBPATH:$(LIBS)

List.obj: List.cpp
	cl /c List.cpp -I $(INCS)

ListDriver.obj: ListDriver.cpp
	cl /c ListDriver.cpp -I $(INCS)

all:mybuild

clean:
   del *.exe *.obj *.pdb

#------------------------------------------------------------------
# If creating multiple obj files:
#mybuild: main.obj foo.obj
#	cl /o myTest.exe main.obj foo.obj /link  \
#		/LIBPATH:$(LIBS) myLib.lib /NODEFAULTLIB:libcmt.lib

# To create the 2nd target: foo.obj
#foo.obj: foo.cpp
#	cl /c /EHsc foo.cpp -I $(INCS)
 

