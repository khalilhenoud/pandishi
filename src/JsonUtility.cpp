#include "JsonUtility.h"
#include "externalLibs/rapidjson/filereadstream.h"
#include <iostream>

namespace JsonUtility {

	void ParseJsonFile(JsonObject& j, const char* path) {
		FILE* fp;
		errno_t err;
		err = fopen_s(&fp, path, "rb"); // Change to r if not windows

		// Close the file and return if there is an error
		if (err != 0) {
			std::cout << "Error in opening " << path << " with error code: " << err << std::endl;
			fclose(fp);
			return;
		}

		// Get size of file
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		char* buffer = new char[size];
		fseek(fp, 0, SEEK_SET);

		// FileReadStream is a byte stream, it does not handle encodings. Make sure file is UTF-8 (Implement EncodedInputStream if other formats are required)
		rapidjson::FileReadStream is(fp, buffer, size*sizeof(char));

		// TODO: Add error check to make sure file is not empty or if there is a json error format

		// Parse json file and store it in j.json
		j.json.ParseStream(is);
		j.path = path;

		// Delete memory
		delete[]buffer;
		fclose(fp);
	}

	int ParseInt(const JsonObject& j, const char* name) {
		// Disable error checking with if, define
		if (!DoesValueExist(j, name)) {
			return 0;
		}

		return j.json[name].GetInt();
	}

	float ParseFloat(const JsonObject& j, const char* name) {
		// Disable error checking with if, define
		if (!DoesValueExist(j, name)) {
			return 0.0f;
		}

		return j.json[name].GetFloat();
	}

	bool ParseBool(const JsonObject& j, const char* name) {
		// Disable error checking with if, define
		if (!DoesValueExist(j, name)) {
			return false;
		}

		return j.json[name].GetBool();
	}

	std::string ParseString(const JsonObject& j, const char* name) {
		// Disable error checking with if, define
		if (!DoesValueExist(j, name)) {
			return "";
		}
		return j.json[name].GetString();
	}

	void ParseValue(int& value, const JsonObject& j, const char* name) {
		value = ParseInt(j, name);
	}

	void ParseValue(float& value, const JsonObject& j, const char* name) {
		value = ParseFloat(j, name);
	}

	void ParseValue(std::string& value, const JsonObject& j, const char* name) {
		value = ParseString(j, name);
	}

	void ParseValue(bool& value, const JsonObject& j, const char* name) {
		value = ParseBool(j, name);
	}

	bool DoesValueExist(const JsonObject& j, const char* name) {
		rapidjson::Value::ConstMemberIterator value = j.json.FindMember(name);
		if (value == j.json.MemberEnd()) {
			std::cout << "Value " << name << "does not exit in the following json file: " << j.path.c_str() << std::endl;
			return false;
		}
		else {
			return true;
		}
	}
}