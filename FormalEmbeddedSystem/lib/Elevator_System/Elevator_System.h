#ifndef _Elevator_System_h
#define _Elevator_System_h

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Clause SETS */
typedef enum
{
    Elevator_System__up,
    Elevator_System__down,
    Elevator_System__empty
    
} Elevator_System__ELEVATOR_DIRECTIONS;
#define Elevator_System__ELEVATOR_DIRECTIONS__max 3
typedef enum
{
    Elevator_System__btn_alarm,
    Elevator_System__btn_phone,
    Elevator_System__btn_open,
    Elevator_System__btn_close
    
} Elevator_System__ELEVATOR_SPECIAL_BUTTONS;
#define Elevator_System__ELEVATOR_SPECIAL_BUTTONS__max 4
typedef enum
{
    Elevator_System__btn_up,
    Elevator_System__btn_down
    
} Elevator_System__FLOOR_BUTTONS;
#define Elevator_System__FLOOR_BUTTONS__max 2

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */
#define Elevator_System__NUM_FLOOR 8
#define Elevator_System__NUM_ELEVATOR 1
typedef int Elevator_System__ELEVATOR_ORDINARY_BUTTONS;
typedef int Elevator_System__ELEVATOR_FLOOR_DISPLAY;
/* Array and record constants */





/* Clause CONCRETE_VARIABLES */

extern void Elevator_System__INITIALISATION(void);

/* Clause OPERATIONS */

extern void Elevator_System__move(void);
extern void Elevator_System__elevator_operation_request(int32_t user_orders);
extern void Elevator_System__elevator_operation_alarm(void);
extern void Elevator_System__elevator_operation_report(void);
extern void Elevator_System__elevator_operation_hold_door(void);
extern void Elevator_System__elevator_operation_open_door(void);
extern void Elevator_System__elevator_operation_close_door(void);
extern void Elevator_System__elevator_operation_let_go(void);
extern void Elevator_System__elevator_operation_break_to_repair(void);
extern void Elevator_System__elevator_operation_repaired(void);
extern void Elevator_System__enter_elevator(int32_t weight);
extern void Elevator_System__exit_elevator(void);
extern void Elevator_System__get_phone_call_from_elevator(void);
extern void Elevator_System__intermediary_call_elevator(int32_t number_floor, Elevator_System__ELEVATOR_DIRECTIONS direction);
extern void Elevator_System__ground_floor_call_elevator(void);
extern void Elevator_System__last_floor_call_elevator(void);
extern void Elevator_System__cancel(int32_t num_floor);
extern void Elevator_System__cancel_floor(int32_t num_floor, Elevator_System__ELEVATOR_DIRECTIONS direction);

void print_alarm_door();
void print_ask_to_repair();
void print_behavior();
void print_btn_actions();
void print_btn_special();
void print_cancel();
void print_current();
void print_display_directon();
void print_display_floor();
void print_floor_leds();
void print_people_in_elev();
void print_ptr_qtd();
void print_sensors();
void print_state_blink();
void print_status();
void print_time();

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _Elevator_System_h */
