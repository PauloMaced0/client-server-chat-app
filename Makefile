CC = g++
CFLAGS = -O2 -Wall -Wextra 
LDFLAGS = -pthread

# wxWidgets configuration
# you might need to change this, as this is a specific wxWidgets configuration path
WX_CONFIG = ~/wxWidgets-3.2.5/build-release/wx-config
WX_CXXFLAGS = $(shell $(WX_CONFIG) --cxxflags)
WX_LDFLAGS = $(shell $(WX_CONFIG) --libs)

SRC_FILES_SERVER	= main.cpp protocol.cpp
# SRC_FILES_CLIENT	= client.cpp protocol.cpp
# SRC_FILES_APP		= wx_main.cpp

OBJ_FILES_TARGET_SERVER = $(SRC_FILES_SERVER:.cpp=.o)
# OBJ_FILES_TARGET_CLIENT = $(SRC_FILES_CLIENT:.cpp=.o)
# OBJ_FILES_TARGET_APP	= $(SRC_FILES_APP:.cpp=.o)


DEP_FILES_TARGET_SERVER = $(SRC_FILES_SERVER:.cpp=.d)
# DEP_FILES_TARGET_CLIENT = $(SRC_FILES_CLIENT:.cpp=.d)
# DEP_FILES_TARGET_APP	= $(SRC_FILES_APP:.cpp=.d)

# Targets
TARGET_SERVER	= main
# TARGET_CLIENT	= main_wx
# TARGET_APP		= another_main

all: $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_APP)

# Rules to link the object files into executables
$(TARGET_SERVER): $(OBJ_FILES_TARGET_SERVER)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET_CLIENT): $(OBJ_FILES_TARGET_CLIENT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET_APP): $(OBJ_FILES_TARGET_APP)
	$(CC) $(CFLAGS) $(WX_CXXFLAGS) $(LDFLAGS) $(WX_LDFLAGS) -o $@ $^

# Rule to compile .cpp files into .o files
$(OBJ_FILES_TARGET_SERVER): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FILES_TARGET_CLIENT): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FILES_TARGET_APP): %.o: %.cpp
	$(CC) $(CFLAGS) $(WX_CXXFLAGS) -c $< -o $@

# Clean rule to remove the compiled files
clean:
	rm -f $(OBJ_FILES_TARGET_SERVER) $(OBJ_FILES_TARGET_CLIENT) $(OBJ_FILES_TARGET_APP) $(DEP_FILES_TARGET_SERVER) $(DEP_FILES_TARGET_CLIENT) $(DEP_FILES_TARGET_APP) $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_APP)

# Rule to generate dependencies
$(DEP_FILES_TARGET_SERVER): %.d: %.cpp
	@$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(DEP_FILES_TARGET_CLIENT): %.d: %.cpp
	@$(CC) -M $(CFLAGS) $(WX_CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(DEP_FILES_TARGET_APP): %.d: %.cpp
	@$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Include the dependency files
-include $(DEP_FILES_TARGET_SERVER)
-include $(DEP_FILES_TARGET_CLIENT)
-include $(DEP_FILES_TARGET_APP)
