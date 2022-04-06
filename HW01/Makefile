CC=gcc -g
EXEC=main
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)
OBJS_DIR=sources/
vpath %.c sources
vpath %.h headers
OBJS=$(OBJS_DIR)/NumberGame.o $(OBJS_DIR)/PictureManipulation.o  $(OBJS_DIR)/main.o

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJS_DIR)/NumberGame.o: NumberGame.c NumberGame.h PictureManipulation.h main.h
	$(CC) -c $(CFLAGS) $< -o $@
$(OBJS_DIR)/PictureManipulation.o: PictureManipulation.c PictureManipulation.h NumberGame.h main.h
	$(CC) -c $(CFLAGS) $< -o $@
	
$(OBJS_DIR)/main.o: main.c main.h PictureManipulation.h NumberGame.h
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	rm -f $(EXEC)
	rm -f $(OBJS)
