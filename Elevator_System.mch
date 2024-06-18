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
    check_points,
    request_points,
    ask_to_repair

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
    & request_points : 1..NUM_FLOOR --> ELEVATOR_DIRECTIONS // referente ao 
    & ask_to_repair : BOOL
    
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
    || ask_to_repair := FALSE
    || request_points := {}

OPERATIONS
    
    // Movimentação?
    clock = 
    BEGIN
        time := time + 1
    END;
    // Operações referentes ao elevador
    
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
        || status_door := FALSE
        || status_work := TRUE
    END;

    elevator_operation_alarm = 
    PRE
        btn_special(btn_alarm) = FALSE
        & status_operation = TRUE
        & status_work = TRUE
    THEN
        btn_special(btn_alarm) := TRUE 
    END;
    
    elevator_operation_report =
    PRE
        btn_special(btn_phone) = FALSE
        & status_work = TRUE
    THEN
        btn_special := btn_special <+ {btn_phone |-> TRUE, btn_alarm |-> TRUE} 
    END;

    elevator_operation_open_door = 
    PRE
        btn_special(btn_open) = FALSE
        & status_work = FALSE
        & status_operation = TRUE
        & status_door = FALSE
    THEN
        btn_special := btn_special <+ {btn_open |-> TRUE, btn_close |-> FALSE}
        || status_door := TRUE
    END;

    elevator_operation_close_door = 
    PRE
        btn_special(btn_close) = FALSE
        & status_work = FALSE
        & status_operation = TRUE
        & status_door = TRUE
    THEN
        btn_special := btn_special <+ {btn_open |-> FALSE, btn_close |-> TRUE}
        || status_door := FALSE
    END;
    
    elevator_operation_break_to_repair =
    PRE
        status_operation = TRUE
        & ask_to_repair = TRUE
    THEN
        IF card(check_points) = 0 THEN
            status_work := FALSE
            || status_operation := FALSE
            || display_direction_elevator := empty
            || ask_to_repair := FALSE
        ELSE
           // vai para o pavimento acima
           status_work := FALSE
           || status_operation := FALSE
           ||time := time + 1
           || display_direction_elevator := empty
           || ask_to_repair := FALSE
        END
    END;
    
    elevator_operation_repaired =
    PRE
        status_operation = FALSE
        & status_work = FALSE
    THEN
        status_door := TRUE
        || status_work := FALSE
        || status_operation := TRUE
        || btn_actions := ELEVATOR_ORDINARY_BUTTONS * {FALSE} // relação com o elevador
        || btn_special := ELEVATOR_SPECIAL_BUTTONS * {FALSE} // relação com o elevador
        || display_floor :=  ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {current_floor |-> TRUE} // relação com o elevador
        || time := 0
        || sensor_pir := FALSE
        || sensor_balance := 0
        || check_points := []
        || display_direction_elevator := empty
        || ask_to_repair := FALSE

    END;
    
    // Modelar a portaria
    get_phone_call_from_elevator =
    PRE
        btn_special(btn_phone) = TRUE
    THEN
        btn_special := btn_special <+ {btn_phone |-> FALSE, btn_alarm |-> FALSE}
        || ask_to_repair := TRUE
    END;      
    
    // Operações referentes ao pavimento
        // Obs: voce pode apertar mais de uma vez, entretanto na função só é registrado 

    intermediary_call_elevator(number_floor, direction) = 
    PRE
        number_floor > 1 & number_floor < NUM_FLOOR
        & direction : ELEVATOR_DIRECTIONS & direction /= empty
        & status_operation = TRUE
    THEN
        request_points := request_points <+ {number_floor |-> direction}
    END;

    ground_floor_call_elevator = 
    PRE
        status_operation = TRUE
    THEN
        request_points := request_points <+ {1 |-> up}
    END;

    last_floor_call_elevator = 
    PRE
        status_operation = TRUE
    THEN
        request_points := request_points <+ {NUM_FLOOR |-> down}
    END


    // Operações que denotam o sistema do elevador: elevador + pavimento + logica de movimentação

    //Sistema com mais de 1 elevador?

END
