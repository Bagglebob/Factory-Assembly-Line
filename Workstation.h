#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include "Station.h"
#include "CustomerOrder.h"
#include <deque>
#include <string>

namespace seneca {
	// Pending Orders || orders to be placed onto the assembly line at the first station
	extern std::deque<CustomerOrder> g_pending;
	// Filled Orders || orders that have been removed from the last station and have been completely filled
	extern std::deque<CustomerOrder> g_completed;
	// Unfullfilled Orders || orders that have been removed from the last station and could not be filled completely
	extern std::deque<CustomerOrder> g_incomplete;

	// Workstation manages order processing for a single Item on the assembly line
	
	class Workstation :public Station {
		// These are orders that have been placed on this station to receive service (or already received service)
		std::deque<CustomerOrder> m_orders;

		// pointer to the next Workstation on the assembly line
		Workstation* m_pNextStation;

	public:
		Workstation(const std::string& str);

		void fill(std::ostream& os);

		bool attemptToMoveOrder();

		void setNextStation(Workstation* station);

		Workstation* getNextStation() const;

		void display(std::ostream& os) const;

		Workstation& operator+=(CustomerOrder&& newOrder);

		// Workstation CANNOT BE COPIED OR MOVED
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		// destructor
		~Workstation();
	};
}
#endif