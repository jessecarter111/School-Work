EXEC =	polyphase_test

OBJS =	polyphase_test.o						\
        polyphase_filter.o                                              \
	libdd.o

INCLUDEPATHS =	-I.

STRIPTOOL = strip

LIBS += $(INCLUDEPATHS) -lrt -lasound -lm -pthread

CFLAGS += -Werror -Wall -Wextra -Wformat-security -Wformat -O3
CFLAGS += -DNEW_CONF_PARSER_VALIDATION=1

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
#	$(STRIPTOOL) -R .comment -R .note $(EXEC)

clean:
	-rm -f $(EXEC) *.o *.wav
