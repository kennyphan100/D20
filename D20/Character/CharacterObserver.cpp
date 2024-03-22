//! @file 
//! @brief Implementation file for CharacterObserver.h
//!

#include "CharacterObserver.h"
#include "CharacterBuilder.h"

#include <iostream>
#include <fstream>

using namespace std;

//! Destructor for CharacterObserver class.
//! Detaches the observer from the subject and sets the subject pointer to null.
CharacterObserver::~CharacterObserver()
{
	_subject->detach(this);
	_subject = NULL;
}

//! Constructor for CharacterObserver class.
//! Attaches the observer to the specified character subject.
//! @param c Pointer to the character subject to observe.
CharacterObserver::CharacterObserver(Character* c)
{
	_subject = c;
	_subject->attach(this);
}

CharacterObserver::CharacterObserver(CharacterBuilder* c)
{
    _subject2 = c;
    _subject2->attach(this);
}

CharacterObserver::CharacterObserver(CharacterDirector* c)
{
    _subject3 = c;
    _subject3->attach(this);
}

//! Update method called when the observed subject notifies the observer.
//! Prints the updated character information.
//! @param o Pointer to the observable subject.
void CharacterObserver::update(Observable* o)
{
	if (_subject == o)
	{
		cout << "==================== Character Update ====================" << endl;
		_subject->printCharacter();
		cout << "\n";
	}
}

void CharacterObserver::log(Observable* o) {
    ofstream logFile("./game_log.txt", ios::app);

    if (_subject == o) {
        if (logFile.is_open()) {
            logFile << "============ Character Update ============" << endl;
            _subject->logCharacter(logFile);
            logFile << "\n";
            logFile.close();
        }
        else {
            cerr << "Unable to open log file." << endl;
        }
    }

    if (_subject2 == o) {
        if (logFile.is_open()) {
            logFile << "============ Character Creation ============" << endl;
            _subject2->logCharacter(logFile);
            logFile << "\n";
            logFile.close();
        }
        else {
            cerr << "Unable to open log file." << endl;
        }
    }
}
