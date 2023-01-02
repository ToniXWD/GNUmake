SOURCE=$(wildcard ./*.cpp ./*.c)
OBJ=$(patsubst %.cpp, %.o, $(SOURCE))
OBJ:=$(patsubst %.c, %.o, $(OBJ))

.PHONY: clean

$(TARGET):$(OBJ)
	$(CXX) $^ -o $@

# %.o:%.cpp
#	gcc -c $^ -o $@

clean:
	$(RM)  $(TARGET) $(OBJ)
