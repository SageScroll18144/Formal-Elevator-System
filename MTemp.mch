/* MTemp
 * Author: ffss
 * Creation date: 22/07/24
 */
MACHINE
    MTemp

VARIABLES
    counter,
    set_t

INVARIANT
    counter : NAT
    & set_t : (0..8) --> NAT

INITIALISATION
    counter := 0
    || set_t := (0..8) * {1}
    
OPERATIONS
    add(number) = 
    PRE
        number : NAT &
        counter < 1000
    THEN
        counter := counter + number 
    END;
    
    ss <-- getCard = 
    BEGIN
        ss := card(dom(set_t))
    END
    

END
