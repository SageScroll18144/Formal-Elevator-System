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
    ask_to_repair,
    people_in_elevator,
    id_inside,
    behavior,
    floor_leds,
    floor_leds_up,
    floor_leds_down,
    cancel_set,
    cancel_set_floor,
    state_blink,
    time_door,
    time_floor,
    alarm_door

INVARIANT
    current_floor : 1..NUM_FLOOR
    & current_direction : ELEVATOR_DIRECTIONS
    & status_door : BOOL
    & status_work : BOOL
    & status_operation : BOOL
    & time : NAT
    & time_floor : NAT
    & time_door : NAT
    & sensor_pir : BOOL
    & sensor_balance : NAT
    & ((status_work = FALSE) => status_door = TRUE & (status_work = TRUE) => status_door = FALSE)
    & btn_actions : ELEVATOR_ORDINARY_BUTTONS --> BOOL // relação com o elevador
    & btn_special : ELEVATOR_SPECIAL_BUTTONS --> BOOL
    & display_floor : ELEVATOR_FLOOR_DISPLAY --> BOOL
    & display_floor(current_floor) = TRUE
    & display_direction_elevator : ELEVATOR_DIRECTIONS
    & display_direction_elevator = current_direction
    & ask_to_repair : BOOL
    & people_in_elevator : NAT <-> NAT1
    & id_inside : NAT
    & behavior : NAT <-> ELEVATOR_DIRECTIONS
    & floor_leds : 1..NUM_FLOOR <-> ELEVATOR_DIRECTIONS
    & floor_leds_up : 1..NUM_FLOOR --> BOOL
    & floor_leds_down : 1..NUM_FLOOR --> BOOL
    & cancel_set : NAT <-> 1..NUM_FLOOR
    & cancel_set_floor : NAT <-> (1..NUM_FLOOR <-> ELEVATOR_DIRECTIONS)
    & state_blink : ELEVATOR_FLOOR_DISPLAY --> BOOL
    & alarm_door : BOOL
    
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
    || time_floor := 0
    || time_door := 1
    || sensor_pir := FALSE
    || sensor_balance := 0
    || display_direction_elevator := empty
    || ask_to_repair := FALSE
    || people_in_elevator := {}
    || id_inside := 0
    || behavior := {}
    || floor_leds := {}
    || floor_leds_up := ELEVATOR_ORDINARY_BUTTONS * {FALSE}
    || floor_leds_down := ELEVATOR_ORDINARY_BUTTONS * {FALSE}
    || cancel_set := {}
    || cancel_set_floor := {}
    || state_blink := ELEVATOR_FLOOR_DISPLAY  * {FALSE}
    || alarm_door := FALSE

