-- Table for purchase 
CREATE TABLE PURCHASE
(
	PURCHASE_ID INTEGER PRIMARY KEY AUTO_INCREMENT,
	PURCHASE_DESC VARCHAR(50),
    PURCHASE_PRICE NUMERIC(8,2),
    PURCHASE_PLATFORM VARCHAR(10),
    PURCHASE_DATE DATE,
    PURCHASE_NUM_OF_ITEMS INTEGER,
    PURCHASE_EST_NET NUMERIC(8,2),
    PURCHASE_ACTUAL_PROFIT NUMERIC(8,2)
);
-- Table for item
CREATE TABLE ITEM
(
	ITEM_NUM INTEGER PRIMARY KEY AUTO_INCREMENT,
    PURCHASE_ID INTEGER,
    ITEM_NAME VARCHAR(50) NOT NULL,
    ITEM_EST_PRICE NUMERIC(8,2) NOT NULL,
    ITEM_EST_NET NUMERIC(8,2),
    ITEM_STATUS VARCHAR(20) NOT NULL,
	ITEM_PLATFORM VARCHAR(20),
    ITEM_SALE_PRICE NUMERIC(8,2),
    ITEM_SHIPPING_PRICE NUMERIC(4,2),
    ITEM_SALE_PLATFORM VARCHAR(20),
    ITEM_ACTUAL_PROFIT NUMERIC(8,2),
    ITEM_IS_AFFILIATE VARCHAR(4),
    ITEM_AFFILIATE_NAME VARCHAR(50),
    ITEM_AFFILIATE_GAIN NUMERIC(8,2),
    CONSTRAINT FOREIGN KEY (PURCHASE_ID) REFERENCES PURCHASE(PURCHASE_ID)
);
-- Procedure to add a purchase to the purchase table
DELIMITER //

CREATE PROCEDURE ADD_PURCHASE(PURCHASE_ID_IN INTEGER, PURCHASE_DESC_IN VARCHAR(50),PURCHASE_PRICE_IN NUMERIC(8,2),
							  PURCHASE_PLATFORM_IN VARCHAR(10),PURCHASE_DATE_IN DATE)
BEGIN
	
    INSERT INTO PURCHASE (PURCHASE_ID,PURCHASE_DESC,PURCHASE_PRICE,PURCHASE_PLATFORM,PURCHASE_DATE,PURCHASE_ACTUAL_PROFIT,PURCHASE_NUM_OF_ITEMS,PURCHASE_EST_NET) 
    VALUES (PURCHASE_ID_IN,PURCHASE_DESC_IN,PURCHASE_PRICE_IN,PURCHASE_PLATFORM_IN,PURCHASE_DATE_IN,-PURCHASE_PRICE_IN,0,-PURCHASE_PRICE_IN);
    
END; //
-- Procedure to add an item to the item table 
DELIMITER //

CREATE PROCEDURE ADD_ITEM(ITEM_NUM_IN INTEGER, PURCHASE_ID_IN INTEGER,ITEM_NAME_IN VARCHAR(50),ITEM_EST_PRICE_IN NUMERIC(8,2),
                          ITEM_STATUS_IN VARCHAR(20), ITEM_PLATFORM_IN VARCHAR(20))

BEGIN

	DECLARE est_net NUMERIC(8,2);

	IF ITEM_PLATFORM_IN LIKE 'Mercari%' THEN
    SET est_net = (ITEM_EST_PRICE_IN - (ITEM_EST_PRICE_IN * 0.10) - 5.00);
    
    ELSEIF ITEM_PLATFORM_IN LIKE 'Amazon%' THEN
    SET est_net = (ITEM_EST_PRICE_IN - (ITEM_EST_PRICE_IN * 0.15) - 5.80);
    
    ELSEIF ITEM_PLATFORM_IN LIKE 'OfferUp%' THEN
    SET est_net = ITEM_EST_PRICE_IN;
    
    END IF;

	INSERT INTO ITEM (ITEM_NUM,PURCHASE_ID,ITEM_NAME,ITEM_EST_PRICE,ITEM_EST_NET,ITEM_STATUS,ITEM_PLATFORM) 
    VALUES (ITEM_NUM_IN,PURCHASE_ID_IN,ITEM_NAME_IN,ITEM_EST_PRICE_IN,est_net,ITEM_STATUS_IN,ITEM_PLATFORM_IN);
    
END; //

DELIMITER ;

DELIMITER //

