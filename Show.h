#ifndef SHOW_H
#define SHOW_H

#include <string>
#include <vector>
#include "Movie.h"
#include "Screen.h"
#include "ShowSeat.h"

// Entity Class: Show
// Responsibility: Represents a single screening event connecting a Movie, a Screen, and a Start Time.
// Relationships:
// - Aggregation with Movie (Show has-a Movie reference; Movie exists independently).
// - Aggregation with Screen (Show has-a Screen reference; Screen exists independently).
// - Composition with ShowSeat (Show owns its ShowSeat collection; when Show ends/deleted, show seats are destroyed).
class Show {
private:
    int showId;
    // Aggregation: Show references existing Movie and Screen objects
    const Movie* movie;
    const Screen* screen;
    std::string startTime;
    // Composition: Show owns its ShowSeat instances
    std::vector<ShowSeat> showSeats;

public:
    Show(int showId, const Movie* movie, const Screen* screen, const std::string& startTime);

    int getShowId() const;
    const Movie* getMovie() const;
    const Screen* getScreen() const;
    std::string getStartTime() const;

    const std::vector<ShowSeat>& getShowSeats() const;
    std::vector<ShowSeat>& getShowSeats();
    ShowSeat* findShowSeat(const std::string& seatNumber);
    const ShowSeat* findShowSeat(const std::string& seatNumber) const;

    void displayDetails() const;
    void displaySeatLayout() const;
};

#endif // SHOW_H
