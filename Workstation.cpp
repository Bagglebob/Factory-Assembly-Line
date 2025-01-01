#include "Workstation.h"
#include <iostream>

namespace seneca {
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string& str) : Station(str), m_orders{}, m_pNextStation{ nullptr }
    {}


    void Workstation::fill(std::ostream& os)
    {        
        if (!m_orders.empty()) {
            auto& it = m_orders.front();
            // Previously: if (!it.isOrderFilled())
            // Previously: while (!it.isOrderFilled() && this->getQuantity() > 0) 
            // REMOVED IF STATEMENT
            //if(!it.isOrderFilled() && this->getQuantity() > 0) {
                it.fillItem(*this, os);
            //}
        }
    }

    bool Workstation::attemptToMoveOrder()
    {
        if (m_orders.empty()) {
            //throw std::string("ERROR: No orders to process!!");
            return false; // No orders to process
        }
        
        bool moved = false;

        // if the order requires no more service at this station or cannot be filled
        // chaned from isOrderFilled to isItemFilled
        if (m_orders.front().isItemFilled(getItemName()) || this->getQuantity() == 0) {
            if (m_pNextStation != nullptr) {
                // move it to the next station
                m_pNextStation->m_orders.push_back(std::move(m_orders.front()));                                
            }
            else {
                // No next station, move to the appropriate global queue
                if (m_orders.front().isOrderFilled()) {
                    g_completed.push_back(std::move(m_orders.front()));                                        
                }
                else {
                    g_incomplete.push_back(std::move(m_orders.front()));
                                        
                }
            }
            // cleaned up and moved this out of the if else
            m_orders.pop_front();
            moved = true;
        }

        return moved;      
    }

    void Workstation::setNextStation(Workstation* station = nullptr)
    {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const
    {
        if (this->getNextStation() != nullptr) {
            os << this->getItemName() << " --> " << this->getNextStation()->getItemName() << std::endl;
        }
        else {
            os << this->getItemName() << " --> End of Line" << std::endl;
        }
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
    // recently added
    Workstation::~Workstation()
    {
        /*delete m_pNextStation;
        m_pNextStation = nullptr;*/
        
        //m_orders.clear();
    }
}