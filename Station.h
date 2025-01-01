// Name: Fawad Arshad
// Student ID: 030815153
// Date: Nov 24, 2024

// I declare that this submission is the result of my own work and I only copied the code that 
// my professor provided to complete my workshops and assignments. 
// This submitted piece of work has not been shared with any other student or 3rd party content provider.

#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <string>
#include <iomanip>

namespace seneca {
	class Station {
		// id of the station
		int m_id;
		// name of the item handled by the station
		std::string m_name;
		// description of the station
		std::string m_descrip;
		// next serial number to be assigned to an item at this station
		size_t m_serialNumber;
		// number of items currently in stock
		unsigned int m_quantity;

		// CLASS VARIABLES
		static size_t m_widthField;
		static unsigned int id_generator;

	public:
		Station(const std::string& str);

		const std::string& getItemName() const;

		size_t getNextSerialNumber();

		size_t getQuantity() const;

		void updateQuantity();

		void display(std::ostream& os, bool full) const;
	};
}
#endif