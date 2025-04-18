CREATE TABLE Users(
UserID INTEGER NOT NULL Primary Key, 
Name TEXT NOT NULL, 
BirthDate TEXT DEFAULT NULL,
Gender TEXT DEFAULT NULL, 
Education TEXT DEFAULT NULL,  
CurrentLocation TEXT DEFAULT NULL, 
Hometown TEXT DEFAULT NULL
);

CREATE TABLE Weddings(
WeddingID INTEGER NOT NULL PRIMARY KEY,
Groom INTEGER NOT NULL,
Bride INTEGER NOT NULL,
FOREIGN KEY (Groom) REFERENCES Users(UserID) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY (Bride) REFERENCES Users(UserID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE CateringServices(
CateringServiceID INTEGER NOT NULL PRIMARY KEY,
Name TEXT NOT NULL,
Contact TEXT NOT NULL,
Price REAL DEFAULT 0.0
);

CREATE TABLE MusicBands(
MusicBandID INTEGER NOT NULL PRIMARY KEY,
Name TEXT NOT NULL,
Genre TEXT DEFAULT NULL,
Contact TEXT NOT NULL,
Price REAL DEFAULT 0.0
);

CREATE TABLE WeddingHalls(
HallID INTEGER NOT NULL PRIMARY KEY,
Name TEXT NOT NULL,
Location TEXT NOT NULL,
Capacity INTEGER NOT NULL,
Price REAL DEFAULT 0.0
);

CREATE TABLE InvitationCardTemplates(
TemplateID INTEGER NOT NULL PRIMARY KEY,
Theme TEXT DEFAULT NULL,
PoemOrText TEXT DEFAULT NULL
);

CREATE TABLE InvitationCards(
InvitationID INTEGER NOT NULL PRIMARY KEY,
WeddingID INTEGER NOT NULL,
TemplateID INTEGER NOT NULL,
RecipientName TEXT DEFAULT NULL,
Note TEXT DEFAULT NULL,
FOREIGN KEY (TemplateID) REFERENCES InvitationCardTemplates(TemplateID) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY (WeddingID) REFERENCES Weddings(WeddingID) ON DELETE CASCADE ON UPDATE CASCADE
);


CREATE TABLE WeddingEvents(
EventID INTEGER NOT NULL PRIMARY KEY,
WeddingID INTEGER NOT NULL,
EventType TEXT NOT NULL CHECK(EventType IN ('Main', 'Reception', 'Dinner')) DEFAULT 'Main',
EventDate DATE NOT NULL,
EventStartTime TIME NOT NULL,
EventEndTime TIME NOT NULL,
Location TEXT NOT NULL,
MusicBandID INTEGER,
CateringServiceID INTEGER,
HallID INTEGER,
FOREIGN KEY (HallID) REFERENCES WeddingHalls(HallID) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY (CateringServiceID) REFERENCES CateringServices(CateringServiceID) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY (MusicBandID) REFERENCES MusicBands(MusicBandID) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY (WeddingID) REFERENCES Weddings(WeddingID) ON DELETE CASCADE ON UPDATE CASCADE
);