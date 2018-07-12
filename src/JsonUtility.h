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

	void ParseValue(int& value, const JsonObject& j, const char* name);
	void ParseValue(float& value, const JsonObject& j, const char* name);
	void ParseValue(std::string& value, const JsonObject& j, const char* name);
	void ParseValue(bool& value, const JsonObject& j, const char* name);
}

#endif // !JSONUTILITY_H