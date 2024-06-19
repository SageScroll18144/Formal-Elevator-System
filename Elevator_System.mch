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
    current_direction,
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
    ask_to_repair,
    people_in_elevator,
    id_inside,
    behavior,
    floor_leds

INVARIANT
    current_floor : 1..NUM_FLOOR
    & current_direction : ELEVATOR_DIRECTIONS
    & status_door : BOOL
    & status_work : BOOL
    & status_operation : BOOL
    & time : NAT
    & sensor_pir : BOOL
    & sensor_balance : NAT
    & ((status_work = FALSE) => status_door = TRUE & (status_work = TRUE) => status_door = FALSE)
    & btn_actions : ELEVATOR_ORDINARY_BUTTONS --> BOOL // relação com o elevador
    & btn_special : ELEVATOR_SPECIAL_BUTTONS --> BOOL
    & display_floor : ELEVATOR_FLOOR_DISPLAY --> BOOL
    & display_floor(current_floor) = TRUE
    & display_direction_elevator : ELEVATOR_DIRECTIONS
    & check_points : seq(1..NUM_FLOOR) // referente ao elevador
    & request_points : 1..NUM_FLOOR <-> ELEVATOR_DIRECTIONS // referente ao 
    & ask_to_repair : BOOL
    & people_in_elevator : NAT <-> NAT1
    & id_inside : NAT
    & behavior : NAT <-> ELEVATOR_DIRECTIONS
    & floor_leds : 1..NUM_FLOOR <-> ELEVATOR_DIRECTIONS

INITIALISATION
    current_floor := 3
    || current_direction := empty
    || status_door := TRUE
    || status_work := FALSE
    || status_operation := TRUE
    || btn_actions := ELEVATOR_ORDINARY_BUTTONS * {FALSE} // relação com o elevador
    || btn_special := ELEVATOR_SPECIAL_BUTTONS * {FALSE} // relação com o elevador
    || display_floor :=  ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {3 |-> TRUE} // relação com o elevador
    || time := 0
    || sensor_pir := FALSE
    || sensor_balance := 0
    || check_points := []
    || display_direction_elevator := empty
    || ask_to_repair := FALSE
    || request_points := {}
    || people_in_elevator := {}
    || id_inside := 0
    || behavior := {}
    || floor_leds := {}

