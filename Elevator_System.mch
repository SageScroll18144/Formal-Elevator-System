MACHINE
    Elevator_System
    
SETS
    ELEVATOR_DIRECTIONS = {up, down, empty}; // Visor
    ELEVATOR_ESPECIAL_BUTTONS = {btn_alarm, btn_phone, btn_open, btn_close};
    FLOOR_BUTTONS = {btn_up, btn_down}
    
CONSTANTS
    NUM_FLOOR,
    NUM_ELEVATOR,
    ELEVATOR_ORDINARY_BUTTONS, 
    ELEVATOR_FLOOR_DISPLAY
    
PROPERTIES 
    NUM_FLOOR >= 4
    & NUM_FLOOR = 8 // Arbitrário
    & NUM_ELEVATOR : NAT1
    & ELEVATOR_ORDINARY_BUTTONS = 1..NUM_FLOOR
    & ELEVATOR_FLOOR_DISPLAY = 1..NUM_FLOOR

VARIABLES 
    current_floor,
    status_door,
    status_work,
    btn_actions, // Talvez relacione com os leds(no caso podemos supor que vao ser os leds)
    display_floor
INVARIANT
    current_floor : 1..NUM_FLOOR
    & status_door : BOOL
    & status_work : BOOL
    & (status_work = FALSE) => status_door = TRUE
    & (status_work = TRUE) => status_door = FALSE
    & btn_actions : ELEVATOR_ORDINARY_BUTTONS --> BOOL
    & display_floor : ELEVATOR_FLOOR_DISPLAY --> BOOL
    & display_floor(current_floor) = TRUE
    
INITIALISATION
    current_floor := 1
    || status_door := TRUE
    || status_work := FALSE
    || btn_actions := ELEVATOR_ORDINARY_BUTTONS * {FALSE}
    || display_floor :=  ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {1 |-> TRUE}
END
