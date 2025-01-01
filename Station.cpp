// Name: Fawad Arshad
// Student ID: 030815153
// Date: Nov 24, 2024

// I declare that this submission is the result of my own work and I only copied the code that 
// my professor provided to complete my workshops and assignments. 
// This submitted piece of work has not been shared with any other student or 3rd party content provider.


#include "Station.h"
#include "Utilities.h"

namespace seneca {
	size_t Station::m_widthField{};
	unsigned int Station::id_generator{};

	Station::Station(const std::string& str) : m_id{}, m_name{}, m_descrip{}, m_serialNumber{}, m_quantity{}
	{
		Utilities utilObj;
		size_t nextPos = 0;
		bool more = false;
		std::string itemName{};
		std::string serialNum{};
		std::string quantity{};
		std::string desc{};
		itemName = utilObj.extractToken(str, nextPos, more);
		serialNum = utilObj.extractToken(str, nextPos, more);
		quantity = utilObj.extractToken(str, nextPos, more);

		if (Station::m_widthField < utilObj.getFieldWidth()) {
			Station::m_widthField = utilObj.getFieldWidth();
		}

		desc = utilObj.extractToken(str, nextPos, more);

		m_name = itemName;
		m_serialNumber = std::stoi(serialNum);
		m_quantity = std::stoi(quantity);
		m_descrip = desc;


		++id_generator;
		m_id = id_generator;
	}

	const std::string& Station::getItemName() const
	{
		return m_name;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return m_quantity;
	}

	void Station::updateQuantity()
	{
		if (m_quantity > 0) {
			--m_quantity;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		if (!full) {
			os << std::setw(3) << std::setfill('0') << std::right << m_id << " | " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | " << std::setw(6) << std::setfill('0')  << std::right << m_serialNumber << " | " << std::endl;
		}
		else {
			os << std::setw(3) << std::setfill('0') << std::right << m_id << " | " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | " << std::setw(6) << std::setfill('0')  << std::right << m_serialNumber << " | " << std::setw(4) << std::right << std::setfill(' ') << m_quantity << " | " << m_descrip << "\n";
		}
	}
}