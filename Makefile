all: parser parsernew

clean:
	rm -rf parser
	rm -rf parsernew
	rm -rf amsparser.o
	$(MAKE) clean -C eMIDI

parsernew: eMIDI/obj/midifile.o eMIDI/obj/emidi_linux.o amsparser.o
	g++ parsernew.cpp eMIDI/obj/midifile.o eMIDI/obj/emidi_linux.o amsparser.o -Irapidxml -IeMIDI/src -o parsernew

parser: eMIDI/obj/midifile.o eMIDI/obj/emidi_linux.o
	g++ main.cpp eMIDI/obj/midifile.o eMIDI/obj/emidi_linux.o -Irapidxml -IeMIDI/src -o parser

amsparser.o: amsparser.cpp
	g++ -c amsparser.cpp -o amsparser.o -Irapidxml -IeMIDI/src

eMIDI/obj/midifile.o: eMIDI/src/midifile.c
	$(MAKE) obj/midifile.o -C eMIDI

eMIDI/obj/emidi_linux.o: eMIDI/src/hal/emidi_linux.c
	$(MAKE) obj/emidi_linux.o -C eMIDI

