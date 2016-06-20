PHONY=flatc clean all write read
INC=-I ../flatbuffers/include -I ../flatbuffers/include/flatbuffers
STATIC_LIB=../flatbuffers/libflatbuffers.a
CXX_FLAG=-std=c++11
CXX=g++
WSRC=write.cpp
RSRC=read.cpp
WTARGET=write
RTARGET=read
FBS_SRC=schema.fbs

all:write read

write: flatc $(FBS_SRC:.fbs=_generated.h)
	$(CXX) $(CXX_FLAG) $(INC) -o $(WTARGET) $(WSRC) $(STATIC_LIB)

read: flatc $(FBS_SRC:.fbs=_generated.h)
	$(CXX) $(CXX_FLAG) $(INC) -o $(RTARGET) $(RSRC) $(STATIC_LIB)

flatc:
	../flatbuffers/flatc -c -o . $(FBS_SRC)

clean:
	rm -rf *.o $(WTARGET) $(RTARGET) schema_generated.h