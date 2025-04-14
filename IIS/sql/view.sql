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
