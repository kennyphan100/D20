//! @file 
//! @brief Implementation file for MapObserver.h
//!

#include "MapObserver.h"

#include <iostream>
#include <fstream>

//! @brief Destructor for MapObserver.
//! Detaches itself from the subject and sets the subject pointer to null.
MapObserver::~MapObserver()
{
	_subject->detach(this);
	_subject = NULL;
}

//! @brief Constructor for MapObserver.
//! Attaches itself to the subject.
//! @param c The subject to observe.
MapObserver::MapObserver(Map* c)
{
	_subject = c;
	_subject->attach(this);
}

//! @brief Update method for MapObserver.
//! Updates the observer when notified by the subject.
//! @param o The observable object that triggered the update.
void MapObserver::update(Observable* o)
{
	if (_subject == o)
	{
		cout << "==================== Map Update ====================" << endl;
		_subject->display();
		cout << "\n";
	}
}

void MapObserver::log(Observable* o) {
    std::ofstream logFile("game_log.txt", std::ios::app); // Open the log file in append mode

    if (_subject == o) {
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Map Update ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            _subject->logMap(logFile); // This needs to be adjusted based on how printCharacter is implemented
            logFile << "\n";
            logFile.close(); // Close the file
        }
        else {
            std::cerr << "Unable to open log file." << std::endl;
        }
    }
}
