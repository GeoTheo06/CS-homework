SELECT u.Name,
       mb.Name
FROM   Weddings w
       JOIN WeddingEvents e   ON w.WeddingID = e.WeddingID
       JOIN Users u ON (w.Groom = u.UserID OR w.Bride = u.UserID)
       JOIN MusicBands mb     ON e.MusicBandID = mb.MusicBandID
WHERE  e.EventType = 'Reception';