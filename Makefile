CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

SRCS = Movie.cpp Seat.cpp Screen.cpp Cinema.cpp ShowSeat.cpp Show.cpp Customer.cpp \
       Payment.cpp UpiPayment.cpp CardPayment.cpp CashPayment.cpp \
       PriceCalculator.cpp TicketPrinter.cpp Booking.cpp BookingService.cpp CinemaApp.cpp

OBJS = $(SRCS:.cpp=.o)
MAIN = main.cpp
TARGET = movie_booking_system
TEST_TARGET = test_runner

all: $(TARGET)

$(TARGET): $(OBJS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(OBJS) test_suite.o
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $^
	./$(TEST_TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
