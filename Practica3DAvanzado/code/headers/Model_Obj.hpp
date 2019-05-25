#pragma once

#ifndef MODEL_OBJ_HEADER
#define MODEL_OBJ_HEADER

#include <string>


namespace renderer
{
	class Model_Obj
	{

		std::string error;

		Model_Obj(const std::string & obj_file_path);
	};
}

#endif