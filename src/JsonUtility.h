#ifndef JSONUTILITY_H
#define JSONUTILITY_H

#include "externalLibs/rapidjson/document.h"
#include "externalLibs/rapidjson/filereadstream.h"

/**
* @brief Handles serialization of json objects
*/
namespace JsonUtility {
	/**
	* @brief JsonObject is a wrapper to be used with the game engine
	*/
	struct JsonObject {
	public:
		rapidjson::Document json;
		std::string path;
		JsonObject() {}
	};

	/**
	* @brief Parses a json file from disk and stores in JsonObject
	*/
	void ParseJsonFile(JsonObject& j, const char* path);
	int ParseInt(const JsonObject& j, const char* name);
	float ParseFloat(const JsonObject& j, const char* name);
	bool ParseBool(const JsonObject& j, const char* name);
	std::string ParseString(const JsonObject& j, const char* name);
	bool DoesValueExist(const JsonObject& j, const char* name);

	/*
	template <typename T> T ParseValue(const JsonObject& j, const char* name) {
		if (j.json[name].IsInt()) {
			return ParseString();
		}
		else if (j.json[name].IsFloat()) {
			return ParseFloat();
		}
		else if (j.json[name].IsBool()) {
			return ParseBool();
		}
		else if (j.json[name].IsString()) {
			return ParseString();
		}
	}*/
}

#endif // !JSONUTILITY_H