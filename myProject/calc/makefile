OBJ=$(patsubst %.c,%.o,$(wildcard ./*.c))
TARGET=calc

.PHONY:clean show

$(TARGET):$(OBJ)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $^ -o $@
clean:
	$(RM) *.o $(TARGET)
	@echo "Remove success!"
show:
	echo $(patsubst %.c,%.o,./*.c)
	echo $(wildcard ./*.c)