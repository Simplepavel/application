libs = -L C:\msys64\ucrt64\lib -l Qt6Widgets -l Qt6Core -l Qt6Gui
includes = -I C:\msys64\ucrt64\include\qt6 -I C:\msys64\ucrt64\include\qt6\QtWidgets \
			-I C:\msys64\ucrt64\include\qt6\QtCore -I C:\msys64\ucrt64\include\qt6\QtGui 

files = main.cpp moc_window.cpp moc_LineEdit.cpp MyLineEdit.cpp window.cpp


all: moc
	g++ $(files) $(includes) $(libs) -o main.exe

moc:
	rm -f moc_*.cpp
	C:\msys64\ucrt64\share\qt6\bin\moc.exe Window.h -o moc_window.cpp
	C:\msys64\ucrt64\share\qt6\bin\moc.exe MyLineEdit.h -o moc_LineEdit.cpp