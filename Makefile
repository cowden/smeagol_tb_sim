


name := simple_ecal
G4TARGET := $(name)
G4EXLIB := true

LDFLAGS := -lhdf5 -lhdf5_cpp 

ifndef G4INSTALL
  G4INSTALL= ../../../
endif

# include and link CaloGraphy
CGDIR := /home/me/proj/CaloX/CaloXUtils/calography
CGINC := -I$(CGDIR)/calography 
CGLIB := -L$(CGDIR)/src -lCaloGraphy -lCGG4
CPPFLAGS := $(CGINC)
LDFLAGS += $(CGLIB)

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

vislean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*
