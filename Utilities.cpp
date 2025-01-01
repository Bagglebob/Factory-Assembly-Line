// Name: Fawad Arshad
// Student ID: 030815153
// Date: Nov 24, 2024

// I declare that this submission is the result of my own work and I only copied the code that 
// my professor provided to complete my workshops and assignments. 
// This submitted piece of work has not been shared with any other student or 3rd party content provider.


#include "Utilities.h"

namespace seneca {
	char Utilities::m_delimiter{};

	std::string Utilities::_trim(std::string& token)
	{
		std::string str{};
		size_t startPos = 0;
		startPos = token.find_first_not_of(' ');
		//str = token.substr(startPos);

		size_t endPos = 0;
		endPos = token.find_last_not_of(' ') + 1;
		str = token.substr(startPos, endPos - startPos);
		return str;
	}

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	};

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string err = "ERROR: delimiter is found at next_pos";
		std::string delimPosErr = "ERROR: delimiter not found";

		if (str[next_pos] != m_delimiter) {
			std::string token{};
			size_t delimPos = str.find_first_of(m_delimiter, next_pos);

			// find token
			token = str.substr(next_pos, delimPos - next_pos);

			// trim token
			std::string trimmedToken{};
			trimmedToken = _trim(token);
			if (trimmedToken.size() > m_widthField) {
				m_widthField = trimmedToken.size();
			}

			// this if statement is for debugging
			if (delimPos < std::numeric_limits<std::size_t>::max()) {
				// set next_pos
				next_pos = delimPos + 1;
				more = true;
				return trimmedToken;
			}
			else {
				more = false;
				return trimmedToken;				
				// if delim isnt found in str [DEBUGGING] Remove throw statement after
				//throw delimPosErr;
			}
		}
		else {
			more = false;
			//std::cout << "delimiter is found at next_pos" << std::endl;
			throw err;
		}
		return "";
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}