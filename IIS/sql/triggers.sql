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