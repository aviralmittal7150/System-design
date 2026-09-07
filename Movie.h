#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>

// Entity Class: Movie
// Single Responsibility: Stores metadata and information about a movie only.
// Does NOT handle booking, payment, or ticket printing.
class Movie {
private:
    // Encapsulation: Private member variables protect data integrity.
    std::string title;
    std::string language;
    int durationMinutes;

public:
    Movie(const std::string& title, const std::string& language, int durationMinutes);

    // Getters for accessing encapsulated fields
    std::string getTitle() const;
    std::string getLanguage() const;
    int getDurationMinutes() const;

    void displayInfo() const;
};

#endif // MOVIE_H
