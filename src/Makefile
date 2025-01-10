OBJS	= main.o guiwindow.o election.o fileops.o audit.o votingsystem.o rawdata.o electable.o party.o candidate.o opl.o cpl.o mpo.o mv.o votingsystemfactory.o
SOURCE	= main.cc guiwindow.cc election.cc fileops.cc audit.cc votingsystem.cc rawdata.cc electable.cc party.cc candidate.cc opl.cc cpl.cc mpo.cc mv.cc votingsystemfactory.cc
HEADER	= guiwindow.h election.h fileops.h audit.h votingsystem.h rawdata.h electable.h party.h candidate.h opl.h cpl.h mpo.h mv.h votingsystemfactory.h
OUT	= project2
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS  = `pkg-config gtkmm-3.0 --cflags --libs`

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cc
	$(CC) $(FLAGS) main.cc -o $@ $(LFLAGS)

guiwindow.o: guiwindow.cc
	$(CC) $(FLAGS) guiwindow.cc $(LFLAGS)

election.o: election.cc
	$(CC) $(FLAGS) election.cc 

fileops.o: fileops.cc
	$(CC) $(FLAGS) fileops.cc

audit.o: audit.cc
	$(CC) $(FLAGS) audit.cc

votingsystem.o: votingsystem.cc
	$(CC) $(FLAGS) votingsystem.cc

votingsystemfactory.o: votingsystemfactory.cc
	$(CC) $(FLAGS) votingsystemfactory.cc

rawdata.o: rawdata.cc
	$(CC) $(FLAGS) rawdata.cc

electable.o: electable.cc
	$(CC) $(FLAGS) electable.cc

party.o: party.cc
	$(CC) $(FLAGS) party.cc

candidate.o: candidate.cc
	$(CC) $(FLAGS) candidate.cc

opl.o: opl.cc
	$(CC) $(FLAGS) opl.cc

cpl.o: cpl.cc
	$(CC) $(FLAGS) cpl.cc

mpo.o: mpo.cc
	$(CC) $(FLAGS) mpo.cc

mv.o: mv.cc
	$(CC) $(FLAGS) mv.cc

clean:
	rm -f $(OBJS) $(OUT)
