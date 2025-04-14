The **database state** is the **actual data** stored in a database at a particular moment in time. This includes the collection of all the data in the database (also called database instance). You have the **initial database state** which refers to the database state when it is initially loaded into the system and the **valid state** which is a state that satisfies the structure and constraints of the database. 
⚠️The database schema changes very rarely whereas the database state changes every time the database is updated. Schema is also called intension and state is also called extension.

Data Definition Language: CREATE, ALTER, DROP, TRUNCATE

Data catalog: stores schema descriptions

disjointness constraints: can an instance of a superclass belong to multiple subclasses? if yes then overlapping else disjoint 

Constraints on specialization and generalization: 
If we can determine exactly those entities that will become members of each sub-class by a condition, the sub-classes are called **predicate-defined**. Display a predicate-defined sub-class by writing the predicate condition next to the line attaching the sub-class to its super-class. If all sub-classes in a specialization have membership condition on same attribute of the super-class, specialization is called **attribute-defined**.

select gives everything; does not eliminate duplicate tuples. (you can use DISTINCT for that)
R U S eliminates duplicates

cartesian product does not have to have type compatible operands (thus join too)

join is actually cartesian product but with select 

equijoin ($\bowtie$) (normal)
natural join (\*) has automatically equality condition on the attributes with the same name

division:
![[Pasted image 20250402184023.png]]

how grouping works:
EMPLOYEE
+-------+------+----------+-----+
|  SSN  | Name |  Salary  | DNO |
+-------+------+----------+-----+
| 11111 | John | 1000     |  10 |
| 22222 | Mary | 2000     |  10 |
| 33333 | Bob  | 1500     |  10 |
| 44444 | Jane | 3000     |  20 |
| 55555 | Dave | 4000     |  20 |
+-------+------+----------+-----+

{DNO}_$F_{COUNT SSN, AVERAGE Salary}$ (EMPLOYEE)

Group 1: DNO = 10
Rows: (11111, John, 1000, 10), (22222, Mary, 2000, 10), (33333, Bob, 1500, 10)
COUNT(SSN) = 3
AVERAGE(Salary) = (1000 + 2000 + 1500) / 3 = 1500

Group 2: DNO = 20
Rows: (44444, Jane, 3000, 20), (55555, Dave, 4000, 20)
COUNT(SSN) = 2
AVERAGE(Salary) = (3000 + 4000) / 2 = 3500



very important - learn by heart:
Mapping ER model to relational model


if there is one to many relationship then you inherit the key attributes in the many relationship. You also include the key attributes of every many to one relationship that the 1 relationship has.

if there is a weak entity then you have to underline the key attribute of the strong entity it inherits.

if there is many to many relationship you make a table with their key attributes (you underline both)

![[Pasted image 20250403104025.png]]
![[Pasted image 20250403104013.png]]

### Arithmetic operations:
try to keep the tables as small as possible (because else it will get confusing )

a relation named BRN is created like this "BRN := "

σ gives the instances that have a specific attribute condition ($σ_{attribute=10}$(ENTITY)). 
π gives all the instances of the attribute ($π_{attribute}$(ENTITY)). Note that it removes duplicates. If you want duplicates use the aggregate function COUNT
p renames
Union: to use Union $A\cup B$, A and B must have the same number of attributes and each pair of corresponding attributes must be type compatible
cross product: A X B. combination of the tuples in A and tuples in B
join: $A \bowtie_{optional condition} B$: returns a relation that combines A and B attributes (ie useful when you want an attribute of relation C with a condition on relation D)
natural join?
division: $A \div B$: when you want to find tuples in one relation that match all tuples in another relation. (ie you have name and sport in relation A, sport in relation B. division will give the students that have all the sports mentioned in B). takes all instances of one relation that correspond to all instances of another relation.



Examples:
gets all instances of EMPLOYEE who have the attribute "dno" to be 5:
dep5 <- $σ_{dno=5}$​(EMPLOYEE)

gets the pnumber of all the "PROJECTS" that have pname=ProductX
pnum <- $Π_Pnumber$​($Σ_{Pname = ′ProductX′}$(PROJECT))


