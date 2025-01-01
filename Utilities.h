// Name: Fawad Arshad
// Student ID: 030815153
// Date: Nov 24, 2024

// I declare that this submission is the result of my own work and I only copied the code that 
// my professor provided to complete my workshops and assignments. 
// This submitted piece of work has not been shared with any other student or 3rd party content provider.


#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <string>
#include <iostream>
#include <limits>

namespace seneca {
	class Utilities {
		size_t m_widthField = 1;
		
		// CLASS VARIABLE
		static char m_delimiter;

		static std::string _trim(std::string& token);
	public:
		void setFieldWidth(size_t newWidth);

		size_t getFieldWidth() const;

		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		// CLASS FUNCTION
		static void setDelimiter(char newDelimiter);

		// CLASS FUNCTION
		static char getDelimiter();
	};
}
#endif
