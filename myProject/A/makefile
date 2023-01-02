libaTest.a:aTest.o
	$(AR) -r $@ aTest.o
aTest.o:aTest.cpp
	$(CXX) -c $^ -o $@

.PHONY:clean

clean:
	$(RM) *.o *.a