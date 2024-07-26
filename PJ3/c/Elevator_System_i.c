/* WARNING if type checker is not performed, translation could contain errors ! */

#include "Elevator_System.h"
#include <stdio.h>
/* Clause CONCRETE_CONSTANTS */
/* Basic constants */

#define Elevator_System__QTD 10
#define Elevator_System__TIME_CANCEL 2
#define Elevator_System__NUM_FLOOR 8
#define Elevator_System__NUM_ELEVATOR 1
/* Array and record constants */
/* Clause CONCRETE_VARIABLES */

static int32_t Elevator_System__current_floor;
static Elevator_System__ELEVATOR_DIRECTIONS Elevator_System__current_direction;
static bool Elevator_System__status_door;
static bool Elevator_System__status_work;
static bool Elevator_System__status_operation;
static bool Elevator_System__btn_actions_[8];
static bool Elevator_System__btn_special[4];
static bool Elevator_System__display_floor_[8];
static Elevator_System__ELEVATOR_DIRECTIONS Elevator_System__display_direction_elevator;
static int32_t Elevator_System__time;
static bool Elevator_System__sensor_pir;
static int32_t Elevator_System__sensor_balance;
static bool Elevator_System__ask_to_repair;
static int32_t Elevator_System__people_in_elevator_2ref_[10];
static bool Elevator_System__behavior_up[8];
static bool Elevator_System__behavior_down[8];
static bool Elevator_System__floor_leds_up_[8];
static bool Elevator_System__floor_leds_down_[8];
static int32_t Elevator_System__cancel_set_2ref_[2];
static int32_t Elevator_System__cancel_set_floor_up_2ref_[2];
static int32_t Elevator_System__cancel_set_floor_down_2ref_[2];
static bool Elevator_System__state_blink_[8];
static int32_t Elevator_System__ptr_qtd;
static int32_t Elevator_System__time_door;
static int32_t Elevator_System__time_floor_up;
static int32_t Elevator_System__time_floor_down;
static bool Elevator_System__alarm_door;
/* Clause INITIALISATION */
void Elevator_System__INITIALISATION(void)
{
    
    unsigned int i = 0;
    Elevator_System__current_floor = 3;
    Elevator_System__current_direction = Elevator_System__empty;
    Elevator_System__status_door = true;
    Elevator_System__status_work = false;
    Elevator_System__status_operation = true;
    for(i = 0; i <= 7;i++)
    {
        Elevator_System__btn_actions_[i] = false;
    }
    for(i = 0; i <= Elevator_System__ELEVATOR_SPECIAL_BUTTONS__max-1;i++)
    {
        Elevator_System__btn_special[i] = false;
    }
    for(i = 0; i <= 7;i++)
    {
        Elevator_System__display_floor_[i] = false;
    }
    Elevator_System__display_floor_[3] = true;
    Elevator_System__time = 0;
    Elevator_System__time_floor_up = 0;
    Elevator_System__time_floor_down = 0;
    Elevator_System__time_door = 1;
    Elevator_System__sensor_pir = false;
    Elevator_System__sensor_balance = 0;
    Elevator_System__display_direction_elevator = Elevator_System__empty;
    Elevator_System__ask_to_repair = false;
    for(i = 0; i <= 9;i++)
    {
        Elevator_System__people_in_elevator_2ref_[i] = 0;
    }
    for(i = 0; i <= 7;i++)
    {
        Elevator_System__behavior_up[i] = false;
    }
    for(i = 0; i <= 7;i++)
    {
        Elevator_System__behavior_down[i] = false;
    }
    for(i = 0; i <= 7;i++)
    {
        Elevator_System__floor_leds_up_[i] = false;
    }
    for(i = 0; i <= 7;i++)
    {
        Elevator_System__floor_leds_down_[i] = false;
    }
    for(i = 0; i <= 1;i++)
    {
        Elevator_System__cancel_set_2ref_[i] = 0;
    }
    for(i = 0; i <= 1;i++)
    {
        Elevator_System__cancel_set_floor_up_2ref_[i] = 0;
    }
    for(i = 0; i <= 1;i++)
    {
        Elevator_System__cancel_set_floor_down_2ref_[i] = 0;
    }
    for(i = 0; i <= 7;i++)
    {
        Elevator_System__state_blink_[i] = false;
    }
    Elevator_System__alarm_door = false;
    Elevator_System__ptr_qtd = 1;
}

/* Clause OPERATIONS */

