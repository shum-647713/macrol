SRCS := macrol.c
OBJS := ${SRCS:.c=.o}
TARGET := macrol.so

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -llua -shared $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
