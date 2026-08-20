CXX = g++

CXXFLAGS = -std=c++17 -O2 -I Public

LDFLAGS = \
-lopenvdb \
-lImath-3_1 \
-ltbb \
-lblosc \
-lz

TARGET = app

SRCS = \
	main.cpp \
	$(wildcard Private/*.cpp)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)