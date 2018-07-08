all: parser parsernew

clean:
	rm -rf parser
	rm -rf instruments.o
	$(MAKE) clean -C eMIDI

parsernew:
	g++ parsernew.cpp eMIDI/obj/midifile.o eMIDI/obj/emidi_linux.o instruments.o -Irapidxml -IeMIDI/src -o parser

parser: eMIDI/obj/midifile.o eMIDI/obj/emidi_linux.o instruments.o
	g++ main.cpp eMIDI/obj/midifile.o eMIDI/obj/emidi_linux.o instruments.o -Irapidxml -IeMIDI/src -o parser

instruments.o: instruments.cpp
	g++ -c instruments.cpp -o instruments.o

eMIDI/obj/midifile.o: eMIDI/src/midifile.c
	$(MAKE) obj/midifile.o -C eMIDI

eMIDI/obj/emidi_linux.o: eMIDI/src/hal/emidi_linux.c
	$(MAKE) obj/emidi_linux.o -C eMIDI