OPERATIONS
        
    move = 
    PRE
        status_work = TRUE
        & status_operation = TRUE
        & status_door = FALSE
        & sensor_pir = TRUE
        & ask_to_repair = FALSE
        & behavior /= {}
    THEN
        IF min(dom(behavior)) = 0 THEN
            behavior := behavior - {0 |-> behavior(0)} 
            || current_direction := empty
            || status_door := TRUE
            || status_work := FALSE
            || btn_special(btn_close) := FALSE
            || time := time + 1
            || btn_actions(current_floor) := FALSE
            || floor_leds := floor_leds - {current_floor |-> up, current_floor |-> down} \/ {current_floor |-> empty}
            
        ELSE
            IF behavior(min(dom(behavior))) = up & current_direction /= down THEN
                 current_floor := current_floor + 1
                || current_direction := up
                || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {(display_floor~(TRUE) + 1) |-> TRUE} 
                //|| behavior := {xx, yy | xx : dom(behavior) & yy ran(behavior) & (xx-1) |-> yy : behavior}
                || behavior := { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {down}) & (xx- 1) |-> yy : (behavior /\ NAT * {down}) } \/ { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {up}) & (xx+1) |-> yy : (behavior /\ NAT * {up}) }
                || time := time + 1
            ELSE
                IF behavior(min(dom(behavior))) = down & current_direction /= up THEN
                    current_floor := current_floor - 1
                    || current_direction := down
                    || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {((display_floor~(TRUE)) - 1) |-> TRUE}
                    || behavior := { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {down}) & (xx+1) |-> yy : (behavior /\ NAT * {down}) } \/ { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {up}) & (xx-1) |-> yy : (behavior /\ NAT * {up}) }
                    || time := time + 1
                ELSE 
                    IF behavior(min(dom(behavior))) = up & current_direction = down THEN
                        current_floor := current_floor - 1
                        || current_direction := down
                        || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {(display_floor~(TRUE) - 1) |-> TRUE}
                        || behavior := { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {down}) & (xx+1) |-> yy : (behavior /\ NAT * {down}) } \/ { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {up}) & (xx-1) |-> yy : (behavior /\ NAT * {up}) }
                      
                        //|| behavior := (behavior <+ {(min(dom(behavior /\ NAT * {down})) - 1) |-> behavior(min(dom(behavior /\ NAT * {down}))), min(dom(behavior /\ NAT * {down})) |-> empty}, )
                    ELSE
                        current_floor := current_floor + 1
                        || current_direction := up
                        || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {(display_floor~(TRUE) + 1) |-> TRUE} 
                        || behavior := { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {down}) & (xx-1) |-> yy : (behavior /\ NAT * {down}) } \/ { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {up}) & (xx+1) |-> yy : (behavior /\ NAT * {up}) }
                    END
                END
            END
        END
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
        & sensor_pir = TRUE
        & btn_special(btn_phone) = FALSE

    THEN        
        IF (user_orders - current_floor) < 0 THEN
            behavior := behavior <+ {(current_floor - user_orders) |-> down}
            || check_points := check_points ^ [user_orders]
            || status_door := FALSE
            || status_work := TRUE
            || btn_actions(user_orders) := TRUE
        ELSE
            behavior := behavior <+ {(user_orders - current_floor) |-> up}
            || check_points := check_points ^ [user_orders]
            || status_door := FALSE
            || status_work := TRUE
            || btn_actions(user_orders) := TRUE
        END
    END;

    elevator_operation_alarm = 
    PRE
        btn_special(btn_alarm) = FALSE
        & status_operation = TRUE
        & status_work = TRUE
        & sensor_pir = TRUE
        
    THEN
        btn_special(btn_alarm) := TRUE 
    END;
    
    elevator_operation_report =
    PRE
        btn_special(btn_phone) = FALSE
        & status_work = TRUE
        & sensor_pir = TRUE
        
    THEN
        btn_special := btn_special <+ {btn_phone |-> TRUE, btn_alarm |-> TRUE} 
    END;

    elevator_operation_open_door = 
    PRE
        btn_special(btn_open) = FALSE
        & status_work = FALSE
        & status_operation = TRUE
        & status_door = FALSE
        & sensor_pir = TRUE
        
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
        & sensor_pir = TRUE
        
    THEN
        btn_special := btn_special <+ {btn_open |-> FALSE, btn_close |-> TRUE}
        || status_door := FALSE
        || status_work := TRUE
    END;
    
    elevator_operation_break_to_repair =
    PRE
        status_operation = FALSE
        & ask_to_repair = TRUE
    THEN
        IF card(check_points) = 0 THEN
            status_work := FALSE
            || display_direction_elevator := empty
            || ask_to_repair := FALSE
            || request_points := {}
            || people_in_elevator := {}
            || id_inside := 0
            || sensor_balance := 0
            || sensor_pir := FALSE
        ELSE
           // vai para o pavimento acima
            status_work := FALSE
            || time := time + 1 // para no andar de cima
            || display_direction_elevator := empty
            || ask_to_repair := FALSE
            || request_points := {}
            || people_in_elevator := {}
            || id_inside := 0
            || sensor_balance := 0
            || sensor_pir := FALSE
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
        || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+  {current_floor |-> TRUE} // relação com o elevador
        || time := 0
        || sensor_pir := FALSE
        || sensor_balance := 0
        || check_points := []
        || display_direction_elevator := empty
        || ask_to_repair := FALSE
        || request_points := {}
        || people_in_elevator := {}
        || id_inside := 0
        
    END;

    enter_elevator(weight) = 
    PRE
        weight : NAT1
        & status_work = FALSE
        & status_door = TRUE
        & status_operation = TRUE
    THEN
        sensor_balance := sensor_balance + weight
        || sensor_pir := TRUE
        || id_inside := id_inside + 1
        || people_in_elevator := people_in_elevator <+ {id_inside |-> weight}
    END;

    exit_elevator =
    PRE 
        people_in_elevator /= {} 
        & status_door = TRUE
        & status_operation = TRUE
        & status_work = FALSE
    THEN
        IF card(people_in_elevator) > 1 THEN
            ANY p1 WHERE p1 : dom(people_in_elevator) THEN
                sensor_balance := sensor_balance - people_in_elevator(p1)
                || people_in_elevator := people_in_elevator - {p1 |-> people_in_elevator(p1)}
            END
        ELSE
            sensor_balance := 0
            || people_in_elevator := {}
            || sensor_pir := FALSE
        END
    END;


    // Operações referentes a portaria

    get_phone_call_from_elevator =
    PRE
        btn_special(btn_phone) = TRUE
    THEN
        btn_special := btn_special <+ {btn_phone |-> FALSE, btn_alarm |-> FALSE}
        || ask_to_repair := TRUE
        || status_operation := FALSE
    END;      
    
    // Operações referentes ao pavimento
        // Obs: voce pode apertar mais de uma vez, entretanto na função só é registrado uma unica vez a requisição

    intermediary_call_elevator(number_floor, direction) = 
    PRE
        number_floor > 1 & number_floor < NUM_FLOOR
        & direction : ELEVATOR_DIRECTIONS & direction /= empty
        & status_operation = TRUE
        & btn_special(btn_phone) = FALSE
    THEN
        IF (number_floor - current_floor) < 0 THEN
            behavior := behavior <+ {(current_floor - number_floor) |-> down}
            || request_points := request_points <+ {(current_floor - number_floor) |-> down}
            || status_door := FALSE
            || status_work := TRUE
            || floor_leds(number_floor) := direction
        ELSE
            behavior := behavior <+ {(number_floor - current_floor) |-> up}
            || request_points := request_points <+ {(number_floor - current_floor) |-> up}
            || status_door := FALSE
            || status_work := TRUE
            || floor_leds(number_floor) := direction
        END
    END;

    ground_floor_call_elevator = 
    PRE
        status_operation = TRUE
        & btn_special(btn_phone) = FALSE
    THEN
        request_points := request_points <+ {1 |-> up}
        || behavior := behavior <+ {(current_floor - 1) |-> up}
        || status_door := FALSE
        || status_work := TRUE
    END;

    last_floor_call_elevator = 
    PRE
        status_operation = TRUE
        & btn_special(btn_phone) = FALSE
    THEN
        request_points := request_points <+ {NUM_FLOOR |-> down}
        || behavior := behavior <+ {(NUM_FLOOR - current_floor) |-> down}
        || status_door := FALSE
        || status_work := TRUE
    END
    
    // Operações que denotam o sistema do elevador: elevador + pavimento + logica de movimentação

    //Sistema com mais de 1 elevador?

END
