C_FILES = dynamic_string.c linked_list.c

.PHONY: all
all:
	gcc main.c ${C_FILES} -o labels.out -Wall

debug:
	gcc main.c ${C_FILES} -o labels.out -Wall -g

.PHONY: clean
clean:
	rm -f labels.out
