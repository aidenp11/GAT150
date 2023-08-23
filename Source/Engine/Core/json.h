#pragma once
#include <string>
#include "vector.h"
#include <C:\Users\apatrick\source\repos\GAT150\Source\ThirdParty\rapidjson\include\rapidjson\document.h>

#define READ_DATA(value, data) lady::Json::Read(value, #data, data)
#define READ_DATA_REQUIRED(value, data) lady::Json::Read(value, #data, data, true)
#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]
#define READ_NAME_DATA(value, name, data) lady::Json::Read(value, name, data)
#define READ_NAME_DATA_REQUIRED(value, name, data) lady::Json::Read(value, name, data, true)

namespace lady
{
	class Json
	{
	public:
		static bool Load(const std::string& filename, rapidjson::Document& document);
		static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);

		static bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required = false);
	};

	using json_t = rapidjson::Value;
}
