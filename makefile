ifeq ($(RELEASE),1)
	CXXFLAGS_DEBUG	= -O2 -DLOCV_RELEASE
else
	CXXFLAGS_DEBUG	= -g
endif

OPENCV_DIR  ?= /usr/local/opt/opencv

LUA_PKGNAME	?= luajit
LUA_CXXFLAGS	?= -I/usr/local/include/luajit-2.1
LUA_LDFLAGS	?= -L/usr/local/lib -lluajit-5.1

CV_PKGNAME	?= opencv4
CV_CXXFLAGS	?= -I$(OPENCV_DIR)/include/opencv4
CV_LDFLAGS	?= -L$(OPENCV_DIR)/lib/ -lopencv_core -lopencv_imgproc \
							 -lopencv_highgui -lopencv_objdetect

DYN_FLAGS	?= -shared -fPIC -Wl,-rpath,$(OPENCV_DIR)/lib/

CROSS_COMPILE	?=
CXX		?= $(CROSS_COMPILE)g++
CXXLD		?= $(CROSS_COMPILE)g++

CXXFLAGS	?= $(DYN_FLAGS) $(LUA_CXXFLAGS) $(CV_CXXFLAGS) \
		   $(CXXFLAGS_DEBUG) -std=c++11
LDFLAGS		?= $(DYN_FLAGS) $(LUA_LDFLAGS) $(CV_LDFLAGS)

SRCS		:= src/luaocv.cpp src/helper.cpp \
	src/core.cpp src/imgcodecs.cpp src/highgui.cpp src/videoio.cpp	\
	src/objdetect.cpp src/imgproc.cpp
OBJS		:= $(patsubst %.cpp, %.o, $(SRCS))

LIB		:= ocv.so

.PHONY: default clean disbuild

default: $(LIB)

$(LIB): $(OBJS)
	$(CXXLD) $(OBJS) -o $(LIB) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJS)

disbuild: clean
	rm -f $(LIB)
