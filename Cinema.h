#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>
#include <memory>
#include "Screen.h"

// Entity Class: Cinema
// Responsibility: Represents the physical movie theatre.
// Demonstrates Composition: Cinema owns its Screen objects.
// Lifetime Test: If Cinema is demolished/destroyed, all screens inside it are destroyed.
class Cinema {
private:
    // Encapsulation: Private member data
    std::string cinemaName;
    // Composition: Cinema owns Screen objects
    std::vector<Screen> screens;

public:
    explicit Cinema(const std::string& cinemaName);

    std::string getCinemaName() const;
    void addScreen(const Screen& screen);
    const std::vector<Screen>& getScreens() const;
    Screen* findScreen(int screenNumber);
    const Screen* findScreen(int screenNumber) const;
};

#endif // CINEMA_H
