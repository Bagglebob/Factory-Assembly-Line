// Name: Fawad Arshad
// Student ID: 030815153
// Date: Nov 29, 2024

// I declare that this submission is the result of my own work and I only copied the code that 
// my professor provided to complete my workshops and assignments. 
// This submitted piece of work has not been shared with any other student or 3rd party content provider.


#include "LineManager.h"
#include "Utilities.h"
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace seneca {
	LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations) : m_activeLine{}, m_cntCustomerOrder{ 0 }, m_firstStation{ nullptr }
	{
		std::string workStation{};
		std::string nextStation{};
		std::string str;

		// any station that doesnt appear second is the m_firstStation
		// last station is one that doesnt have a next station in the same line
		// m_activeLine assigns stations from stations in the order of file
		std::ifstream file(filename);
		size_t delimPos = 0;
		//size_t nextDelimPos = 0;
		// If something goes wrong, this constructor reports an error
		const char* err{ "Bad file name!" };

		if (file.is_open()) {
			while (!file.eof())
			{
				std::getline(file, str);
				delimPos = str.find_first_of('|');


				workStation = str.substr(0, delimPos);
				if (delimPos != std::string::npos) {
					nextStation = str.substr(delimPos + 1);
				}

				std::for_each(stations.begin(), stations.end(), [workStation, stations, nextStation, this](Workstation* workstation) {
					if (workstation->getItemName() == workStation) {
						auto nextSt = std::find_if(stations.begin(), stations.end(), [nextStation](Workstation* station) {
							return station->getItemName() == nextStation;
							});

						if (nextSt != stations.end() && (*nextSt)->getItemName() != (workstation)->getItemName()) {
							workstation->setNextStation(*nextSt);
						}
						m_activeLine.push_back(workstation);
						return;
					}
					});
				// ORIGINAL LOOP
				/*
				for (auto it : stations) {
					// find station with matching name in stations
					if (it->getItemName() == workStation) {
						// find the next station
						auto nextSt = std::find_if(stations.begin(), stations.end(), [nextStation](Workstation* station) {
							return station->getItemName() == nextStation;
							});

						if (nextSt != stations.end() && (*nextSt)->getItemName() != (it)->getItemName()) {
							it->setNextStation(*nextSt);
						}
						m_activeLine.push_back(it);
						break;
					}
				}
				*/
				// ORIGINAL LOOP
					// 1. find next station for each station
					// 2. then search for the first station 
					// (the first station is one which isnt the nextStation for any station)
					// foreach station x, find if there is another station y where y.nextStation() == x
					// if there is such a y, then x is not the one im looking for.
					// try with loops first	
			}

			// FIND THE FIRST STATION
			/*
			for (auto it : m_activeLine) {
				bool isFirstStation = true;

				// check if any station has it as a nextStation
				for (auto it2 : m_activeLine) {
					if (it2->getNextStation() == it) {
						isFirstStation = false;
						break; // if we find it as a nextStation, it's not the first station
					}
				}

				// if it wasn't found as a nextStation for any other station, it's the first station
				if (isFirstStation) {
					m_firstStation = it;
					break;
				}
			}
			// FIND THE FIRST STATION
			*/
			// redone with algorithms
			bool isFirstStation = true;
			std::for_each(m_activeLine.begin(), m_activeLine.end(), [this, &isFirstStation](Workstation* workStation) {
				// using find_if to break the loop instead of a break
				// find if workstation from for_each has a nextStation which is workstation
				// if not then returns m_activeLine.end()
				auto it = std::find_if(m_activeLine.begin(), m_activeLine.end(),
				[workStation](Workstation* workStation2) {
						return workStation2->getNextStation() == workStation;
					});
			// if it wasn't found as a nextStation for any other station, it's the first station
					if (it == m_activeLine.end()) {
						m_firstStation = workStation;
						return; 
					}
				});

			m_cntCustomerOrder = g_pending.size();
		}
		// If something goes wrong, this constructor reports an error
		else { throw err; }
	}

	void LineManager::reorderStations()
	{
		std::vector<Workstation*> reorderedStations;
		reorderedStations.push_back(m_firstStation);

		size_t index = 0;
		while (reorderedStations[index]->getNextStation() != nullptr) {
			for (auto it2 : m_activeLine) {
				if (it2->getItemName() == reorderedStations[index]->getNextStation()->getItemName()) {
					reorderedStations.push_back(it2);
					// stop searching and adding, once the next station is found
					break;
				}
			}
			++index;
		}

		m_activeLine.clear();
		for (auto it3 : reorderedStations) {
			m_activeLine.push_back(it3);
		}
	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t itNum = 0;


		++itNum;
		os << "Line Manager Iteration: " << itNum << std::endl;

		if (!g_pending.empty()) {
			// moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		// added this loop
		for (auto& it : m_activeLine) {
			// WHY IS THE FIRST M_ORDER IN ACTIVELINE THE ONLY ONE WITH ORDERS?
			it->fill(os);
		}
		// added this loop
		for (auto& it : m_activeLine) {
			it->attemptToMoveOrder();
		}
		// before I had 1 loop for move and fill		
	// return true if all customer orders have been filled or cannot be filled, otherwise returns false.
		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;

	}

	void LineManager::display(std::ostream& os) const
	{
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* station) {
			station->display(os);
			});
	}

	// recently added
	LineManager::~LineManager()
	{
		/*m_activeLine.clear();
		delete m_firstStation;
		m_firstStation = nullptr;*/
	}
}