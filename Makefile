EXEC = fp.exe

program:	Record.o View.o Control.o ReportGenerator.o
	g++ -o fp main.cc Record.o View.o Control.o	ReportGenerator.o

ReportGenerator: ReportGenerator.cc ReportGenerator.h Record.h Map.h ReportData.h CompareBehavior.h
	g++ -c ReportGenerator.cc

Record.o:	Record.cc Record.h
	g++ -c Record.cc

Control.o: Control.cc Control.h View.h
	g++ -c Control.cc

View.o: View.cc View.h
	g++ -c View.cc

clean:
	del -rf *.o fp  # For Windows (Mingw)
	rm -f *.o fp	# For Linux

	# MinGW32-make clean (for running the whole code files with Makefile)