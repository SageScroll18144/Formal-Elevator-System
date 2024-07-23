/* MTemp
 * Author: ffss
 * Creation date: 22/07/24
 */
MACHINE
    MTemp

VARIABLES
    counter

INVARIANT
    counter : NAT

INITIALISATION
    counter := 0

OPERATIONS
    add(number) = 
    PRE
        number : NAT &
        counter < 1000
    THEN
        counter := counter + number 
    END
    
    

END
