CROSS=

CC=$(CROSS)gcc
CPP=$(CROSS)g++

MKDIR       := mkdir -p
RM          := rm -f
DIRNAME     := dirname


APP=efmgr

LDFLAGS = -lemi `pkg-config -libs lilv-0`
CFLAGS = -Wall -Wextra -I. -DDEBUG -g -O2 -std=c++2a `pkg-config --cflags lilv-0`

OUTDIR=./.out
BINDIR=$(OUTDIR)/bin

PATHDIR=$(shell find -type d) 

SRCS= $(foreach dir,$(PATHDIR),$(wildcard $(dir)/*.cpp)) 
PATHOBJS=$(subst ./,,$(SRCS:.cpp=.o))
OBJS=$(patsubst %,$(OUTDIR)/%,$(PATHOBJS))

$(APP):$(OBJS)
	@$(MKDIR) $(BINDIR)
	@$(CPP) $(OBJS) -o $(BINDIR)/$@ $(LDFLAGS) 

$(OBJS):$(OUTDIR)/%.o:%.cpp
	@$(MKDIR) `$(DIRNAME) $@`
	@echo COMPILING $(notdir $@)
	@$(CPP) $(CFLAGS) -c -o $@ $<

format:
	clang-format -style=LLVM -i src/*

clean:
	$(RM) -rf $(OUTDIR)
