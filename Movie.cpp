#include "Movie.h"

// Constructor demonstrating the use of 'this' pointer to disambiguate parameters from member variables
Movie::Movie(const std::string& title, const std::string& language, int durationMinutes) {
    // 'this' pointer explicitly refers to the current object instance
    this->title = title;
    this->language = language;
    this->durationMinutes = durationMinutes;
}

// Encapsulation: Getter method providing read-only access to private title
std::string Movie::getTitle() const {
    return this->title;
}

// Encapsulation: Getter method providing read-only access to private language
std::string Movie::getLanguage() const {
    return this->language;
}

// Encapsulation: Getter method providing read-only access to private duration
int Movie::getDurationMinutes() const {
    return this->durationMinutes;
}

void Movie::displayInfo() const {
    std::cout << this->title << " (" << this->language << ", " << this->durationMinutes << " mins)";
}
