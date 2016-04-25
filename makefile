#Best nmake tutorial: http://www.bogotobogo.com/cplusplus/make.php
INCS=\

# Specify the location to my SDK libs (e.g. DbgHelp.Lib)
LIBS=\
	"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib" 

mybuild: ListDriver.obj List.obj
	cl /Zi /o AndoList.exe ListDriver.obj List.obj

List.obj: List.cpp
	cl /c /EHsc List.cpp

ListDriver.obj: ListDriver.cpp
	cl /c /EHsc ListDriver.cpp

all:mybuild

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
 

