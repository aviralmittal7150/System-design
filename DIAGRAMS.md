# SYSTEM DESIGN & UML DIAGRAMS
**Movie Ticket Booking System for a Single Cinema**  
**Course**: B.Tech CSE Semester 5 | System Design & OOP  
**Author**: Aviral Mittal  
**Repository**: [aviralmittal7150/System-design](https://github.com/aviralmittal7150/System-design)

---

## 1. COMPREHENSIVE UML CLASS DIAGRAM

```mermaid
classDiagram
    direction TB

    %% Enums
    class SeatType {
        <<enumeration>>
        SILVER
        GOLD
        PLATINUM
    }

    class SeatStatus {
        <<enumeration>>
        AVAILABLE
        BOOKED
    }

    class BookingStatus {
        <<enumeration>>
        CONFIRMED
        CANCELLED
        FAILED
    }

    %% Domain Entities
    class Cinema {
        -string cinemaName
        -vector~Screen~ screens
        +Cinema(string cinemaName)
        +string getCinemaName() const
        +void addScreen(const Screen& screen)
        +const vector~Screen~& getScreens() const
        +Screen* findScreen(int screenNumber)
    }

    class Screen {
        -int screenNumber
        -vector~Seat~ seats
        +Screen(int screenNumber)
        +int getScreenNumber() const
        +string getScreenName() const
        +void addSeat(const Seat& seat)
        +const vector~Seat~& getSeats() const
        +const Seat* findSeat(string seatNumber) const
    }

    class Seat {
        -string seatNumber
        -SeatType seatType
        +Seat(string seatNumber, SeatType seatType)
        +string getSeatNumber() const
        +SeatType getSeatType() const
        +string getSeatTypeString() const
    }

    class Show {
        -int showId
        -const Movie* movie
        -const Screen* screen
        -string startTime
        -vector~ShowSeat~ showSeats
        +Show(int showId, const Movie* movie, const Screen* screen, string startTime)
        +int getShowId() const
        +const Movie* getMovie() const
        +const Screen* getScreen() const
        +string getStartTime() const
        +const vector~ShowSeat~& getShowSeats() const
        +vector~ShowSeat~& getShowSeats()
        +ShowSeat* findShowSeat(string seatNumber)
        +void displayDetails() const
        +void displaySeatLayout() const
    }

    class ShowSeat {
        -const Seat* physicalSeat
        -SeatStatus status
        +ShowSeat(const Seat* physicalSeat)
        +const Seat* getPhysicalSeat() const
        +string getSeatNumber() const
        +SeatType getSeatType() const
        +SeatStatus getStatus() const
        +bool isAvailable() const
        +bool book()
        +void release()
    }

    class Movie {
        -string title
        -string language
        -int durationMinutes
        +Movie(string title, string language, int durationMinutes)
        +string getTitle() const
        +string getLanguage() const
        +int getDurationMinutes() const
        +void displayInfo() const
    }

    class Customer {
        -string name
        -string phone
        +Customer(string name, string phone)
        +string getName() const
        +string getPhone() const
    }

    class Booking {
        -static int nextBookingId
        -string bookingId
        -Customer customer
        -const Show* show
        -vector~ShowSeat*~ bookedSeats
        -double totalAmount
        -string paymentMethod
        -BookingStatus status
        +Booking(Customer customer, const Show* show, vector~ShowSeat*~ bookedSeats, double totalAmount, string paymentMethod)
        +static void resetNextBookingId(int startId)
        +string getBookingId() const
        +const Customer& getCustomer() const
        +const Show* getShow() const
        +const vector~ShowSeat*~& getBookedSeats() const
        +double getTotalAmount() const
        +string getPaymentMethod() const
        +BookingStatus getStatus() const
        +bool cancel()
    }

    %% Payment Layer (Polymorphism & Abstraction)
    class Payment {
        <<abstract>>
        #string paymentMethodName
        +Payment(string methodName)
        +virtual ~Payment()
        +virtual bool pay(double amount)*
        +string getPaymentMethodName() const
    }

    class UpiPayment {
        -string upiId
        +UpiPayment(string upiId)
        +bool pay(double amount) override
        +string getUpiId() const
    }

    class CardPayment {
        -string cardNumber
        -string cardHolderName
        -string cvv
        +CardPayment(string cardNumber, string cardHolderName, string cvv)
        +bool pay(double amount) override
        +string getCardNumberMasked() const
    }

    class CashPayment {
        -double amountTendered
        +CashPayment(double amountTendered)
        +bool pay(double amount) override
        +double getAmountTendered() const
    }

    %% Service Layer
    class PriceCalculator {
        +static const double SILVER_PRICE = 150.0
        +static const double GOLD_PRICE = 250.0
        +static const double PLATINUM_PRICE = 400.0
        +calculatePrice(SeatType type) const double
        +calculatePrice(SeatType type, int quantity) const double
        +calculatePrice(const vector~const ShowSeat*~& seats) const double
    }

    class TicketPrinter {
        +printTicket(const Booking& booking) const void
        +printTicket(const Booking& booking, ostream& out) const void
        +printSummary(const Booking& booking) const void
    }

    class BookingService {
        -PriceCalculator priceCalculator
        -TicketPrinter ticketPrinter
        -vector~unique_ptr~Booking~~ bookings
        +createBooking(Customer cust, Show* show, vector~string~ seats, Payment* payment) Booking*
        +cancelBooking(string bookingId) bool
        +const Booking* findBooking(string bookingId) const
        +void displayAllBookings() const
    }

    %% Presentation Layer
    class CinemaApp {
        -Cinema cinema
        -vector~Movie~ movies
        -vector~unique_ptr~Show~~ shows
        -BookingService bookingService
        +CinemaApp()
        +void run()
    }

    %% Relationships
    Cinema "1" *-- "1..*" Screen : Composition (owns)
    Screen "1" *-- "1..*" Seat : Composition (owns)
    Seat -- SeatType : uses
    ShowSeat -- SeatStatus : uses
    Booking -- BookingStatus : uses
    Show "1" *-- "1..*" ShowSeat : Composition (owns)
    Show "1" o-- "1" Movie : Aggregation (references)
    Show "1" o-- "1" Screen : Aggregation (references)
    ShowSeat "1" o-- "1" Seat : Aggregation (points to)
    Booking "1" o-- "1" Customer : Aggregation (references)
    Booking "1" o-- "1" Show : Aggregation (references)
    Booking "1" o-- "1..*" ShowSeat : Aggregation (references)
    Payment <|-- UpiPayment : Inheritance (is-a)
    Payment <|-- CardPayment : Inheritance (is-a)
    Payment <|-- CashPayment : Inheritance (is-a)
    BookingService --> PriceCalculator : uses (SRP)
    BookingService --> TicketPrinter : uses (SRP)
    BookingService --> Payment : invokes pay() (DIP & Polymorphism)
    BookingService *-- Booking : manages lifetime
    CinemaApp --> BookingService : orchestrates
    CinemaApp *-- Cinema : owns
```

---

## 2. UML SEQUENCE DIAGRAM
### Scenario: "Customer books ONE seat and pays by UPI"

```mermaid
sequenceDiagram
    autonumber
    actor Customer as Customer (Aviral)
    participant UI as CinemaApp
    participant BS as BookingService
    participant S as Show
    participant SS as ShowSeat (A1)
    participant PC as PriceCalculator
    participant P as Payment (UpiPayment)
    participant B as Booking
    participant TP as TicketPrinter

    Customer->>UI: Selects Show #1, Seat "A1", Payment: UPI
    activate UI
    UI->>BS: createBooking(customer, show, ["A1"], upiPayment)
    activate BS

    %% Step 1: Validate Seat
    BS->>S: findShowSeat("A1")
    activate S
    S-->>BS: return showSeatPtr
    deactivate S

    BS->>SS: isAvailable()
    activate SS
    SS-->>BS: true (AVAILABLE)
    deactivate SS

    %% Step 2: Calculate Price
    BS->>PC: calculatePrice(selectedSeats)
    activate PC
    PC-->>BS: return totalAmount = ₹150.00
    deactivate PC

    %% Step 3: Polymorphic Payment
    Note over BS,P: Runtime Polymorphism: Payment* calls UpiPayment::pay()
    BS->>P: pay(150.00)
    activate P
    P-->>BS: true (Payment Success)
    deactivate P

    %% Step 4: Mutate Seat State
    BS->>SS: book()
    activate SS
    SS-->>BS: status = BOOKED
    deactivate SS

    %% Step 5: Instantiate Booking
    BS->>B: <<create>> Booking(customer, show, [SS], 150.00, "UPI")
    activate B
    B-->>BS: return bookingInstance (ID: B1001)
    deactivate B

    %% Step 6: Print Ticket
    BS->>TP: printTicket(bookingInstance)
    activate TP
    TP-->>Customer: Render Formatted Ticket
    deactivate TP

    BS-->>UI: return bookingPtr
    deactivate BS
    UI-->>Customer: Display Success Screen
    deactivate UI
```

---

## 3. ACTIVITY / WORKFLOW DIAGRAM (BOOKING WORKFLOW)

```mermaid
flowchart TD
    Start([User Initiates Booking]) --> InputShow[Select Movie & Show]
    InputShow --> DisplayLayout[Render Seat Layout with Status]
    DisplayLayout --> InputSeats[User Inputs Seat Numbers]
    InputSeats --> ValidateSeats{Are all seats valid & AVAILABLE?}
    
    ValidateSeats -- No --> RejectReq[Display Error: Invalid or Booked Seat]
    RejectReq --> AbortBooking([Abort Transaction - No State Change])

    ValidateSeats -- Yes --> CalcPrice[PriceCalculator Computes Total Amount]
    CalcPrice --> ChoosePayment[User Selects Payment: UPI / Card / Cash]
    ChoosePayment --> ProcessPayment[Invoke polymorphic Payment::pay]
    
    ProcessPayment --> CheckPayment{Did Payment Succeed?}
    
    CheckPayment -- No --> Rollback[Display Payment Failed Error]
    Rollback --> KeepAvailable[Seats Remain AVAILABLE - No Booking Created]
    KeepAvailable --> AbortBooking

    CheckPayment -- Yes --> LockSeats[Mark Selected ShowSeats as BOOKED]
    LockSeats --> GenBooking[Create Booking with Unique ID B1001]
    GenBooking --> PrintTicket[TicketPrinter Renders Formatted Ticket]
    PrintTicket --> EndBooking([Booking Complete & Confirmed])
```

---

## 4. STATE MACHINE DIAGRAMS

### 4.1 ShowSeat Lifecycle State Machine

```mermaid
stateDiagram-v2
    [*] --> AVAILABLE : Show Created / Initialized
    
    AVAILABLE --> BOOKED : Payment Succeeded (ShowSeat::book())
    AVAILABLE --> AVAILABLE : Payment Failed (Rollback / No Change)
    
    BOOKED --> AVAILABLE : Booking Cancelled (ShowSeat::release())
    BOOKED --> [*] : Show Screening Concluded
```

### 4.2 Booking Lifecycle State Machine

```mermaid
stateDiagram-v2
    [*] --> PENDING_PAYMENT : User selects seats
    
    PENDING_PAYMENT --> FAILED : Payment Declined (No Booking created)
    FAILED --> [*]
    
    PENDING_PAYMENT --> CONFIRMED : Payment Successful (Booking instantiated)
    
    CONFIRMED --> CANCELLED : Customer requests cancellation
    CANCELLED --> [*]
```

---

## 5. SYSTEM ARCHITECTURE & PACKAGE DIAGRAM

```mermaid
flowchart TB
    subgraph Presentation_Layer [Presentation Layer]
        CinemaApp[CinemaApp / Console Menu]
    end

    subgraph Service_Layer [Service & Business Logic Layer]
        BookingService[BookingService Orchestrator]
        PriceCalculator[PriceCalculator (SRP)]
        TicketPrinter[TicketPrinter (SRP)]
    end

    subgraph Payment_Layer [Payment Abstraction Layer (DIP / OCP / LSP)]
        Payment["«abstract» Payment"]
        UpiPayment[UpiPayment]
        CardPayment[CardPayment]
        CashPayment[CashPayment]
    end

    subgraph Domain_Layer [Domain Entities Layer (Composition / Aggregation)]
        Cinema[Cinema]
        Screen[Screen]
        Seat[Seat]
        Show[Show]
        ShowSeat[ShowSeat]
        Movie[Movie]
        Customer[Customer]
        Booking[Booking]
    end

    Presentation_Layer --> Service_Layer
    Presentation_Layer --> Domain_Layer
    Service_Layer --> Payment_Layer
    Service_Layer --> Domain_Layer
    Payment_Layer <|-- UpiPayment
    Payment_Layer <|-- CardPayment
    Payment_Layer <|-- CashPayment
```
