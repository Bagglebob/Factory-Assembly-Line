// Name: Fawad Arshad
// Student ID: 030815153
// Date: Nov 24, 2024

// I declare that this submission is the result of my own work and I only copied the code that 
// my professor provided to complete my workshops and assignments. 
// This submitted piece of work has not been shared with any other student or 3rd party content provider.


#include "CustomerOrder.h"
#include "Utilities.h"
#include <vector>

namespace seneca {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() :m_name{}, m_product{}, m_cntItem{}, m_lstItem{}
	{}

	CustomerOrder::CustomerOrder(const std::string & str) :m_name{}, m_product{}, m_cntItem{}, m_lstItem{}
	{
		Utilities utilObj;
		size_t nextPos = 0;
		bool more = false;
		std::string custName{};
		std::string orderName{};
		std::vector<std::string> itemList{};
		custName = utilObj.extractToken(str, nextPos, more);
		orderName = utilObj.extractToken(str, nextPos, more);
		
		while (str[nextPos] != utilObj.getDelimiter() && nextPos != std::string::npos) {
			std::string item{};
			
			//if (nextPos != std::string::npos && more == true) {
			if (more == true) {
				item = utilObj.extractToken(str, nextPos, more);
				// https://stackoverflow.com/questions/571394/how-to-find-out-if-an-item-is-present-in-a-stdvector
				//if (std::find(itemList.begin(), itemList.end(), item) == itemList.end()) {
					itemList.push_back(item);
				//}				
			}
			else {
				break;
			}
		}
		
		m_name = custName;
		
		m_product = orderName;
		
		  // Update item count
		m_cntItem = itemList.size();

		// Dynamically allocate an array of pointers to Item
		m_lstItem = new Item * [m_cntItem];

		// Populate the array with dynamically allocated Items
		for (size_t i = 0; i < m_cntItem; ++i) {
			m_lstItem[i] = new Item(itemList[i]);
		}

		if (utilObj.getFieldWidth() > m_widthField) {
			m_widthField = utilObj.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder&)
	{
		std::string err{ "ERROR: Copy Constructor not available for Customer Order" };
		throw err;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept :m_name{}, m_product{}, m_cntItem{}, m_lstItem{}
	{
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src)
		{
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}

			delete[] m_lstItem;

			// 3. shallow copy			
			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;

			// 4. move the resource from parameter into current instance
			m_lstItem = src.m_lstItem;
						
			src.m_lstItem = nullptr;
			src.m_name = "";
			src.m_product = "";				

			src.m_cntItem = 0;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i]; 
		}
		delete[] m_lstItem;

		m_lstItem = nullptr;
		m_name = "";
		m_product = "";
		m_cntItem = 0;
	}

	bool CustomerOrder::isOrderFilled() const
	{				
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_isFilled == false) {
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{		
		//bool itemFound = false;
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName) {
				//itemFound = true;
				if (!m_lstItem[i]->m_isFilled) {
					return false; // find unfilled item
				}
			}
		}		
		// If the item doesn't exist in the order, this query returns true
		return true;	
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					std::cout << "    Filled " << m_name << ", "<< m_product <<" [" << m_lstItem[i]->m_itemName << "]\n";
					// the break stops from filling all items, just fills one
					break;
				}
				else {
					std::cout << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
					// the break stops from filling all items, just fills one
					// break;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; ++i) {
			os << "[" << std::setfill('0') << std::setw(6) << std::right << m_lstItem[i]->m_serialNumber << "] "
				<< std::setfill(' ') << std::setw(m_widthField)<< std::left<< m_lstItem[i]->m_itemName << " - "
				<< ((m_lstItem[i]->m_isFilled) ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}