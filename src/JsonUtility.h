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
	class JsonUtility {
	public:
		JsonUtility() {}
		~JsonUtility() {}
		static void ParseJsonFile(JsonObject& j, const char* path);
		template<typename T>
		static void ParseValue(T& value, const JsonObject& j, const char* name) {
			// Disable error checking with if, define
			if (!_DoesValueExist(j, name)) {
				return;
			}

			//TODO check if type is supported

			_ParseValue(value, j, name);
		}
	private:
		static void _ParseValue(int& value, const JsonObject& j, const char* name);
		static void _ParseValue(float& value, const JsonObject& j, const char* name);
		static void _ParseValue(std::string& value, const JsonObject& j, const char* name);
		static void _ParseValue(bool& value, const JsonObject& j, const char* name);
		static int _ParseInt(const JsonObject& j, const char* name);
		static float _ParseFloat(const JsonObject& j, const char* name);
		static bool _ParseBool(const JsonObject& j, const char* name);
		static std::string _ParseString(const JsonObject& j, const char* name);
		static bool _DoesValueExist(const JsonObject& j, const char* name);
	};
}

#endif // !JSONUTILITY_H