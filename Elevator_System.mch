/* Elevator_System
 * Author: Felipe Santos, Victor Mendonça
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
    ELEVATOR_DIRECTIONS = {up, down};
    FLOOR_BUTTONS = {btn_up, btn_down}
    
CONSTANTS
    NUM_FLOOR,
    NUM_ELEVATOR
    
PROPERTIES 
    NUM_FLOOR : NAT
    & NUM_FLOOR >= 4
    & NUM_FLOOR = 8
    
    & NUM_ELEVATOR : NAT

VARIABLES 
    current_floor,
    status_door,
    status_work

INVARIANT
    current_floor : NAT
    & current_floor >= 4
    & current_floor <= NUM_FLOOR
    
    & status_door : BOOL
    & status_work : BOOL
    
INITIALISATION
    current_floor := 4
    || status_door := TRUE
    || status_work := FALSE
    
END