CREATE TRIGGER TRG_ITEM_INSERT
BEFORE INSERT ON ITEM
FOR EACH ROW

BEGIN

	UPDATE PURCHASE
    SET PURCHASE_EST_NET = PURCHASE_EST_NET + NEW.ITEM_EST_NET
    WHERE NEW.PURCHASE_ID = PURCHASE.PURCHASE_ID;
    
    UPDATE PURCHASE
    SET PURCHASE_NUM_OF_ITEMS = PURCHASE_NUM_OF_ITEMS + 1
    WHERE NEW.PURCHASE_ID = PURCHASE.PURCHASE_ID;

END; //

DELIMITER ;

DELIMITER // 

CREATE PROCEDURE SET_SOLD(ITEM_NUM_IN INTEGER,PURCHASE_ID_IN INTEGER, ITEM_SALE_PRICE_IN NUMERIC(8,2), 
						  ITEM_SHIPPING_PRICE_IN NUMERIC(8,2),ITEM_SALE_PLATFORM_IN VARCHAR(20))
BEGIN

    
	UPDATE ITEM
    SET ITEM_SALE_PRICE = ITEM_SALE_PRICE_IN
    WHERE ITEM_NUM_IN = ITEM.ITEM_NUM;
    
    UPDATE ITEM
    SET ITEM_SHIPPING_PRICE = ITEM_SHIPPING_PRICE_IN
    WHERE ITEM_NUM_IN = ITEM.ITEM_NUM;
    
    UPDATE ITEM
    SET ITEM_SALE_PLATFORM = ITEM_SALE_PLATFORM_IN
    WHERE ITEM_NUM_IN = ITEM.ITEM_NUM;
    
    UPDATE ITEM 
    SET ITEM_STATUS = 'Sold'
    WHERE ITEM_NUM_IN = ITEM.ITEM_NUM;
    
    IF ITEM_SALE_PLATFORM_IN LIKE 'Mercari%' THEN
    UPDATE ITEM
    SET ITEM_ACTUAL_PROFIT = (ITEM_SALE_PRICE_IN - (ITEM_SALE_PRICE_IN * 0.10) - ITEM_SHIPPING_PRICE_IN)
    WHERE ITEM_NUM_IN = ITEM.ITEM_NUM;
    
    UPDATE PURCHASE 
    SET PURCHASE_ACTUAL_PROFIT = PURCHASE_ACTUAL_PROFIT + 
								 (ITEM_SALE_PRICE_IN - (ITEM_SALE_PRICE_IN * 0.10) - ITEM_SHIPPING_PRICE_IN)
	WHERE PURCHASE_ID_IN = PURCHASE.PURCHASE_ID;
    
    ELSEIF ITEM_SALE_PLATFORM_IN LIKE 'Amazon%' THEN
    UPDATE ITEM
    SET ITEM_ACTUAL_PROFIT = (ITEM_SALE_PRICE_IN - (ITEM_SALE_PRICE_IN * 0.15) - ITEM_SHIPPING_PRICE_IN - 1.80)
    WHERE ITEM_NUM_IN = ITEM.ITEM_NUM;
    
    UPDATE PURCHASE 
    SET PURCHASE_ACTUAL_PROFIT = PURCHASE_ACTUAL_PROFIT + 
								 (ITEM_SALE_PRICE_IN - (ITEM_SALE_PRICE_IN * 0.15) - ITEM_SHIPPING_PRICE_IN - 1.80)
	WHERE PURCHASE_ID_IN = PURCHASE.PURCHASE_ID;
    
    ELSEIF ITEM_SALE_PLATFORM_IN LIKE 'OfferUp%' THEN
    UPDATE ITEM
    SET ITEM_ACTUAL_PROFIT = ITEM_SALE_PRICE_IN
    WHERE ITEM_NUM_IN = ITEM.ITEM_NUM;
    
    UPDATE PURCHASE 
    SET PURCHASE_ACTUAL_PROFIT = PURCHASE_ACTUAL_PROFIT + ITEM_SALE_PRICE_IN
	WHERE PURCHASE_ID_IN = PURCHASE.PURCHASE_ID;
    
    END IF;
    
END; //

DELIMITER ;

DELIMITER //

CREATE PROCEDURE ITEM_LIST(ITEM_NUM_IN INTEGER)

BEGIN

	UPDATE ITEM
    SET ITEM_STATUS = 'Active'
    WHERE ITEM_NUM_IN = ITEM.ITEM_NUM;
    
END; //

DELIMITER ;

DELIMITER //
	
    
