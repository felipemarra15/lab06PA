# Makefile para Lab6PA (C++98)

CXX       = g++
CXXFLAGS  = -Wall -Wextra -std=gnu++98
INCLUDES  = -I. \
            -I./ICollection \
            -I./DataTypes

# Listado automático de fuentes
SRCS      := $(wildcard *.cpp) \
             $(wildcard ICollection/*.cpp) \
             $(wildcard ICollection/interfaces/*.cpp) \
             $(wildcard ICollection/collections/*.cpp) \
             $(wildcard DataTypes/*.cpp)

# Genera los .o
OBJS      := $(SRCS:.cpp=.o)

# Ejecutable final
TARGET    = programa

.PHONY: all clean

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJS)

# Regla genérica
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