OPERATIONS
        
    move = 
    PRE
        status_work = TRUE
        & status_operation = TRUE
        
        & status_door = FALSE
        & ask_to_repair = FALSE
        & behavior /= {}
    THEN
        IF min(dom(behavior)) = 0 THEN
            behavior := behavior - {0 |-> up, 0 |-> down}  
            || current_direction := empty
            || display_direction_elevator := empty
            || status_door := TRUE
            || status_work := FALSE
            || btn_special(btn_close) := FALSE
            || btn_actions(current_floor) := FALSE
            || floor_leds := floor_leds - {current_floor |-> up, current_floor |-> down} \/ {current_floor |-> empty}
            || floor_leds_up(current_floor) := FALSE
            || floor_leds_down(current_floor) := FALSE
            || time := 0
            || time_floor := 0
            || state_blink(current_floor) := FALSE
            
        ELSE
            IF behavior(min(dom(behavior))) = up & current_direction /= down THEN
                 current_floor := current_floor + 1
                || current_direction := up
                || display_direction_elevator := up
                || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {(display_floor~(TRUE) + 1) |-> TRUE} 
                
                || behavior := { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {down}) & (xx- 1) |-> yy : (behavior /\ NAT * {down}) } \/ { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {up}) & (xx+1) |-> yy : (behavior /\ NAT * {up}) }
                || time := 0
                || time_floor := 0
                || status_work := TRUE
                
            ELSE
                IF behavior(min(dom(behavior))) = down & current_direction /= up THEN
                    current_floor := current_floor - 1
                    || current_direction := down
                    || display_direction_elevator := down
                    || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {((display_floor~(TRUE)) - 1) |-> TRUE}
                    || behavior := { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {down}) & (xx+1) |-> yy : (behavior /\ NAT * {down}) } \/ { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {up}) & (xx-1) |-> yy : (behavior /\ NAT * {up}) }
                    || time := 0
                    || time_floor := 0
                    || status_work := TRUE
                    
                ELSE 
                    IF behavior(min(dom(behavior))) = up & current_direction = down THEN
                        current_floor := current_floor - 1
                        || current_direction := down
                        || display_direction_elevator := down
                        || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {(display_floor~(TRUE) - 1) |-> TRUE}
                        || behavior := { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {down}) & (xx+1) |-> yy : (behavior /\ NAT * {down}) } \/ { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {up}) & (xx-1) |-> yy : (behavior /\ NAT * {up}) }
                        || time := 0
                        || time_floor := 0
                        || status_work := TRUE
                      
                    ELSE
                        current_floor := current_floor + 1
                        || current_direction := up
                        || display_direction_elevator := up
                        || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {(display_floor~(TRUE) + 1) |-> TRUE} 
                        || behavior := { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {down}) & (xx-1) |-> yy : (behavior /\ NAT * {down}) } \/ { xx,yy | xx : NAT & yy : ran(behavior /\ NAT * {up}) & (xx+1) |-> yy : (behavior /\ NAT * {up}) }
                        || time := 0
                        || time_floor := 0
                        || status_work := TRUE
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
        & sensor_balance > 0
        & user_orders : 1..NUM_FLOOR
        & status_operation = TRUE
        & btn_special(btn_phone) = FALSE

    THEN        
        IF (user_orders - current_floor) < 0 THEN
            behavior := behavior \/ {(current_floor - user_orders) |-> down}
            || btn_actions(user_orders) := TRUE
            || time := 0
            || time_floor := 0
        ELSE
            behavior := behavior \/ {(user_orders - current_floor) |-> up}
            || btn_actions(user_orders) := TRUE
            || time := 0
            || time_floor := 0
        END
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
        || status_operation := FALSE
    END;
    
    elevator_operation_hold_door = 
    PRE
        status_work = FALSE
        & status_door = TRUE
        & status_operation = TRUE
        & alarm_door = FALSE
        
    THEN
        IF time_door = 10 & card(behavior) > 0 THEN 
            time_door := 1
            || alarm_door := TRUE
            || sensor_pir := TRUE
        ELSE IF card(behavior) > 0 THEN
             sensor_pir := TRUE
            || status_door := TRUE
            || time_door := time_door + 1
           ELSE
             sensor_pir := TRUE
            || status_door := TRUE
            || time_door := 1
       
            END 
        
        END
    END;

    elevator_operation_open_door = 
    PRE
        status_operation = TRUE
        & alarm_door = FALSE
        & current_direction = empty
        & sensor_balance > 0
    THEN
        IF time_door = 10 & card(behavior) > 0 THEN 
            time_door := 1
            || alarm_door := TRUE
            || btn_special := btn_special <+ {btn_open |-> FALSE, btn_close |-> FALSE}
            || status_work := FALSE
        ELSE IF card(behavior) > 0 THEN
            btn_special := btn_special <+ {btn_open |-> TRUE, btn_close |-> FALSE}
            || status_door := TRUE
            || time_door := time_door + 1
            || status_work := FALSE
           ELSE
            btn_special := btn_special <+ {btn_open |-> TRUE, btn_close |-> FALSE}
            || status_door := TRUE
            || time_door := 1
            || status_work := FALSE
       
            END 
        END
    END;

    elevator_operation_close_door = 
    PRE
        (btn_special(btn_close) = FALSE
        & status_work = FALSE
        & status_operation = TRUE
        & status_door = TRUE
        & sensor_pir = FALSE
       ) or alarm_door = TRUE
        
    THEN
        btn_special := btn_special <+ {btn_open |-> FALSE, btn_close |-> TRUE}
        || status_door := FALSE
        || alarm_door := FALSE
        || time_door := 1
        || status_work := TRUE
        
    END;

    elevator_operation_let_go = 
    PRE
        sensor_pir = TRUE
    THEN 
        sensor_pir := FALSE
        || time_door := 1
    END;
    
    elevator_operation_break_to_repair =
    PRE
        status_operation = FALSE
        & ask_to_repair = TRUE
    THEN
        IF card(behavior) = 0 or current_direction = empty THEN
            status_work := FALSE
            || display_direction_elevator := empty
            || ask_to_repair := FALSE
            || behavior := {}
            || people_in_elevator := {}
            || id_inside := 0
            || sensor_balance := 0
            || sensor_pir := FALSE
        ELSE
           IF (current_direction = up & current_floor /= NUM_FLOOR) or (current_floor = 1) THEN
               // vai para o pavimento acima
                status_work := FALSE
                || current_floor := current_floor + 1 
                || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {display_floor~(TRUE) + 1 |-> TRUE}
                || current_direction := empty
                || display_direction_elevator := empty
                || ask_to_repair := FALSE
                || behavior := {}
                || people_in_elevator := {}
                || id_inside := 0
                || sensor_balance := 0
                || sensor_pir := FALSE
           ELSE IF (current_direction = down & current_floor /= 1) or (current_floor = NUM_FLOOR) THEN
                status_work := FALSE
                || current_floor := current_floor - 1 
                || display_floor := ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {display_floor~(TRUE) - 1 |-> TRUE}
                || current_direction := empty
                || display_direction_elevator := empty
                || ask_to_repair := FALSE
                || behavior := {}
                || people_in_elevator := {}
                || id_inside := 0
                || sensor_balance := 0
                || sensor_pir := FALSE
            END
           END
        END
    END;
    
    elevator_operation_repaired =
    PRE
        status_operation = FALSE
        & status_work = FALSE
    THEN
        current_direction := empty
        || status_door := TRUE
        || status_work := FALSE
        || status_operation := TRUE
        || btn_actions := ELEVATOR_ORDINARY_BUTTONS * {FALSE} // relação com o elevador
        || btn_special := ELEVATOR_SPECIAL_BUTTONS * {FALSE} // relação com o elevador
        || display_floor :=  ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {current_floor |-> TRUE} // relação com o elevador
        || time := 0
        || time_floor := 0
        || time_door := 1
        || sensor_pir := FALSE
        || sensor_balance := 0
        || display_direction_elevator := empty
        || ask_to_repair := FALSE
        || people_in_elevator := {}
        || id_inside := 0
        || behavior := {}
        || floor_leds := {}
        || floor_leds_up := ELEVATOR_ORDINARY_BUTTONS * {FALSE}
        || floor_leds_down := ELEVATOR_ORDINARY_BUTTONS * {FALSE}
        || cancel_set := {}
        || state_blink := ELEVATOR_FLOOR_DISPLAY  * {FALSE}
        || alarm_door := FALSE
    END;

    enter_elevator(weight) = 
    PRE
        weight : NAT1
        & status_work = FALSE
        & status_door = TRUE
        & status_operation = TRUE
        & alarm_door = FALSE
    THEN
        sensor_balance := sensor_balance + weight
        || id_inside := id_inside + 1
        || people_in_elevator := people_in_elevator <+ {id_inside |-> weight}
    END;

    exit_elevator =
    PRE 
        people_in_elevator /= {} 
        & status_door = TRUE
        & status_operation = TRUE
        & status_work = FALSE
        & alarm_door = FALSE
    THEN
        IF card(people_in_elevator) > 1 THEN
            ANY p1 WHERE p1 : dom(people_in_elevator) THEN
                sensor_balance := sensor_balance - people_in_elevator(p1)
                || people_in_elevator := people_in_elevator - {p1 |-> people_in_elevator(p1)}
            END
        ELSE
            sensor_balance := 0
            || people_in_elevator := {}
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
        & ({number_floor |-> direction} /\ floor_leds) = {}
        & (direction = up => floor_leds_up(number_floor) = FALSE)
        & (direction = down => floor_leds_down(number_floor) = FALSE)
        & number_floor /= current_floor
    THEN
        IF sensor_pir = FALSE THEN
            IF (number_floor - current_floor) < 0 THEN
                IF direction = up THEN
                    behavior := behavior \/ {(current_floor - number_floor) |-> down}
                    || status_door := FALSE
                    || status_work := TRUE
                    || floor_leds := floor_leds \/ {(number_floor) |-> direction}
                    || floor_leds_up(number_floor) := TRUE
                    || time := 0
                    || time_floor := 0
                ELSE
                    behavior := behavior \/ {(current_floor - number_floor) |-> down}
                    || status_door := FALSE
                    || status_work := TRUE
                    || floor_leds := floor_leds \/ {(number_floor) |-> direction}
                    || floor_leds_down(number_floor) := TRUE
                    || time := 0
                    || time_floor := 0
                END
            ELSE 
                IF direction = up THEN
                    behavior := behavior \/ {(number_floor - current_floor) |-> up}
                    || status_door := FALSE
                    || status_work := TRUE
                    || floor_leds := floor_leds \/ {(number_floor) |-> direction}
                    || floor_leds_up(number_floor) := TRUE
                    || time := 0
                    || time_floor := 0
                ELSE
                    behavior := behavior \/ {(number_floor - current_floor) |-> up}
                    || status_door := FALSE
                    || status_work := TRUE
                    || floor_leds := floor_leds \/ {(number_floor) |-> direction}
                    || floor_leds_down(number_floor) := TRUE
                    || time := 0
                    || time_floor := 0
                END
            END
        ELSE
            IF (number_floor - current_floor) < 0 THEN
                IF direction = up THEN
                    behavior := behavior \/ {(current_floor - number_floor) |-> down}
                    || status_door := TRUE
                    || status_work := FALSE
                    || floor_leds := floor_leds \/ {number_floor |-> direction}
                    || floor_leds_up(number_floor) := TRUE
                    || time := 0
                    || time_floor := 0 
                ELSE
                    behavior := behavior \/ {(current_floor - number_floor) |-> down}
                    || status_door := TRUE
                    || status_work := FALSE
                    || floor_leds := floor_leds \/ {number_floor |-> direction}
                    || floor_leds_down(number_floor) := TRUE
                    || time := 0
                    || time_floor := 0 
                END
            ELSE 
                IF direction = up THEN
                    behavior := behavior \/ {(number_floor - current_floor) |-> up}
                    || status_door := TRUE
                    || status_work := FALSE
                    || floor_leds := floor_leds \/ {(number_floor) |-> direction}
                    || floor_leds_up(number_floor) := TRUE
                    || time := 0
                    || time_floor := 0
                ELSE
                    behavior := behavior \/ {(number_floor - current_floor) |-> up}
                    || status_door := TRUE
                    || status_work := FALSE
                    || floor_leds := floor_leds \/ {(number_floor) |-> direction}
                    || floor_leds_down(number_floor) := TRUE
                    || time := 0
                    || time_floor := 0
                END
            END
        END

    END;

    ground_floor_call_elevator = 
    PRE
        status_operation = TRUE
        & btn_special(btn_phone) = FALSE
    THEN
        IF sensor_pir = TRUE THEN
            behavior := behavior <+ {(current_floor - 1) |-> down}
            || time := 0
            || time_floor := 0
            || floor_leds := floor_leds <+ {1 |-> up}
            || floor_leds_up(1) := TRUE
            || status_door := TRUE
            || status_work := FALSE
        ELSE
            behavior := behavior <+ {(current_floor - 1) |-> down}
            || time := 0
            || time_floor := 0
            || floor_leds := floor_leds <+ {1 |-> up}
            || floor_leds_up(1) := TRUE
            || status_door := FALSE
            || status_work := TRUE
            
        END
    END;

    last_floor_call_elevator = 
    PRE
        status_operation = TRUE
        & btn_special(btn_phone) = FALSE
    THEN
        IF sensor_pir = TRUE THEN
            behavior := behavior <+ {(NUM_FLOOR - current_floor) |-> up}
            || time := 0
            || time_floor := 0
            || floor_leds := floor_leds <+ {NUM_FLOOR |-> down}
            || floor_leds_down(NUM_FLOOR) := TRUE
            || status_door := TRUE
            || status_work := FALSE
        ELSE
            behavior := behavior <+ {(NUM_FLOOR - current_floor) |-> up}
            || time := 0
            || time_floor := 0
            || floor_leds := floor_leds <+ {NUM_FLOOR |-> down}
            || floor_leds_down(NUM_FLOOR) := TRUE
            || status_door := FALSE
            || status_work := TRUE
        END
    END;
    
    cancel(num_floor) =
    PRE 
        btn_actions(num_floor) = TRUE
        & status_operation = TRUE
    THEN
        IF time > 1 & cancel_set(time-2) = num_floor & cancel_set(time-2) = cancel_set(time-1)  THEN
            IF card(behavior) = 1 THEN
                state_blink(num_floor) := TRUE
            ELSE IF (num_floor - current_floor) < 0 THEN
                behavior := behavior - {(current_floor - num_floor) |-> down}
                || btn_actions(num_floor) := FALSE
                || cancel_set := {}
                || time := 0
                || current_direction := empty
                || display_direction_elevator := empty
                || state_blink(num_floor) := FALSE
            ELSE 
                behavior := behavior - {(num_floor - current_floor) |-> up}
                || btn_actions(num_floor) := FALSE
                || cancel_set := {}
                || time := 0
                || current_direction := empty
                || display_direction_elevator := empty
                || state_blink(num_floor) := FALSE
            END
            END
        ELSE
            cancel_set := cancel_set <+ {time |-> num_floor}
            || time := time + 1
            || state_blink(num_floor) := FALSE
        END
    END;
    
    cancel_floor(num_floor, direction) =
    PRE 
        direction : ELEVATOR_DIRECTIONS 
        & num_floor : dom(floor_leds)
        & num_floor /= current_floor 
        & {num_floor |-> direction} /\ floor_leds /= {}
        & (floor_leds_down(num_floor) = TRUE or floor_leds_up(num_floor) = TRUE)
        & status_operation = TRUE
        & direction /= empty
    THEN
        IF time_floor > 1 & cancel_set_floor(time_floor-2) = {num_floor |-> direction} & cancel_set_floor(time_floor-2) = cancel_set_floor(time_floor-1) THEN
            IF card(behavior) = 1 THEN
                IF current_direction = up THEN
                    behavior := {}
                    || floor_leds := floor_leds - {num_floor |-> direction}
                    || floor_leds_up(num_floor) := FALSE
                    || floor_leds_down(num_floor) := FALSE
                    || cancel_set_floor := {}
                    || time_floor := 0
                    || current_direction := empty
                    || display_direction_elevator := empty
                    || current_floor := current_floor + 1 
                    || display_floor :=  ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {display_floor~(TRUE) +1 |-> TRUE}
                    
                 ELSE IF current_direction = down THEN
                    behavior := {}
                    || floor_leds := floor_leds - {num_floor |-> direction}
                    || floor_leds_up(num_floor) := FALSE
                    || floor_leds_down(num_floor) := FALSE
                    || cancel_set_floor := {}
                    || time_floor := 0
                    || current_direction := empty
                    || display_direction_elevator := empty
                    || current_floor := current_floor - 1
                    || display_floor :=  ELEVATOR_FLOOR_DISPLAY * {FALSE} <+ {display_floor~(TRUE) -1 |-> TRUE}
                     
                 ELSE
                     behavior := {}
                    || floor_leds := floor_leds - {num_floor |-> direction}
                    || floor_leds_up(num_floor) := FALSE
                    || floor_leds_down(num_floor) := FALSE
                    || cancel_set_floor := {}
                    || time_floor := 0
                    || current_direction := empty
                    || display_direction_elevator := empty
                     
               
                 END
            END
            
            ELSE IF direction = down THEN
                behavior := behavior - {(current_floor - num_floor) |-> down}
                || floor_leds := floor_leds - {num_floor |-> direction}
                || floor_leds_up(num_floor) := FALSE
                || floor_leds_down(num_floor) := FALSE
                || cancel_set_floor := {}
                || time_floor := 0
                || current_direction := empty
                || display_direction_elevator := empty
       
            ELSE 
                behavior := behavior - {(num_floor - current_floor) |-> up}
                || floor_leds := floor_leds - {num_floor |-> direction}
                || floor_leds_up(num_floor) := FALSE
                || floor_leds_down(num_floor) := FALSE
                || cancel_set_floor := {}
                || time_floor := 0
                || current_direction := empty
                || display_direction_elevator := empty
       
            END
            END
            
        ELSE
            cancel_set_floor := cancel_set_floor <+ {time_floor |-> {num_floor |-> direction}}
            || time_floor := time_floor + 1
     
        END
     END
END