will retrieve the essn of the employees who work on projectX for more than 10 hours. (pnum * pnumber gives entities of WORKS_ON that works on ProjectX )
$worksOnProject_{pssn}$ <- π(essn )(σ(hours>10)($pnum*_{Pnumber = Pno}$ WORKS_ON)


disjunct is one superclass and multiple subclasses

overlapping is that the superclass can be at the same time more than one of its subclasses

union is many superclasses and one subclass

the arrow will point down towards the subclasses

when you have only one subclass and one superclass then you don't need to name if its disjunct or union, just put arrow towards the subclass

if you have a weak entity that does not have an identifying relationship (so that it can be identified by something) then you create your own key attribute for that entity to make it total (not weak).


# Sqlite

### create
You put either NOT NULL or DEFAULT NULL. If it is foreign key and null then nothing.

whenever type is datetime, you write TIMESTAMP DEFAULT CURRENT_TIMESTAMP
(DEFAULT will make sqlite give to the attribute automatically values)

AUTOINCREMENT will put incrementing integers as values (no need to put DEFAULT after it)

NOTE: primary keys have autoincrement built in.


when the data type has custom values (or strings i guess) then you do this:
EventType TEXT NOT NULL CHECK(EventType IN ('Main', 'Reception', 'Dinner')),

Foreign keys:
CREATE TABLE Weddings(
WeddingID INTEGER NOT NULL PRIMARY KEY,
Groom INTEGER NOT NULL,
Bride INTEGER NOT NULL,
FOREIGN KEY (Groom) REFERENCES Users(UserID) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY (Bride) REFERENCES Users(UserID) ON DELETE CASCADE ON UPDATE CASCADE
);

### insert
INSERT INTO Users(Name, BirthDate, Gender, Education, CurrentLocation, Hometown)
VALUES ('John Doe', '1990-05-15', 'Male', 'Bachelor', 'New York', 5);

### update
UPDATE CateringServices SET Price = 10 WHERE Name = 'Delicious Catering';
### delete
DELETE FROM WeddingEvents
WHERE Location = 'Miami';

### select
SELECT Name, Genre FROM MusicBands;

### triggers
syntax:
```
CREATE TRIGGER trigger_name
[BEFORE|AFTER] [INSERT|UPDATE|DELETE]
ON table_name
[FOR EACH ROW]
BEGIN
    -- One or more SQL statements
END;

```

OLD.columnName is the column’s value before the change
NEW.columnName is the column’s value after the change

If you want to prevent an action (for example, if a condition fails), you can do:
```
SELECT RAISE(ABORT, 'Some error message') 
WHERE <some condition>;
```

example:
```
CREATE TRIGGER UserUpdateAuditTrigger
AFTER UPDATE
ON Users
FOR EACH ROW
BEGIN
    INSERT UserAudit(UserID, Action) VALUES (OLD.UserID, 'UPDATE');
END;
```

```
CREATE TRIGGER PreventDeleteCascadeTrigger
BEFORE DELETE
ON Users
FOR EACH ROW
BEGIN
    SELECT RAISE(ABORT, 'cannot delete user. They are groom or bride')
    WHERE EXISTS (
        SELECT 1
        FROM Weddings
        WHERE Weddings.Groom = OLD.UserID
           OR Weddings.Bride = OLD.UserID
    );
END;
```

```
CREATE TRIGGER EventConflictCHeckTrigger
BEFORE INSERT
ON WeddingEvents
FOR EACH ROW
BEGIN
	SELECT RAISE(ABORT, 'Time conflict: overlapping event')
    WHERE EXISTS (
        SELECT 1
        FROM WeddingEvents
        WHERE WeddingID = NEW.WeddingID
          AND EventDate = NEW.EventDate
          AND (NEW.EventStartTime < EventEndTime 
               AND NEW.EventEndTime   > EventStartTime)
    );
END;
```

### VIEWS 
syntax:
```
CREATE VIEW view_name AS
SELECT ...
FROM ...
WHERE ...;

```
After creation, you can query it exactly like a table:
SELECT * FROM view_name;

δεν το καταλαβα την ασκηση. νομιζω οτι αυτο κανεις οταν εχεις foreign keys και θες να κανεις access
```
CREATE VIEW WeddingDetails AS
SELECT 
    w.WeddingID,
    g.Name,
    b.Name
FROM Weddings AS w
JOIN Users AS g 
    ON w.Groom = g.UserID
JOIN Users AS b 
    ON w.Bride = b.UserID;

```

### retrieval
B Retrieves the names of users along with the names of the music bands performing at the ”Reception” event of their weddings.
```
SELECT u.Name,
       mb.Name
FROM   Weddings w
       JOIN WeddingEvents e   ON w.WeddingID = e.WeddingID
       JOIN Users u ON (w.Groom = u.UserID OR w.Bride = u.UserID)
       JOIN MusicBands mb     ON e.MusicBandID = mb.MusicBandID
WHERE  e.EventType = 'Reception';
```




some more things:


CREATE TABLE Teacher(
    PNr INT NOT NULL,
    Name VARCHAR(20) NOT NULL,
    Gender VARCHAR(1) CHECK (Gender IN ('m', 'f')),
    City VARCHAR(20),
    Year INT,
    PRIMARY KEY (PNr)
);


CREATE TABLE is_teacher_of(
    Class_KNr INT NOT NULL,
    Subject-SName VARCHAR(30) NOT NULL,
    Teacher_PNr INT NOT NULL,
    N-of-Students INT,
    PRIMARY KEY (Class_KNr, Subject-SName),
    FOREIGN KEY (Class_KNr) REFERENCES Class(KNr),
    FOREIGN KEY (Subject-SName) REFERENCES Subject(SName),
    FOREIGN KEY (Teacher_PNr) REFERENCES Teacher(PNr)
);