void Elevator_System__move(void)
{
    unsigned int i = 0;
    {
        {
            bool flag_behavior;
            int32_t ii;
            bool tmp_up;
            bool tmp_down;
            
            ii = 0;
            flag_behavior = false;
            while((ii) < (8))
            {
                tmp_up = Elevator_System__behavior_up[ii];
                tmp_down = Elevator_System__behavior_down[ii];
                if((tmp_up == true) ||
                (tmp_down == true))
                {
                    flag_behavior = true;
                }
                ii = ii+1;
            }
            if(((((Elevator_System__status_work == true) &&
                        (Elevator_System__status_operation == true)) &&
                    (Elevator_System__status_door == false)) &&
                (Elevator_System__ask_to_repair == false)) &&
            (flag_behavior == true))
            {
                {
                    bool flag_zero;
                    bool tmpUp;
                    bool tmpDown;
                    
                    flag_zero = false;
                    tmpUp = Elevator_System__behavior_up[0];
                    tmpDown = Elevator_System__behavior_down[0];
                    if((tmpUp == true) ||
                    (tmpDown == true))
                    {
                        flag_zero = true;
                    }
                    {
                        int32_t pivo_up;
                        int32_t pivo_down;
                        int32_t ii;
                        bool greedy_ans;
                        
                        pivo_up = 9;
                        pivo_down = 9;
                        ii = 0;
                        while((ii) < (8))
                        {
                            greedy_ans = Elevator_System__behavior_up[ii];
                            if((greedy_ans == true) &&
                            ((ii) < (pivo_up)))
                            {
                                pivo_up = ii;
                            }
                            ii = ii+1;
                        }
                        ii = 0;
                        while((ii) < (8))
                        {
                            greedy_ans = Elevator_System__behavior_down[ii];
                            if((greedy_ans == true) &&
                            ((ii) < (pivo_down)))
                            {
                                pivo_down = ii;
                            }
                            ii = ii+1;
                        }
                        if(flag_zero == true)
                        {
                            Elevator_System__behavior_up[0] = false;
                            Elevator_System__behavior_down[0] = false;
                            Elevator_System__current_direction = Elevator_System__empty;
                            Elevator_System__display_direction_elevator = Elevator_System__empty;
                            Elevator_System__status_door = true;
                            Elevator_System__status_work = false;
                            for(i = 0; i <= 1;i++)
                            {
                                Elevator_System__cancel_set_2ref_[i] = 0;
                            }
                            for(i = 0; i <= 1;i++)
                            {
                                Elevator_System__cancel_set_floor_up_2ref_[i] = 0;
                            }
                            for(i = 0; i <= 1;i++)
                            {
                                Elevator_System__cancel_set_floor_down_2ref_[i] = 0;
                            }
                            Elevator_System__btn_special[Elevator_System__btn_close] = false;
                            Elevator_System__btn_actions_[Elevator_System__current_floor] = false;
                            Elevator_System__floor_leds_up_[Elevator_System__current_floor] = false;
                            Elevator_System__floor_leds_down_[Elevator_System__current_floor] = false;
                            Elevator_System__state_blink_[Elevator_System__current_floor] = false;
                        }
                        else
                        {
                            if(((pivo_down) > (pivo_up)) &&
                            ((Elevator_System__current_direction) != (Elevator_System__down)))
                            {
                                Elevator_System__current_floor = Elevator_System__current_floor+1;
                                Elevator_System__current_direction = Elevator_System__up;
                                Elevator_System__display_direction_elevator = Elevator_System__up;
                                for(i = 0; i <= 1;i++)
                                {
                                    Elevator_System__cancel_set_2ref_[i] = 0;
                                }
                                for(i = 0; i <= 1;i++)
                                {
                                    Elevator_System__cancel_set_floor_up_2ref_[i] = 0;
                                }
                                for(i = 0; i <= 1;i++)
                                {
                                    Elevator_System__cancel_set_floor_down_2ref_[i] = 0;
                                }
                                Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                                Elevator_System__display_floor_[Elevator_System__current_floor-1] = false;
                                Elevator_System__status_work = true;
                                {
                                    int32_t ii;
                                    bool tmp_up;
                                    bool tmp_down;
                                    
                                    ii = 0;
                                    tmp_up = Elevator_System__behavior_up[ii];
                                    tmp_down = Elevator_System__behavior_up[ii];
                                    while((ii) < (8))
                                    {
                                        if(tmp_up == true)
                                        {
                                            Elevator_System__behavior_up[ii-1] = true;
                                            Elevator_System__behavior_up[ii] = false;
                                        }
                                        if(tmp_down == true)
                                        {
                                            Elevator_System__behavior_down[ii+1] = true;
                                            Elevator_System__behavior_down[ii] = false;
                                        }
                                        ii = ii+1;
                                    }
                                }
                            }
                            else
                            {
                                if(((pivo_down) < (pivo_up)) &&
                                ((Elevator_System__current_direction) != (Elevator_System__up)))
                                {
                                    Elevator_System__current_floor = Elevator_System__current_floor-1;
                                    Elevator_System__current_direction = Elevator_System__down;
                                    Elevator_System__display_direction_elevator = Elevator_System__down;
                                    for(i = 0; i <= 1;i++)
                                    {
                                        Elevator_System__cancel_set_2ref_[i] = 0;
                                    }
                                    for(i = 0; i <= 1;i++)
                                    {
                                        Elevator_System__cancel_set_floor_up_2ref_[i] = 0;
                                    }
                                    for(i = 0; i <= 1;i++)
                                    {
                                        Elevator_System__cancel_set_floor_down_2ref_[i] = 0;
                                    }
                                    Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                                    Elevator_System__display_floor_[Elevator_System__current_floor+1] = false;
                                    Elevator_System__status_work = true;
                                    {
                                        int32_t ii;
                                        bool tmp_up;
                                        bool tmp_down;
                                        
                                        ii = 0;
                                        tmp_up = Elevator_System__behavior_up[ii];
                                        tmp_down = Elevator_System__behavior_up[ii];
                                        while((ii) < (8))
                                        {
                                            if(tmp_up == true)
                                            {
                                                Elevator_System__behavior_up[ii+1] = true;
                                                Elevator_System__behavior_up[ii] = false;
                                            }
                                            if(tmp_down == true)
                                            {
                                                Elevator_System__behavior_down[ii-1] = true;
                                                Elevator_System__behavior_down[ii] = false;
                                            }
                                            ii = ii+1;
                                        }
                                    }
                                }
                                else
                                {
                                    if(((pivo_down) > (pivo_up)) &&
                                    (Elevator_System__current_direction == Elevator_System__down))
                                    {
                                        Elevator_System__current_floor = Elevator_System__current_floor-1;
                                        Elevator_System__current_direction = Elevator_System__down;
                                        Elevator_System__display_direction_elevator = Elevator_System__down;
                                        for(i = 0; i <= 1;i++)
                                        {
                                            Elevator_System__cancel_set_2ref_[i] = 0;
                                        }
                                        for(i = 0; i <= 1;i++)
                                        {
                                            Elevator_System__cancel_set_floor_up_2ref_[i] = 0;
                                        }
                                        for(i = 0; i <= 1;i++)
                                        {
                                            Elevator_System__cancel_set_floor_down_2ref_[i] = 0;
                                        }
                                        Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                                        Elevator_System__display_floor_[Elevator_System__current_floor+1] = false;
                                        Elevator_System__status_work = true;
                                        {
                                            int32_t ii;
                                            bool tmp_up;
                                            bool tmp_down;
                                            
                                            ii = 0;
                                            tmp_up = Elevator_System__behavior_up[ii];
                                            tmp_down = Elevator_System__behavior_up[ii];
                                            while((ii) < (8))
                                            {
                                                if(tmp_up == true)
                                                {
                                                    Elevator_System__behavior_up[ii+1] = true;
                                                    Elevator_System__behavior_up[ii] = false;
                                                }
                                                if(tmp_down == true)
                                                {
                                                    Elevator_System__behavior_down[ii-1] = true;
                                                    Elevator_System__behavior_down[ii] = false;
                                                }
                                                ii = ii+1;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        Elevator_System__current_floor = Elevator_System__current_floor+1;
                                        Elevator_System__current_direction = Elevator_System__up;
                                        Elevator_System__display_direction_elevator = Elevator_System__up;
                                        for(i = 0; i <= 1;i++)
                                        {
                                            Elevator_System__cancel_set_2ref_[i] = 0;
                                        }
                                        for(i = 0; i <= 1;i++)
                                        {
                                            Elevator_System__cancel_set_floor_up_2ref_[i] = 0;
                                        }
                                        for(i = 0; i <= 1;i++)
                                        {
                                            Elevator_System__cancel_set_floor_down_2ref_[i] = 0;
                                        }
                                        Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                                        Elevator_System__display_floor_[Elevator_System__current_floor-1] = false;
                                        Elevator_System__status_work = true;
                                        {
                                            int32_t ii;
                                            bool tmp_up;
                                            bool tmp_down;
                                            
                                            ii = 0;
                                            tmp_up = Elevator_System__behavior_up[ii];
                                            tmp_down = Elevator_System__behavior_up[ii];
                                            while((ii) < (8))
                                            {
                                                if(tmp_up == true)
                                                {
                                                    Elevator_System__behavior_up[ii-1] = true;
                                                    Elevator_System__behavior_up[ii] = false;
                                                }
                                                if(tmp_down == true)
                                                {
                                                    Elevator_System__behavior_down[ii+1] = true;
                                                    Elevator_System__behavior_down[ii] = false;
                                                }
                                                ii = ii+1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Elevator_System__elevator_operation_request(int32_t user_orders)
{
    {
        int32_t f1;
        bool flag;
        bool tmp;
        bool tmp2;
        bool tmp3;
        
        f1 = 0;
        flag = true;
        while((f1) < (8))
        {
            tmp = Elevator_System__display_floor_[f1];
            if(((f1) != (Elevator_System__current_floor)) &&
            (tmp == true))
            {
                flag = false;
            }
            f1 = f1+1;
        }
        tmp2 = Elevator_System__display_floor_[Elevator_System__current_floor];
        tmp3 = Elevator_System__btn_special[Elevator_System__btn_phone];
        if((((((((tmp2 == true) &&
                                (flag == true)) &&
                            ((Elevator_System__sensor_balance) <= (450))) &&
                        ((Elevator_System__sensor_balance) > (0))) &&
                    ((user_orders) >= (0))) &&
                ((user_orders) < (Elevator_System__NUM_FLOOR))) &&
            (Elevator_System__status_operation == true)) &&
        (tmp3 == false))
        {
            {
                int32_t delta;
                
                delta = user_orders-Elevator_System__current_floor;
                if((delta) < (0))
                {
                    Elevator_System__behavior_down[Elevator_System__current_floor-user_orders] = true;
                    Elevator_System__btn_actions_[user_orders] = true;
                }
                else
                {
                    Elevator_System__behavior_up[user_orders-Elevator_System__current_floor] = true;
                    Elevator_System__btn_actions_[user_orders] = true;
                }
            }
        }
    }
}

void Elevator_System__elevator_operation_alarm(void)
{
    {
        bool flag_btn_special;
        
        flag_btn_special = Elevator_System__btn_special[Elevator_System__btn_alarm];
        if(((flag_btn_special == false) &&
            (Elevator_System__status_operation == true)) &&
        (Elevator_System__status_work == true))
        {
            Elevator_System__btn_special[Elevator_System__btn_alarm] = true;
        }
    }
}

void Elevator_System__elevator_operation_report(void)
{
    {
        bool flag_btn_special;
        
        flag_btn_special = Elevator_System__btn_special[Elevator_System__btn_phone];
        if((flag_btn_special == false) &&
        (Elevator_System__status_work == true))
        {
            Elevator_System__btn_special[Elevator_System__btn_phone] = true;
            Elevator_System__btn_special[Elevator_System__btn_alarm] = true;
            Elevator_System__status_operation = false;
        }
    }
}

void Elevator_System__elevator_operation_hold_door(void)
{
    if((((Elevator_System__status_work == false) &&
            (Elevator_System__status_door == true)) &&
        (Elevator_System__status_operation == true)) &&
    (Elevator_System__alarm_door == false))
    {
        {
            int32_t ii;
            bool flag_ans;
            bool tmp_up;
            bool tmp_down;
            
            ii = 0;
            flag_ans = false;
            while((ii) < (8))
            {
                tmp_up = Elevator_System__behavior_up[ii];
                tmp_down = Elevator_System__behavior_down[ii];
                if((tmp_up == true) ||
                (tmp_down == true))
                {
                    flag_ans = true;
                }
                ii = ii+1;
            }
            if((Elevator_System__time_door == 10) &&
            (flag_ans == true))
            {
                Elevator_System__time_door = 1;
                Elevator_System__alarm_door = true;
                Elevator_System__sensor_pir = true;
            }
            else
            {
                if(flag_ans == true)
                {
                    Elevator_System__sensor_pir = true;
                    Elevator_System__status_door = true;
                    Elevator_System__time_door = Elevator_System__time_door+1;
                }
                else
                {
                    Elevator_System__sensor_pir = true;
                    Elevator_System__status_door = true;
                    Elevator_System__time_door = 1;
                }
            }
        }
    }
}

void Elevator_System__elevator_operation_open_door(void)
{
    if((((Elevator_System__status_operation == true) &&
            (Elevator_System__alarm_door == false)) &&
        (Elevator_System__current_direction == Elevator_System__empty)) &&
    ((Elevator_System__sensor_balance) > (0)))
    {
        {
            int32_t ii;
            bool flag_ans;
            bool tmp_up;
            bool tmp_down;
            
            ii = 0;
            flag_ans = false;
            while((ii) < (8))
            {
                tmp_up = Elevator_System__behavior_up[ii];
                tmp_down = Elevator_System__behavior_down[ii];
                if((tmp_up == true) ||
                (tmp_down == true))
                {
                    flag_ans = true;
                }
                ii = ii+1;
            }
            if((Elevator_System__time_door == 10) &&
            (flag_ans == true))
            {
                Elevator_System__time_door = 1;
                Elevator_System__alarm_door = true;
                Elevator_System__btn_special[Elevator_System__btn_open] = false;
                Elevator_System__btn_special[Elevator_System__btn_close] = false;
                Elevator_System__status_work = false;
            }
            else
            {
                if(flag_ans == true)
                {
                    Elevator_System__btn_special[Elevator_System__btn_open] = true;
                    Elevator_System__btn_special[Elevator_System__btn_close] = false;
                    Elevator_System__status_door = true;
                    Elevator_System__time_door = Elevator_System__time_door+1;
                    Elevator_System__status_work = false;
                }
                else
                {
                    Elevator_System__btn_special[Elevator_System__btn_open] = true;
                    Elevator_System__btn_special[Elevator_System__btn_close] = false;
                    Elevator_System__status_door = true;
                    Elevator_System__time_door = 1;
                    Elevator_System__status_work = false;
                }
            }
        }
    }
}

void Elevator_System__elevator_operation_close_door(void)
{
    {
        bool flag_btn_special;
        
        flag_btn_special = Elevator_System__btn_special[Elevator_System__btn_close];
        if(((((((flag_btn_special == false) &&
                            (Elevator_System__status_work == false)) &&
                        (Elevator_System__status_operation == true)) &&
                    (Elevator_System__status_door == true)) &&
                (Elevator_System__sensor_pir == false))) ||
        (Elevator_System__alarm_door == true))
        {
            Elevator_System__btn_special[Elevator_System__btn_open] = false;
            Elevator_System__btn_special[Elevator_System__btn_close] = false;
            Elevator_System__status_door = false;
            Elevator_System__alarm_door = false;
            Elevator_System__time_door = 1;
            Elevator_System__status_work = true;
        }
    }
}

void Elevator_System__elevator_operation_let_go(void)
{
    if(Elevator_System__sensor_pir == true)
    {
        Elevator_System__sensor_pir = false;
        Elevator_System__time_door = 1;
    }
}

void Elevator_System__elevator_operation_break_to_repair(void)
{
    unsigned int i = 0;
    {
        if((Elevator_System__status_operation == false) &&
        (Elevator_System__ask_to_repair == true))
        {
            {
                bool flag_behavior;
                int32_t ii;
                bool tmp_up;
                bool tmp_down;
                
                flag_behavior = true;
                ii = 0;
                while((ii) < (Elevator_System__NUM_FLOOR))
                {
                    tmp_up = Elevator_System__behavior_up[ii];
                    tmp_down = Elevator_System__behavior_down[ii];
                    if((tmp_up == true) ||
                    (tmp_down == true))
                    {
                        flag_behavior = false;
                    }
                    ii = ii+1;
                }
                if((flag_behavior == true) ||
                (Elevator_System__current_direction == Elevator_System__empty))
                {
                    Elevator_System__status_work = false;
                    Elevator_System__display_direction_elevator = Elevator_System__empty;
                    Elevator_System__ask_to_repair = false;
                    for(i = 0; i <= 7;i++)
                    {
                        Elevator_System__behavior_up[i] = false;
                    }
                    for(i = 0; i <= 7;i++)
                    {
                        Elevator_System__behavior_down[i] = false;
                    }
                    for(i = 0; i <= 9;i++)
                    {
                        Elevator_System__people_in_elevator_2ref_[i] = 0;
                    }
                    Elevator_System__ptr_qtd = 1;
                    Elevator_System__sensor_balance = 0;
                    Elevator_System__sensor_pir = false;
                }
                else
                {
                    if((((Elevator_System__current_direction == Elevator_System__up) &&
                            ((Elevator_System__current_floor) != (Elevator_System__NUM_FLOOR)))) ||
                    ((Elevator_System__current_floor == 1)))
                    {
                        Elevator_System__status_work = false;
                        Elevator_System__current_floor = Elevator_System__current_floor+1;
                        for(i = 0; i <= 7;i++)
                        {
                            Elevator_System__display_floor_[i] = false;
                        }
                        Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                        Elevator_System__current_direction = Elevator_System__empty;
                        Elevator_System__display_direction_elevator = Elevator_System__empty;
                        Elevator_System__ask_to_repair = false;
                        for(i = 0; i <= 7;i++)
                        {
                            Elevator_System__behavior_up[i] = false;
                        }
                        for(i = 0; i <= 7;i++)
                        {
                            Elevator_System__behavior_down[i] = false;
                        }
                        for(i = 0; i <= 9;i++)
                        {
                            Elevator_System__people_in_elevator_2ref_[i] = 0;
                        }
                        Elevator_System__ptr_qtd = 1;
                        Elevator_System__sensor_balance = 0;
                        Elevator_System__sensor_pir = false;
                    }
                    else
                    {
                        if((((Elevator_System__current_direction == Elevator_System__down) &&
                                ((Elevator_System__current_floor) != (1)))) ||
                        ((Elevator_System__current_floor == Elevator_System__NUM_FLOOR)))
                        {
                            Elevator_System__status_work = false;
                            Elevator_System__current_floor = Elevator_System__current_floor-1;
                            for(i = 0; i <= 7;i++)
                            {
                                Elevator_System__display_floor_[i] = false;
                            }
                            Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                            Elevator_System__current_direction = Elevator_System__empty;
                            Elevator_System__display_direction_elevator = Elevator_System__empty;
                            Elevator_System__ask_to_repair = false;
                            for(i = 0; i <= 7;i++)
                            {
                                Elevator_System__behavior_up[i] = false;
                            }
                            for(i = 0; i <= 7;i++)
                            {
                                Elevator_System__behavior_down[i] = false;
                            }
                            for(i = 0; i <= 9;i++)
                            {
                                Elevator_System__people_in_elevator_2ref_[i] = 0;
                            }
                            Elevator_System__ptr_qtd = 1;
                            Elevator_System__sensor_balance = 0;
                            Elevator_System__sensor_pir = false;
                        }
                    }
                }
            }
        }
    }
}

void Elevator_System__elevator_operation_repaired(void)
{
    unsigned int i = 0;
    {
        if((Elevator_System__status_operation == false) &&
        (Elevator_System__status_work == false))
        {
            Elevator_System__current_direction = Elevator_System__empty;
            Elevator_System__status_door = true;
            Elevator_System__status_work = false;
            Elevator_System__status_operation = true;
            for(i = 0; i <= 7;i++)
            {
                Elevator_System__btn_actions_[i] = false;
            }
            for(i = 0; i <= Elevator_System__ELEVATOR_SPECIAL_BUTTONS__max-1;i++)
            {
                Elevator_System__btn_special[i] = false;
            }
            for(i = 0; i <= 7;i++)
            {
                Elevator_System__display_floor_[i] = false;
            }
            Elevator_System__display_floor_[Elevator_System__current_floor] = true;
            Elevator_System__time_door = 1;
            Elevator_System__sensor_pir = false;
            Elevator_System__sensor_balance = 0;
            Elevator_System__display_direction_elevator = Elevator_System__empty;
            Elevator_System__ask_to_repair = false;
            for(i = 0; i <= 9;i++)
            {
                Elevator_System__people_in_elevator_2ref_[i] = 0;
            }
            Elevator_System__ptr_qtd = 1;
            for(i = 0; i <= 7;i++)
            {
                Elevator_System__behavior_up[i] = false;
            }
            for(i = 0; i <= 7;i++)
            {
                Elevator_System__behavior_down[i] = false;
            }
            for(i = 0; i <= 7;i++)
            {
                Elevator_System__floor_leds_up_[i] = false;
            }
            for(i = 0; i <= 7;i++)
            {
                Elevator_System__floor_leds_down_[i] = false;
            }
            for(i = 0; i <= 1;i++)
            {
                Elevator_System__cancel_set_2ref_[i] = 0;
            }
            for(i = 0; i <= 1;i++)
            {
                Elevator_System__cancel_set_floor_up_2ref_[i] = 0;
            }
            for(i = 0; i <= 1;i++)
            {
                Elevator_System__cancel_set_floor_down_2ref_[i] = 0;
            }
            for(i = 0; i <= 7;i++)
            {
                Elevator_System__state_blink_[i] = false;
            }
            Elevator_System__alarm_door = false;
        }
    }
}

void Elevator_System__enter_elevator(int32_t weight)
{
    if(((((((weight) > (0)) &&
                    (Elevator_System__status_work == false)) &&
                (Elevator_System__status_door == true)) &&
            (Elevator_System__status_operation == true)) &&
        (Elevator_System__alarm_door == false)) &&
    ((Elevator_System__ptr_qtd) < (10)))
    {
        Elevator_System__sensor_balance = Elevator_System__sensor_balance+weight;
        Elevator_System__people_in_elevator_2ref_[Elevator_System__ptr_qtd] = weight;
        Elevator_System__ptr_qtd = Elevator_System__ptr_qtd+1;
    }
}

void Elevator_System__exit_elevator(void)
{
    {
        int32_t ii;
        bool flag_ans;
        int32_t tmp;
        
        ii = 0;
        flag_ans = false;
        while((ii) < (Elevator_System__QTD))
        {
            tmp = Elevator_System__people_in_elevator_2ref_[ii];
            if((tmp) != (0))
            {
                flag_ans = true;
            }
            ii = ii+1;
        }
        if(((((flag_ans == true) &&
                    (Elevator_System__status_door == true)) &&
                (Elevator_System__status_operation == true)) &&
            (Elevator_System__status_work == false)) &&
        (Elevator_System__alarm_door == false))
        {
            Elevator_System__sensor_balance = Elevator_System__sensor_balance-Elevator_System__people_in_elevator_2ref_[Elevator_System__ptr_qtd-1];
            Elevator_System__people_in_elevator_2ref_[Elevator_System__ptr_qtd-1] = 0;
            Elevator_System__ptr_qtd = Elevator_System__ptr_qtd-1;
        }
    }
}

void Elevator_System__get_phone_call_from_elevator(void)
{
    {
        bool flag_btn_special;
        
        flag_btn_special = Elevator_System__btn_special[Elevator_System__btn_phone];
        if(flag_btn_special == true)
        {
            Elevator_System__btn_special[Elevator_System__btn_phone] = false;
            Elevator_System__btn_special[Elevator_System__btn_alarm] = false;
            Elevator_System__ask_to_repair = true;
            Elevator_System__status_operation = false;
        }
    }
}

void Elevator_System__intermediary_call_elevator(int32_t number_floor, Elevator_System__ELEVATOR_DIRECTIONS direction)
{
    {
        bool tmp;
        
        tmp = Elevator_System__btn_special[Elevator_System__btn_phone];
        if(((((((number_floor) > (1)) &&
                        ((number_floor) < (Elevator_System__NUM_FLOOR))) &&
                    ((direction) != (Elevator_System__empty))) &&
                (Elevator_System__status_operation == true)) &&
            (tmp == false)) &&
        ((number_floor) != (Elevator_System__current_floor)))
        {
            if(Elevator_System__sensor_pir == false)
            {
                {
                    int32_t delta;
                    
                    delta = (number_floor-Elevator_System__current_floor);
                    if((delta) < (0))
                    {
                        if(direction == Elevator_System__up)
                        {
                            Elevator_System__behavior_down[Elevator_System__current_floor-number_floor] = true;
                            Elevator_System__status_door = false;
                            Elevator_System__status_work = true;
                            Elevator_System__floor_leds_up_[number_floor] = true;
                        }
                        else
                        {
                            Elevator_System__behavior_down[Elevator_System__current_floor-number_floor] = true;
                            Elevator_System__status_door = false;
                            Elevator_System__status_work = true;
                            Elevator_System__floor_leds_down_[number_floor] = true;
                        }
                    }
                    else
                    {
                        if(direction == Elevator_System__up)
                        {
                            Elevator_System__behavior_up[number_floor-Elevator_System__current_floor] = true;
                            Elevator_System__status_door = false;
                            Elevator_System__status_work = true;
                            Elevator_System__floor_leds_up_[number_floor] = true;
                        }
                        else
                        {
                            Elevator_System__behavior_up[number_floor-Elevator_System__current_floor] = true;
                            Elevator_System__status_door = false;
                            Elevator_System__status_work = true;
                            Elevator_System__floor_leds_down_[number_floor] = true;
                        }
                    }
                }
            }
            else
            {
                {
                    int32_t delta;
                    
                    delta = (number_floor-Elevator_System__current_floor);
                    if((delta) < (0))
                    {
                        if(direction == Elevator_System__up)
                        {
                            Elevator_System__behavior_down[Elevator_System__current_floor-number_floor] = true;
                            Elevator_System__status_door = true;
                            Elevator_System__status_work = false;
                            Elevator_System__floor_leds_up_[number_floor] = true;
                        }
                        else
                        {
                            Elevator_System__behavior_down[Elevator_System__current_floor-number_floor] = true;
                            Elevator_System__status_door = true;
                            Elevator_System__status_work = false;
                            Elevator_System__floor_leds_down_[number_floor] = true;
                        }
                    }
                    else
                    {
                        if(direction == Elevator_System__up)
                        {
                            Elevator_System__behavior_up[number_floor-Elevator_System__current_floor] = true;
                            Elevator_System__status_door = true;
                            Elevator_System__status_work = false;
                            Elevator_System__floor_leds_up_[number_floor] = true;
                        }
                        else
                        {
                            Elevator_System__behavior_up[number_floor-Elevator_System__current_floor] = true;
                            Elevator_System__status_door = true;
                            Elevator_System__status_work = false;
                            Elevator_System__floor_leds_down_[number_floor] = true;
                        }
                    }
                }
            }
        }
    }
}

void Elevator_System__ground_floor_call_elevator(void)
{
    {
        bool flag_btn_special;
        
        flag_btn_special = Elevator_System__btn_special[Elevator_System__btn_phone];
        if((flag_btn_special == false) &&
        (Elevator_System__status_operation == true))
        {
            if(Elevator_System__sensor_pir == true)
            {
                Elevator_System__behavior_down[Elevator_System__current_floor-1] = true;
                Elevator_System__floor_leds_up_[1] = true;
                Elevator_System__status_door = true;
                Elevator_System__status_work = false;
            }
            else
            {
                Elevator_System__behavior_down[Elevator_System__current_floor-1] = true;
                Elevator_System__floor_leds_up_[1] = true;
                Elevator_System__status_door = false;
                Elevator_System__status_work = true;
            }
        }
    }
}

void Elevator_System__last_floor_call_elevator(void)
{
    {
        bool flag_btn_special;
        
        flag_btn_special = Elevator_System__btn_special[Elevator_System__btn_phone];
        if((Elevator_System__status_operation == true) &&
        (flag_btn_special == false))
        {
            if(Elevator_System__sensor_pir == true)
            {
                Elevator_System__behavior_up[Elevator_System__NUM_FLOOR-Elevator_System__current_floor] = true;
                Elevator_System__floor_leds_down_[Elevator_System__NUM_FLOOR] = true;
                Elevator_System__status_door = true;
                Elevator_System__status_work = false;
            }
            else
            {
                Elevator_System__behavior_up[Elevator_System__NUM_FLOOR-Elevator_System__current_floor] = true;
                Elevator_System__floor_leds_down_[Elevator_System__NUM_FLOOR] = true;
                Elevator_System__status_door = false;
                Elevator_System__status_work = true;
            }
        }
    }
}

void Elevator_System__cancel(int32_t num_floor)
{
    {
        bool flag_btn_actions_;
        bool flag_single_req;
        int32_t ii;
        int32_t count;
        bool flag_cancel;
        
        flag_btn_actions_ = Elevator_System__btn_actions_[num_floor];
        flag_single_req = false;
        ii = 0;
        count = 0;
        flag_cancel = false;
        {
            int32_t cond1;
            int32_t cond2;
            
            cond1 = Elevator_System__cancel_set_2ref_[0];
            cond2 = Elevator_System__cancel_set_2ref_[1];
            if((cond1 == num_floor) &&
            (cond2 == num_floor))
            {
                flag_cancel = true;
            }
        }
        while((ii) < (8))
        {
            {
                bool cond;
                
                cond = Elevator_System__behavior_up[ii];
                if(cond == true)
                {
                    count = count+1;
                }
            }
            {
                bool cond;
                
                cond = Elevator_System__behavior_down[ii];
                if(cond == true)
                {
                    count = count+1;
                }
            }
            ii = ii+1;
        }
        if((((num_floor) > (0)) &&
            (flag_btn_actions_ == true)) &&
        (Elevator_System__status_operation == true))
        {
            if(flag_cancel == true)
            {
                {
                    int32_t delta;
                    
                    delta = (num_floor-Elevator_System__current_floor);
                    if(count == 1)
                    {
                        Elevator_System__state_blink_[num_floor] = true;
                    }
                    else
                    {
                        if((delta) < (0))
                        {
                            Elevator_System__behavior_down[Elevator_System__current_floor-num_floor] = false;
                            Elevator_System__btn_actions_[num_floor] = false;
                            Elevator_System__current_direction = Elevator_System__empty;
                            Elevator_System__display_direction_elevator = Elevator_System__empty;
                            Elevator_System__state_blink_[num_floor] = false;
                        }
                        else
                        {
                            Elevator_System__behavior_up[num_floor-Elevator_System__current_floor] = false;
                            Elevator_System__btn_actions_[num_floor] = false;
                            Elevator_System__current_direction = Elevator_System__empty;
                            Elevator_System__display_direction_elevator = Elevator_System__empty;
                            Elevator_System__state_blink_[num_floor] = false;
                        }
                    }
                }
            }
            else
            {
                if((Elevator_System__time) < (2))
                {
                    Elevator_System__time = Elevator_System__time+1;
                    Elevator_System__cancel_set_2ref_[Elevator_System__time] = num_floor;
                    Elevator_System__state_blink_[num_floor] = false;
                }
                else
                {
                    Elevator_System__time = 1;
                    Elevator_System__cancel_set_2ref_[Elevator_System__time] = num_floor;
                    Elevator_System__state_blink_[num_floor] = false;
                }
            }
        }
    }
}

void Elevator_System__cancel_floor(int32_t num_floor, Elevator_System__ELEVATOR_DIRECTIONS direction)
{
    unsigned int i = 0;
    {
        {
            bool flag_leds_up;
            bool flag_leds_down;
            bool flag_cancel_up;
            bool flag_cancel_down;
            int32_t ii;
            int32_t count;
            
            flag_leds_up = false;
            flag_leds_down = false;
            flag_cancel_up = false;
            flag_cancel_down = false;
            ii = 0;
            count = 0;
            {
                bool cond;
                
                cond = Elevator_System__floor_leds_up_[num_floor];
                if(cond == true)
                {
                    flag_leds_up = true;
                }
            }
            {
                bool cond;
                
                cond = Elevator_System__floor_leds_down_[num_floor];
                if(cond == true)
                {
                    flag_leds_down = true;
                }
            }
            {
                int32_t cond1;
                int32_t cond2;
                
                cond1 = Elevator_System__cancel_set_floor_up_2ref_[0];
                cond2 = Elevator_System__cancel_set_floor_up_2ref_[1];
                if((cond1 == num_floor) &&
                (cond2 == num_floor))
                {
                    flag_cancel_up = true;
                }
            }
            {
                int32_t cond1;
                int32_t cond2;
                
                cond1 = Elevator_System__cancel_set_floor_down_2ref_[0];
                cond2 = Elevator_System__cancel_set_floor_down_2ref_[1];
                if((cond1 == num_floor) &&
                (cond2 == num_floor))
                {
                    flag_cancel_down = true;
                }
            }
            ii = 0;
            while((ii) < (8))
            {
                {
                    bool cond1;
                    bool cond2;
                    
                    cond1 = Elevator_System__behavior_up[ii];
                    cond2 = Elevator_System__behavior_down[ii];
                    if(cond1 == true)
                    {
                        count = count+1;
                    }
                    if(cond2 == true)
                    {
                        count = count+1;
                    }
                }
                ii = ii+1;
            }
            if(((((num_floor) != (Elevator_System__current_floor)) &&
                    ((((((direction == Elevator_System__up)) &&
                                    ((flag_leds_up == true)))) ||
                            ((((direction == Elevator_System__down)) &&
                                    ((flag_leds_down == true))))))) &&
                (Elevator_System__status_operation == true)) &&
            ((direction) != (Elevator_System__empty)))
            {
                if(direction == Elevator_System__up)
                {
                    if(flag_cancel_up == true)
                    {
                        if(count == 1)
                        {
                            if(Elevator_System__current_direction == Elevator_System__up)
                            {
                                for(i = 0; i <= 7;i++)
                                {
                                    Elevator_System__behavior_up[i] = false;
                                }
                                for(i = 0; i <= 7;i++)
                                {
                                    Elevator_System__behavior_down[i] = false;
                                }
                                Elevator_System__floor_leds_up_[num_floor] = false;
                                Elevator_System__floor_leds_down_[num_floor] = false;
                                Elevator_System__current_direction = Elevator_System__empty;
                                Elevator_System__display_direction_elevator = Elevator_System__empty;
                                Elevator_System__current_floor = Elevator_System__current_floor+1;
                                Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                                Elevator_System__display_floor_[Elevator_System__current_floor-1] = false;
                            }
                            else
                            {
                                if(Elevator_System__current_direction == Elevator_System__down)
                                {
                                    for(i = 0; i <= 7;i++)
                                    {
                                        Elevator_System__behavior_up[i] = false;
                                    }
                                    for(i = 0; i <= 7;i++)
                                    {
                                        Elevator_System__behavior_down[i] = false;
                                    }
                                    Elevator_System__floor_leds_up_[num_floor] = false;
                                    Elevator_System__floor_leds_down_[num_floor] = false;
                                    Elevator_System__current_direction = Elevator_System__empty;
                                    Elevator_System__display_direction_elevator = Elevator_System__empty;
                                    Elevator_System__current_floor = Elevator_System__current_floor-1;
                                    Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                                    Elevator_System__display_floor_[Elevator_System__current_floor+1] = false;
                                }
                                else
                                {
                                    for(i = 0; i <= 7;i++)
                                    {
                                        Elevator_System__behavior_up[i] = false;
                                    }
                                    for(i = 0; i <= 7;i++)
                                    {
                                        Elevator_System__behavior_down[i] = false;
                                    }
                                    Elevator_System__floor_leds_up_[num_floor] = false;
                                    Elevator_System__floor_leds_down_[num_floor] = false;
                                    Elevator_System__current_direction = Elevator_System__empty;
                                    Elevator_System__display_direction_elevator = Elevator_System__empty;
                                }
                            }
                        }
                        else
                        {
                            if((Elevator_System__current_floor) > (num_floor))
                            {
                                Elevator_System__behavior_down[Elevator_System__current_floor-num_floor] = false;
                                Elevator_System__floor_leds_up_[num_floor] = false;
                                Elevator_System__floor_leds_down_[num_floor] = false;
                                Elevator_System__current_direction = Elevator_System__empty;
                                Elevator_System__display_direction_elevator = Elevator_System__empty;
                            }
                            else
                            {
                                Elevator_System__behavior_up[num_floor-Elevator_System__current_floor] = false;
                                Elevator_System__floor_leds_up_[num_floor] = false;
                                Elevator_System__floor_leds_down_[num_floor] = false;
                                Elevator_System__current_direction = Elevator_System__empty;
                                Elevator_System__display_direction_elevator = Elevator_System__empty;
                            }
                        }
                    }
                    else
                    {
                        if((Elevator_System__time_floor_up) < (2))
                        {
                            Elevator_System__time_floor_up = Elevator_System__time_floor_up+1;
                            Elevator_System__cancel_set_floor_up_2ref_[Elevator_System__time_floor_up] = num_floor;
                        }
                        else
                        {
                            Elevator_System__time_floor_up = 1;
                            Elevator_System__cancel_set_floor_up_2ref_[Elevator_System__time_floor_up] = num_floor;
                        }
                    }
                }
                else
                {
                    if(flag_cancel_down == true)
                    {
                        if(count == 1)
                        {
                            if(Elevator_System__current_direction == Elevator_System__up)
                            {
                                for(i = 0; i <= 7;i++)
                                {
                                    Elevator_System__behavior_up[i] = false;
                                }
                                for(i = 0; i <= 7;i++)
                                {
                                    Elevator_System__behavior_down[i] = false;
                                }
                                Elevator_System__floor_leds_up_[num_floor] = false;
                                Elevator_System__floor_leds_down_[num_floor] = false;
                                Elevator_System__current_direction = Elevator_System__empty;
                                Elevator_System__display_direction_elevator = Elevator_System__empty;
                                Elevator_System__current_floor = Elevator_System__current_floor+1;
                                Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                                Elevator_System__display_floor_[Elevator_System__current_floor-1] = false;
                            }
                            else
                            {
                                if(Elevator_System__current_direction == Elevator_System__down)
                                {
                                    for(i = 0; i <= 7;i++)
                                    {
                                        Elevator_System__behavior_up[i] = false;
                                    }
                                    for(i = 0; i <= 7;i++)
                                    {
                                        Elevator_System__behavior_down[i] = false;
                                    }
                                    Elevator_System__floor_leds_up_[num_floor] = false;
                                    Elevator_System__floor_leds_down_[num_floor] = false;
                                    Elevator_System__current_direction = Elevator_System__empty;
                                    Elevator_System__display_direction_elevator = Elevator_System__empty;
                                    Elevator_System__current_floor = Elevator_System__current_floor-1;
                                    Elevator_System__display_floor_[Elevator_System__current_floor] = true;
                                    Elevator_System__display_floor_[Elevator_System__current_floor+1] = false;
                                }
                                else
                                {
                                    for(i = 0; i <= 7;i++)
                                    {
                                        Elevator_System__behavior_up[i] = false;
                                    }
                                    for(i = 0; i <= 7;i++)
                                    {
                                        Elevator_System__behavior_down[i] = false;
                                    }
                                    Elevator_System__floor_leds_up_[num_floor] = false;
                                    Elevator_System__floor_leds_down_[num_floor] = false;
                                    Elevator_System__current_direction = Elevator_System__empty;
                                    Elevator_System__display_direction_elevator = Elevator_System__empty;
                                }
                            }
                        }
                        else
                        {
                            if((Elevator_System__current_floor) > (num_floor))
                            {
                                Elevator_System__behavior_down[Elevator_System__current_floor-num_floor] = false;
                                Elevator_System__floor_leds_up_[num_floor] = false;
                                Elevator_System__floor_leds_down_[num_floor] = false;
                                Elevator_System__current_direction = Elevator_System__empty;
                                Elevator_System__display_direction_elevator = Elevator_System__empty;
                            }
                            else
                            {
                                Elevator_System__behavior_up[num_floor-Elevator_System__current_floor] = false;
                                Elevator_System__floor_leds_up_[num_floor] = false;
                                Elevator_System__floor_leds_down_[num_floor] = false;
                                Elevator_System__current_direction = Elevator_System__empty;
                                Elevator_System__display_direction_elevator = Elevator_System__empty;
                            }
                        }
                    }
                    else
                    {
                        if((Elevator_System__time_floor_down) < (2))
                        {
                            Elevator_System__time_floor_down = Elevator_System__time_floor_down+1;
                            Elevator_System__cancel_set_floor_down_2ref_[Elevator_System__time_floor_down] = num_floor;
                        }
                        else
                        {
                            Elevator_System__time_floor_down = 1;
                            Elevator_System__cancel_set_floor_down_2ref_[Elevator_System__time_floor_down] = num_floor;
                        }
                    }
                }
            }
        }
    }
}

void print_alarm_door() {
    if(Elevator_System__alarm_door) printf("alarm_door = TRUE\n");
    else printf("alarm_door = FALSE\n");
}

void print_ask_to_repair() {
    if(Elevator_System__ask_to_repair) printf("ask_to_repair = TRUE\n");
    else printf("ask_to_repair = FALSE\n");
}

void print_behavior() {
    for(int i=0;i<8;i++) {
        if(Elevator_System__behavior_up[i]) printf("behavior_up(%d) = TRUE\n", i);
        else printf("behavior_up(%d) = FALSE\n", i);
    }

    for(int i=0;i<8;i++) {
        if(Elevator_System__behavior_down[i]) printf("behavior_down(%d) = TRUE\n", i);
        else printf("behavior_down(%d) = FALSE\n", i);
    }
}

void print_btn_actions() {
    for(int i=0;i<8;i++) {
        if(Elevator_System__btn_actions_[i]) printf("btn_actions(%d) = TRUE\n", i);
        else printf("btn_actions(%d) = FALSE\n", i);
    }
}

void print_btn_special() {
    for(int i = 0; i < Elevator_System__ELEVATOR_SPECIAL_BUTTONS__max;i++) {
        if(Elevator_System__btn_special[i]) {
            if(i == 0) printf("btn_special(btn_alarm) = TRUE\n");
            else if(i == 1) printf("btn_special(btn_phone) = TRUE\n");
            else if(i == 2) printf("btn_special(btn_open) = TRUE\n");
            else printf("btn_special(btn_close) = TRUE\n");
        } 
        else {
            if(i == 0) printf("btn_special(btn_alarm) = FALSE\n");
            else if(i == 1) printf("btn_special(btn_phone) = FALSE\n");
            else if(i == 2) printf("btn_special(btn_open) = FALSE\n");
            else printf("btn_special(btn_close) = FALSE\n");
        }
    }
}

void print_cancel() {
    for(int i = 0; i < 2; i++) {
        printf("cancel_set(%d) = %d\n", i, Elevator_System__cancel_set_2ref_[i]);
    }
    for(int i = 0; i < 2; i++) {
        printf("cancel_set_floor_down(%d) = %d\n", i, Elevator_System__cancel_set_floor_down_2ref_[i]);
    }

    for(int i = 0; i < 2; i++) {
        printf("cancel_set_floor_up(%d) = %d\n", i, Elevator_System__cancel_set_floor_up_2ref_[i]);
    }
}

void print_current() {

    switch (Elevator_System__current_direction)
    {
    case Elevator_System__down:
        printf("current_direction = down\n");
        break;
    
    case Elevator_System__up:
        printf("current_direction = up\n");
        break;
    case Elevator_System__empty:
        printf("current_direction = empty\n");
        break;
    }

    printf("current_floor = %d\n", Elevator_System__current_floor);
}

void print_display_directon() {
    switch (Elevator_System__display_direction_elevator)
    {
    case Elevator_System__down:
        printf("display_direction_elevator = down\n");
        break;
    
    case Elevator_System__up:
        printf("display_direction_elevator = up\n");
        break;
    case Elevator_System__empty:
        printf("display_direction_elevator = empty\n");
        break;
    }
}

void print_display_floor() {
    for(int i = 0; i < 8; i++) {
        if(Elevator_System__display_floor_[i]) printf("display_floor(%d) = TRUE\n", i);
        else printf("display_floor(%d) = FALSE\n", i);
    }
}

void print_floor_leds() {
    for(int i = 0; i < 8; i++) {
        if(Elevator_System__floor_leds_down_[i]) printf("floor_leds_down(%d) = TRUE\n", i);
        else printf("floor_leds_down(%d) = FALSE\n", i);
    }

    for(int i = 0; i < 8; i++) {
        if(Elevator_System__floor_leds_up_[i]) printf("floor_leds_up(%d) = TRUE\n", i);
        else printf("floor_leds_up(%d) = FALSE\n", i);
    }
}

void print_people_in_elev() {
    for(int i = 0; i < 10; i++) {
        printf("people_in_elevator(%d) = %d\n", i, Elevator_System__people_in_elevator_2ref_[i]);
    }
}

void print_ptr_qtd() {
    printf("ptr_qtd = %d\n", Elevator_System__ptr_qtd);
}

void print_sensors() {
    printf("sensor_balance = %d\n", Elevator_System__sensor_balance);

    if(Elevator_System__sensor_pir) printf("sensor_pir = TRUE\n");
    else printf("sensor_pir = FALSE\n");
}

void print_state_blink() {
    for(int i = 0; i < 8; i++) {
        if(Elevator_System__state_blink_[i]) printf("state_blink(%d) = TRUE\n", i);
        else printf("state_blink(%d) = FALSE\n", i);
    }
}

void print_status() {
    if(Elevator_System__status_door) printf("status_door = TRUE\n");
    else printf("status_door = FALSE\n");

    if(Elevator_System__status_operation) printf("status_operation = TRUE\n");
    else printf("status_operation = FALSE\n");

    if(Elevator_System__status_work) printf("status_work = TRUE\n");
    else printf("status_work = FALSE\n");
}

void print_time() {
    printf("time = %d\n", Elevator_System__time);
    printf("time_door = %d\n", Elevator_System__time_door);
    printf("time_floor_down = %d\n", Elevator_System__time_floor_down);
    printf("time_floor_up = %d\n", Elevator_System__time_floor_up);
}
