all: eMIDI/obj/midifile.o eMIDI/obj/emidi_linux.o
	g++ main.cpp eMIDI/obj/midifile.o eMIDI/obj/emidi_linux.o -Irapidxml -IeMIDI/src -o parser

clean:
	rm -rf parser
	$(MAKE) clean -C eMIDI

eMIDI/obj/midifile.o: eMIDI/src/midifile.c
	$(MAKE) obj/midifile.o -C eMIDI

eMIDI/obj/emidi_linux.o: eMIDI/src/hal/emidi_linux.c
	$(MAKE) obj/emidi_linux.o -C eMIDI

