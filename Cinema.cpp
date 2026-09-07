#include "Cinema.h"

Cinema::Cinema(const std::string& cinemaName) {
    this->cinemaName = cinemaName;
}

std::string Cinema::getCinemaName() const {
    return this->cinemaName;
}

// Composition: Cinema manages the lifetime of Screen instances
void Cinema::addScreen(const Screen& screen) {
    this->screens.push_back(screen);
}

const std::vector<Screen>& Cinema::getScreens() const {
    return this->screens;
}

Screen* Cinema::findScreen(int screenNumber) {
    for (auto& screen : this->screens) {
        if (screen.getScreenNumber() == screenNumber) {
            return &screen;
        }
    }
    return nullptr;
}

const Screen* Cinema::findScreen(int screenNumber) const {
    for (const auto& screen : this->screens) {
        if (screen.getScreenNumber() == screenNumber) {
            return &screen;
        }
    }
    return nullptr;
}
