.SUFFIXES:
.SUFFIXES: .cpp .o

CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
EXEDIR = exe
UNAME := $(shell uname)

vpath %.cpp Source
vpath %.h Headers

target = FindEliza

.PHONY: clean setup

CPP_FILES := $(wildcard ../Source/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
#objects := $(patsubst %, $(OBJDIR)/%, $(target).o, ImageHandler.o, Finder.o)

all: setup clean $(target)

setup:
ifeq ($(UNAME),Linux)
	$(shell install-opencv.sh)
else
	@echo $(UNAME)
endif

$(target):
	mkdir $(EXEDIR)
	@echo [INFO] Creating Binary Executable [$(target)]
	cd $(EXEDIR) && \
	g++ $(CFLAGS) $(LIBS) -o $(target) -g ../Source/$(target).cpp ../Source/ImageHandler.cpp ../Source/Finder.cpp

clean:
	rm -rf $(EXEDIR)