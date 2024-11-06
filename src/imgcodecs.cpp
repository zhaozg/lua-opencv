/*
 *	luaocv
 *	/src/imgcodecs.cpp
 *	This file is distributed under MIT License.
 *	Copyright (c) 2024 Yao Zi. All rights reserved.
 */

#include<lua.hpp>
#include<opencv2/core.hpp>
#include"core.hpp"

#ifdef HAVE_OPENCV_IMGCODECS
#include<opencv2/imgcodecs.hpp>

#include"imgcodecs.hpp"
#include"helper.hpp"

int
locv_imgcodecs_imread(lua_State *l)
{
	const char *path = luaL_checkstring(l, 1);

	const char *const list[] = {
		"unchanged", "grayscale", "color", "anydepth", "anycolor",
		NULL
	};
	enum cv::ImreadModes modes[] = {
		cv::IMREAD_UNCHANGED, cv::IMREAD_GRAYSCALE, cv::IMREAD_COLOR,
		cv::IMREAD_ANYDEPTH, cv::IMREAD_ANYCOLOR
	};
	int opt = luaL_checkoption(l, 2, "color", list);

	cv::Mat res = cv::imread(path, modes[opt]);

	if (!res.data) {
		lua_pushnil(l);
		lua_pushfstring(l, "Failed to read image %s", path);
		return 2;
	}

	cv::Mat *cpy = new cv::Mat(res);
	locv_core_mat_in_lua(l, cpy);

	return 1;
}

/*	TODO: support codec parameters	*/
int
locv_imgcodecs_imwrite(lua_State *l)
{
	const char *path = luaL_checkstring(l, 1);
	cv::Mat *mat = locv_core_mat_in_native(l, 2);

	bool result = false;
	try {
		result = cv::imwrite(path, *mat);
	} catch (const cv::Exception &e) {
		lua_pushboolean(l, false);
		lua_pushfstring(l, "Cannot save image as %s: %s", e.what());
		return 2;
	}

	lua_pushboolean(l, true);
	return 1;
}

void
locv_imgcodecs_init(lua_State *l)
{
	return;
}
#endif
