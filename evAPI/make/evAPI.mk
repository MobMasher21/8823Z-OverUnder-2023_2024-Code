#!Makefile data use for compiling the evAPI

#*Check which OS the hoast computer is running
ifeq ($(OS),Windows_NT)
  #?Windows
  #*Get the source files from the evAPI and add them into SRC_C
  #Find all the .cpp and .c files
  EVSRC_C := $(shell dir evAPI\*.cpp evAPI\*.c /s/b/a:-d)
  #Convert the list to the same format the vex makefiles uses and store it in SRC_C
  SRC_C += $(subst $(CURDIR)/,,$(subst \,/,$(EVSRC_C)))
  
  #*Get the header files from the evAPI and add them into SRC_H
  #Find all the .h files
  EVSRC_H := $(shell dir evAPI\*.h /s/b/a:-d)
  #Convert the list to the same format the vex makefiles uses and store it in SRC_H
  SRC_H += $(subst $(CURDIR)/,,$(subst \,/,$(EVSRC_H)))
else
  #?Unix like
  #*Get the source files from the evAPI and add them into SRC_C
  SRC_C += $(shell find evAPI -type f -name "*.cpp" -o -name "*.c")

  #*Get the header files from the evAPI and add them into SRC_H
  SRC_H += $(shell find evAPI -type f -name "*.h")
endif