--TableName: Column1, Column2, ..
--(Records)
INSERT INTO Users(Name, BirthDate, Gender, Education, CurrentLocation, Hometown)
VALUES
    ('John Doe', '1990-05-15', 'Male', 'Bachelor', 'New York', 'Los Angeles'),
    ('Jane Smith', '1985-10-20', 'Female', 'Master', 'Los Angeles', 'Chicago'),
    ('Alice Johnson', '1995-02-28', 'Female', 'Bachelor', 'Chicago', 'New York'),
    ('Michael Brown', '1982-09-10', 'Male', 'PhD', 'Houston', 'Dallas'),
    ('Emily Davis', '1993-07-05', 'Female', 'Bachelor', 'Miami', 'Orlando'),
    ('William Wilson', '1988-03-20', 'Male', 'Bachelor', 'Boston', 'Seattle'),
    ('Sophia Garcia', '1987-11-12', 'Female', 'Master', 'San Francisco', 'Los Angeles'),
    ('Jacob Martinez', '1992-06-30', 'Male', 'Bachelor', 'Dallas', 'San Antonio'),
    ('Olivia Anderson', '1986-04-18', 'Female', 'PhD', 'Chicago', 'New York'),
    ('Daniel Rodriguez', '1990-09-08', 'Male', 'Bachelor', 'Los Angeles', 'San Diego');


INSERT INTO Weddings(Groom, Bride)
VALUES    (1, 2),
    (3, 4),
    (5, 6),
    (7, 8),
    (9, 10);


WeddingEvents: WeddingID, EventType, EventDate, EventStartTime, EventEndTime, Location, MusicBandID, CateringServiceID, HallID
    (1, 'Main', '2024-06-15', '17:00', '18:00', 'New York City Hall', NULL, NULL, NULL),
    (1, 'Reception', '2024-06-15', '18:00', '20:00', 'Central Park', NULL, 1, 1),
    (2, 'Main', '2024-07-20', '16:00', '17:30', 'Chicago Botanic Garden', 1, 2, 2),
    (2, 'Reception', '2024-07-20', '18:00', '20:30', 'Chicago Botanic Garden', 2, 2, 2),
    (3, 'Main', '2024-08-25', '18:00', '19:00', 'Houston Country Club', NULL, 3, 3),
    (3, 'Reception', '2024-08-25', '19:00', '21:00', 'Houston Country Club', 3, 3, 3),
    (4, 'Main', '2024-09-30', '15:30', '17:00', 'Miami Beach Resort', NULL, 4, 4),
    (4, 'Reception', '2024-09-30', '17:30', '20:00', 'Miami Beach Resort', 4, 4, 4),
    (5, 'Main', '2024-10-05', '14:00', '15:30', 'Boston Harbor Hotel', NULL, 5, 5),
    (5, 'Reception', '2024-10-05', '16:00', '18:00', 'Boston Harbor Hotel', 5, 5, 5);
	
CateringServices: Name, Contact, Price
    ('Delicious Catering', 'contact@deliciouscatering.com', 5000),
    ('Elegant Events Catering', 'info@elegantevents.com', 7500),
    ('Gourmet Galore Caterers', 'sales@gourmetgalore.com', 6000),
    ('Savor the Flavor Catering', 'hello@savortheflavor.com', 5500),
    ('Tasty Treats Catering', 'orders@tastytreats.com', 4800);
	

MusicBands: Name, Genre, Contact, Price
    ('The Wedding Singers', 'Pop, Rock', 'bookings@weddingsingers.com', 3000),
    ('Smooth Jazz Trio', 'Jazz', 'info@smoothjazztrio.com', 2500),
    ('Classical Ensemble', 'Classical', 'contact@classicalensemble.com', 2000),
    ('Salsa Rhythms Band', 'Latin', 'salsarhythms@gmail.com', 2800),
    ('Country Serenade', 'Country', 'bookings@countryserenade.com', 2200);
	
WeddingHalls: Name, Location, Capacity, Price
    ('Grand Ballroom', 'New York', 200, 8000),
    ('Garden Pavilion', 'Chicago', 150, 6000),
    ('Lakeview Terrace', 'Houston', 180, 7000),
    ('Oceanfront Hall', 'Miami', 250, 9000),
    ('Harbor View Room', 'Boston', 180, 7000);


InvitationCardTemplates: Theme, PoemOrText
    ('Classic Elegance', 'You are cordially invited to celebrate the union of...'),
    ('Rustic Charm', 'Join us for an intimate gathering to celebrate...'),
    ('Modern Minimalist', 'Save the date for the wedding of...'),
    ('Vintage Romance', 'Love is in the air! Join us for the wedding of...'),
    ('Tropical Paradise', 'Escape to paradise with us as we exchange vows...');


InvitationCards: WeddingID, TemplateID, RecipientName, Note
    (1, 1, 'Alice Johnson', 'Please join us in celebrating the wedding of John and Jane.'),
    (1, 1, 'Michael Brown', 'You are invited to witness the union of John and Jane.'),
    (2, 2, 'Andrew Wilson', 'Join us for an unforgettable evening of love and joy.'),
    (2, 2, 'Jessica Davis', 'You are cordially invited to the wedding of Emily and Michael.'),
    (3, 3, 'William Wilson', 'Save the date for the wedding of Emily and Michael.'),
    (3, 3, 'Sarah Lee', 'Join us in celebrating the love of Emily and Michael.'),
    (4, 4, 'Sophia Garcia', 'Please join us for a beachside wedding celebration.'),
    (4, 4, 'Jacob Martinez', 'You are invited to witness the marriage of Emily and Michael.'),
    (5, 5, 'Olivia Anderson', 'Join us as we celebrate the union of Emily and Michael.'),
    (5, 5, 'Daniel Rodriguez', 'You are cordially invited to the wedding of Emily and Michael.');



