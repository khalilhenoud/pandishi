#include "JsonUtility.h"
#include "externalLibs/rapidjson/filereadstream.h"
#include <iostream>

namespace utils {
	namespace json {

		void Api::ParseJsonFile(Object& j, const char* path) {
			FILE* fp;
			errno_t err;

			// Change to r if not windows (Add if, def to run appropriate parameter)
			err = fopen_s(&fp, path, "rb");

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

			// If file is empty
			if (size == 0) {
				std::cout << "Error: File " << path << " is an empty file." << std::endl;
				delete[]buffer;
				fclose(fp);
				return;
			}

			// FileReadStream is a byte stream, it does not handle encodings. Make sure file is UTF-8 (Implement EncodedInputStream if other formats are required)
			rapidjson::FileReadStream is(fp, buffer, size * sizeof(char));

			// Parse json file and store it in j.json
			if (j.json.ParseStream(is).HasParseError()) {
				std::cout << "Error: File " << path << " is not a valid json file." << std::endl;
			}

			j.path = path;

			// Delete memory
			delete[]buffer;
			fclose(fp);
		}

		int Api::_ParseInt(const Object& j, const char* name) {
			return j.json[name].GetInt();
		}

		float Api::_ParseFloat(const Object& j, const char* name) {
			return j.json[name].GetFloat();
		}

		bool Api::_ParseBool(const Object& j, const char* name) {
			return j.json[name].GetBool();
		}

		std::string Api::_ParseString(const Object& j, const char* name) {
			return j.json[name].GetString();
		}

		void Api::_ParseValue(int& value, const Object& j, const char* name) {
			value = _ParseInt(j, name);
		}

		void Api::_ParseValue(float& value, const Object& j, const char* name) {
			value = _ParseFloat(j, name);
		}

		void Api::_ParseValue(std::string& value, const Object& j, const char* name) {
			value = _ParseString(j, name);
		}

		void Api::_ParseValue(bool& value, const Object& j, const char* name) {
			value = _ParseBool(j, name);
		}

		bool Api::_DoesValueExist(const Object& j, const char* name) {
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
}