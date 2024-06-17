MACHINE
    Elevator_System
    
SETS
    ELEVATOR_DIRECTIONS = {up, down, empty}; // Visor
    ELEVATOR_SPECIAL_BUTTONS = {btn_alarm, btn_phone, btn_open, btn_close};
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
    status_operation,
    btn_actions, // Talvez relacione com os leds(no caso podemos supor que vao ser os leds)
    btn_special,
    display_floor,// andares
    display_direction_elevator, // direçao do elevador
    time,
    sensor_pir,
    sensor_balance,
    check_points

INVARIANT
    current_floor : 1..NUM_FLOOR
    & status_door : BOOL
    & status_work : BOOL
    & status_operation : BOOL
    & time : NAT
    & sensor_pir : BOOL
    & sensor_balance : NAT
    & (status_work = FALSE) => status_door = TRUE
    & (status_work = TRUE) => status_door = FALSE
    & btn_actions : ELEVATOR_ORDINARY_BUTTONS --> BOOL // relação com o elevador
    & btn_special : ELEVATOR_SPECIAL_BUTTONS --> BOOL
    & display_floor : ELEVATOR_FLOOR_DISPLAY --> BOOL
    & display_floor(current_floor) = TRUE
    & display_direction_elevator : ELEVATOR_DIRECTIONS
    & check_points : seq(1..NUM_FLOOR) // referente ao elevador
    & btn_special(btn_phone) = TRUE => btn_special(btn_alarm) = TRUE
    
INITIALISATION
    current_floor := 1
    || status_door := TRUE
    || status_work := FALSE
    || status_operation := TRUE
    || btn_actions := ELEVATOR_ORDINARY_BUTTONS * {FALSE} // relação com o elevador
    || btn_special := ELEVATOR_SPECIAL_BUTTONS * {FALSE} // relação com o elevador
    || display_floor :=  ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {1 |-> TRUE} // relação com o elevador
    || time := 0
    || sensor_pir := FALSE
    || sensor_balance := 0
    || check_points := []
    || display_direction_elevator := empty

OPERATIONS
    // Operações referentes ao elevador

    clock = 
    BEGIN
        time := time + 1
    END;

    elevator_operation_request(user_orders) = 
    PRE
        display_floor(current_floor) = TRUE
        & !(f1) . (f1 /= current_floor => display_floor(f1) = FALSE)
        & sensor_balance <= 450
        & user_orders : 1..NUM_FLOOR
        & not(user_orders : ran(check_points))
        & status_operation = TRUE
    THEN
        check_points := check_points ^ [user_orders]
    END;

    elevator_operation_alarm = 
    PRE
        btn_special(btn_alarm) = FALSE
        & status_operation = TRUE
    THEN
        btn_special(btn_alarm) := TRUE 
    END;
    
    elevator_operation_report =
    PRE
        btn_special(btn_phone) = FALSE
    THEN
        btn_special := btn_special <+ {btn_phone |-> TRUE, btn_alarm |-> TRUE} 
    END;

    elevator_operation_open_door = 
    PRE
        btn_special(btn_open) = FALSE
        & status_work = FALSE
        & status_operation = TRUE
    THEN
        btn_special := btn_special <+ {btn_open |-> TRUE, btn_close |-> FALSE}
        || status_door := TRUE
    END;

    elevator_operation_close_door = 
    PRE
        btn_special(btn_close) = FALSE
        & status_work = FALSE
        & status_operation = TRUE
    THEN
        btn_special := btn_special <+ {btn_open |-> FALSE, btn_close |-> TRUE}
        || status_door := FALSE
    END;
    
    elevator_operation_break_to_repair =
    PRE
        status_operation = TRUE
    THEN
        IF card(check_points) = 0 THEN
            status_work := FALSE
            || status_operation := FALSE
            || display_direction_elevator := empty
        ELSE
           // vai para o pavimento acima
           status_work := FALSE
           || status_operation := FALSE
           ||time := time + 1
           || display_direction_elevator := empty
        END
    END;
    
    elevator_operation_repaired =
    PRE
        status_operation = FALSE
        & status_work = FALSE
    THEN
        status_operation := TRUE
    END;
    
    // Modelar a portaria
    get_phone_call_from_elevator =
    PRE
        btn_special(btn_phone) = TRUE
    THEN
        btn_special := btn_special <+ {btn_phone |-> FALSE, btn_alarm |-> FALSE}
    END
        
    
    
    // Operações referentes ao pavimento

    // intermediary_call_elevator(number_floor, direction) = 
    // PRE
    //     number_floor > 1 & number_floor < NUM_FLOOR
    //     & direction : ELEVATOR_DIRECTIONS & direction /= empty
    // THEN
    //     IF direction = up THEN
    //         // faça algo
    //     ELSE
    //         // faça algo
    //     END
    // END;

    // ground_floor_call_elevator = 
    // BEGIN
    //     // faça algo com o up
    // END;

    // last_floor_call_elevator = 
    // BEGIN
    //     // faça algo com o up
    // END


    // Operações que denotam o sistema do elevador: elevador + pavimento + logica de movimentação

    //Sistema com mais de 1 elevador?

END
