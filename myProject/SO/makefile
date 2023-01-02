test:libSoTest.so
	$(CXX) test.cpp -o $@ -L . -l SoTest
libSoTest.so:SoTest.cpp
	$(CXX) -fPIC -shared $^ -o $@

.PHONY:clean

clean:
	$(RM) *.so test
