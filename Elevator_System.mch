/* Elevator_System
 * Author: Felipe Santos, Victor Mendonça, Roberto Albuquerque
 * Creation date: 08/06/24
 * 
 * TODO: 
 *     - Primeiro pensar para um elevador
 *     - Segundo pensar no pavimento
 *     - Terceiro pensar na integraçao elevador/pavimento
 *     - Quarto pensar o funcionamento de um sistema, um conjunto de N elevadores
 */
 
MACHINE
    Elevator_System
    
SETS
    ELEVATOR_DIRECTIONS = {up, down}; // Visor
    FLOOR_BUTTONS = {btn_up, btn_down}
    
CONSTANTS
    NUM_FLOOR,
    NUM_ELEVATOR
    
PROPERTIES 
    NUM_FLOOR >= 4
    & NUM_FLOOR = 8 //arbritrario
    & NUM_ELEVATOR : NAT1

VARIABLES 
    current_floor,
    status_door,
    status_work

INVARIANT
    current_floor : NAT1
    & current_floor <= NUM_FLOOR
    
    & status_door : BOOL
    & status_work : BOOL
    //& (status_work = FALSE) => status_door = TRUE
    //& (status_work = TRUE) => status_door = FALSE
    
INITIALISATION
    current_floor := 1
    || status_door := TRUE
    || status_work := FALSE
    
END
