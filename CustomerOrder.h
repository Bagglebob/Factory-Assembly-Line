// Name: Fawad Arshad
// Student ID: 030815153
// Date: Nov 24, 2024

// I declare that this submission is the result of my own work and I only copied the code that 
// my professor provided to complete my workshops and assignments. 
// This submitted piece of work has not been shared with any other student or 3rd party content provider.


#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include <string>
#include "Station.h"

namespace seneca {
	class CustomerOrder {		
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

		// Customer Name
		std::string m_name;
		// Product Name
		std::string m_product;
		// Number of items in Customer Order
		size_t m_cntItem;
		// dynamically allocated array of pointers. 
		// Each element of the array points to a dynamically allocated object of type Item
		// Managed by CustomerOrder class
		Item** m_lstItem;

		// CLASS VARIABLE
		static size_t m_widthField;

	public:
		CustomerOrder();

		CustomerOrder(const std::string& str);

		// DELETED OPERATIONS
		CustomerOrder(const CustomerOrder&);

		CustomerOrder& operator=(const CustomerOrder&) = delete;
		// DELETED OPERATIONS END

		// move constructor
		CustomerOrder(CustomerOrder&&) noexcept;

		// move assignment
		CustomerOrder& operator=(CustomerOrder&&) noexcept;

		~CustomerOrder();

		bool isOrderFilled() const;

		bool isItemFilled(const std::string& itemName) const;

		void fillItem(Station& station, std::ostream& os);

		void display(std::ostream& os) const;
	};
}
#endif