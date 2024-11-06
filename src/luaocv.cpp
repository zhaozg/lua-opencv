/*
 *	luaocv
 *	/src/luaocv.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>
#include"functions.hpp"
#include"core.hpp"

extern "C" int
luaopen_ocv(lua_State *l)
{
	locv_core_init(l);
#ifdef HAVE_OPENCV_IMGCODECS
	locv_imgcodecs_init(l);
#endif
	locv_highgui_init(l);
#ifdef HAVE_OPENCV_VIDEOIO
	locv_videoio_init(l);
#endif
	locv_objdetect_init(l);
	locv_imgproc_init(l);
	luaL_newlib(l, luaocvFunctions);
	return 1;
}
