// #include <stdio.h>
// #include <string.h>

// #define MAX_STATES 20
// #define MAX_SYMBOLS 10

// typedef struct {
//     int current_state;
//     char symbol;
//     int next_state;
// } Transition;

// Transition transitions[MAX_STATES * MAX_SYMBOLS];
// int num_states, num_symbols, num_transitions = 0;
// char symbols[MAX_SYMBOLS];
// int accept_states[MAX_STATES];
// int num_accept_states;
// int start_state;

// // Function to find the next state
// int get_next_state(int current_state, char symbol) {
//     for (int i = 0; i < num_transitions; i++) {
//         if (transitions[i].current_state == current_state && transitions[i].symbol == symbol) {
//             return transitions[i].next_state;
//         }
//     }
//     return -1;  // No valid transition
// }

// // Validate string against finite automata
// int validate_string(const char* input_string) {
//     int current_state = start_state;

//     for (int i = 0; i < strlen(input_string); i++) {
//         char symbol = input_string[i];
//         int next_state = get_next_state(current_state, symbol);
        
//         if (next_state == -1) {
//             return 0;  // Invalid string
//         }
//         current_state = next_state;
//     }

//     // Check if final state is accepting
//     for (int i = 0; i < num_accept_states; i++) {
//         if (current_state == accept_states[i]) {
//             return 1;  // Valid string
//         }
//     }
//     return 0;
// }

// int main() {
//     // Input symbols
//     printf("Number of input symbols: ");
//     scanf("%d", &num_symbols);
    
//     printf("Input symbols (space separated): ");
//     for (int i = 0; i < num_symbols; i++) {
//         scanf(" %c", &symbols[i]);
//     }

//     // Input states
//     printf("Enter number of states: ");
//     scanf("%d", &num_states);

//     // Initial state
//     printf("Initial state: ");
//     scanf("%d", &start_state);

//     // Accepting states
//     printf("Number of accepting states: ");
//     scanf("%d", &num_accept_states);
    
//     printf("Accepting states (space separated): ");
//     for (int i = 0; i < num_accept_states; i++) {
//         scanf("%d", &accept_states[i]);
//     }

//     // Transitions
//     printf("Enter transitions in format: current_state symbol next_state\n");
//     printf("Type -1 to stop.\n");

//     while (1) {
//         int current, next;
//         char symbol;
        
//         scanf("%d", &current);
//         if (current == -1) break;
        
//         scanf(" %c %d", &symbol, &next);
        
//         transitions[num_transitions].current_state = current;
//         transitions[num_transitions].symbol = symbol;
//         transitions[num_transitions].next_state = next;
//         num_transitions++;
//     }

//     // Validate input string
//     char input_string[100];
//     printf("Input string: ");
//     scanf("%s", input_string);
    
//     if (validate_string(input_string)) {
//         printf("Valid String\n");
//     } else {
//         printf("Invalid String\n");
//     }
    
//     return 0;
// }


#include <stdio.h>
#include <string.h>

int main()
{
    int num_symbols, num_states, num_transitions = 0;
    char symbols[10];
    int start_state,num_accept_states, accepting_states[100], transition_table[100][100];

    printf("Number of input symbols :");
    scanf("%d", &num_symbols);

    printf("Input symbols (space separated): ");
    for (int i = 0; i < num_symbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter number of states :");
    scanf("%d", &num_states);

    printf("Inirial states :");
    scanf("%d", &start_state);

    printf("Number of accepting states:");
    scanf("%d", &num_accept_states);

    printf("Accepting states :");
    for(int i = 0; i < num_accept_states; i++){
        scanf("%d", &accepting_states[i]);
    }

    printf("Enter transitions in format: current_state symbol next_state\n");
    printf("Type -1 to stop.\n");

    int current, next;
    char symbol;

    while(1) {
        scanf("%d", &current);
        if (current == -1) break;

        scanf(" %c %d", &symbol, &next);

        transition_table[current][symbol] = next;
    }

    int current_state = start_state;
    int valid = 1,l=1;
    char input_string[100];
    
    while(l=1){
        printf("Enter input string :\n");
        scanf("%s", input_string);
        
        
        for(int i = 0; i <strlen(input_string); i++) {
            char input_symbol = input_string[i];
            int next_state = transition_table[current][input_symbol];
            
            if (next_state == '\0'){
                valid = 0;
                break;
            }
            current_state = next_state;
        }

        int is_accpting=0;
        for(int i= 0; i < num_accept_states; i++) {
            if(accepting_states[i] == current_state) {
                is_accpting = 1;
                break;
            }
        }

        if(valid && is_accpting) {
        printf("Valid String\n");
        } else {
            printf("Invalid String\n");
        }

        printf("Second String : ");
        scanf("%d",l);

        if(l==0) break;
    }
    

    


    return 0;
}
