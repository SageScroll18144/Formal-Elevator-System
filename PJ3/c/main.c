#include <stdio.h>
#include <stdbool.h>
#include "Elevator_System.h"

int main() {

    Elevator_System__INITIALISATION();

    int flag = 1, w, d; 

    while(flag) {
        printf("Escolha uma operação: ");
        printf("\n\t - 1) Move\n\t - 2) Requisicao Interna do Elevator\n\t - 3) Alarme\n\t - 4) Reportar\n\t - 5) Segurar a porta\n\t - 6) Abrir a porta\n\t - 7) Fechar porta\n\t - 8) LetGo(Tirar mão da porta)\n\t - 9) Parar elevador para reparo\n\t - 10) Reparar\n\t - 11) Entrar no elevador\n\t - 12) Sair do elevador\n\t - 13) Portaria atender interfone\n\t - 14) Chamada externa de pavimento\n\t - 15) Cancelamento interno\n\t - 16) Cancelamento externo\n");
        printf(".: ");

        int op;
        scanf("%d", &op);

        switch (op) {
        case 1:
            Elevator_System__move();
            break;
        
        case 2:
            printf(" - Informe o andar que você deseja: "); 
            w;
            scanf("%d", &w);
            Elevator_System__elevator_operation_request(w);
            break;

        case 3:
            Elevator_System__elevator_operation_alarm();
            break;

        case 4:
            Elevator_System__elevator_operation_report();
            break;

        case 5:
            Elevator_System__elevator_operation_hold_door();
            break;

        case 6:
            Elevator_System__elevator_operation_open_door();
            break;

        case 7:
            Elevator_System__elevator_operation_close_door();
            break;

        case 8:
            Elevator_System__elevator_operation_let_go();
            break;

        case 9:
            Elevator_System__elevator_operation_break_to_repair();
            break;

        case 10:
            Elevator_System__elevator_operation_repaired();
            break;
        
        case 11:
            printf(" - Informe o seu peso: "); 
            w;
            scanf("%d", &w);
            Elevator_System__enter_elevator(w);
            break;

        case 12:
            Elevator_System__exit_elevator();
            break;
        
        case 13:
            Elevator_System__get_phone_call_from_elevator();
            break;
        
        case 14:
            w;
            printf(" - Informe o andar: ");
            scanf("%d", &w);
            if(w >= 8) {
                Elevator_System__last_floor_call_elevator();
            }
            else if(w == 1) {
                Elevator_System__ground_floor_call_elevator();
            } else {
                d;
                printf(" - Informe a direção | 1 -> up | 0 -> down: ");
                scanf("%d", &d);

                if(d) {
                    Elevator_System__intermediary_call_elevator(w, Elevator_System__up);
                } else {
                    Elevator_System__intermediary_call_elevator(w, Elevator_System__down);
                }
            }

            break;

        case 15:
            w;
            printf(" - Informe o andar: ");
            scanf("%d", &w);
            Elevator_System__cancel(w);
            break;

        case 16:
            w;
            printf(" - Informe o andar: ");
            scanf("%d", &w);
            d;
            printf(" - Informe a direção | 1 -> up | 0 -> down: ");
            scanf("%d", &d);
            switch (d)
            {
            case 1:
                Elevator_System__cancel_floor(w, Elevator_System__up);
                break;
            
            case 0:
                Elevator_System__cancel_floor(w, Elevator_System__down);
                break;
            }
            break;    

        default:
            flag = 0;
        }

        // Historico
        print_alarm_door();
        print_ask_to_repair();
        print_behavior();
        print_btn_actions();
        print_btn_special();
        print_cancel();
        print_current();
        print_display_directon();
        print_display_floor();
        print_floor_leds();
        print_people_in_elev();
        print_ptr_qtd();
        print_sensors();
        print_state_blink();
        print_status();
        print_time();
        
    }

    return 0;
}
