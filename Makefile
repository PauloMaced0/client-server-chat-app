CC = g++
CFLAGS = -O2 -Wall -Wextra
LDFLAGS = -pthread

SRC_FILES = main.cpp protocol.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

TARGET = main 

all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

# Clean rule to remove the compiled files
clean:
	rm -f $(OBJ_FILES) $(TARGET)

# Rule to generate dependencies
%.d: %.cpp
	@$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Include the dependency files
-include $(SRC_FILES:.cpp=.d)
