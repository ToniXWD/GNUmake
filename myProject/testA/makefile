TARGET=main
LDFLAGS=-L ../A
LIBS=-laTest

$(TARGET):main.cpp
	$(CXX) $^ -o $@ $(LIBS) $(LDFLAGS)

.PHONY:clean

clean:
	$(RM) $(TARGET)