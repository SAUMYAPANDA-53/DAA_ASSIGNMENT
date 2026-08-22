#include <stdio.h>
#include <math.h>


long long move_count = 0;


void towers_of_hanoi(int n, char source, char aux, char dest, int print_moves) {
    if (n == 1) {
        move_count++;
        if (print_moves) {
            printf("  Move disk 1 from %c to %c\n", source, dest);
        }
        return;
    }

    
    towers_of_hanoi(n - 1, source, dest, aux, print_moves);

    
    move_count++;
    if (print_moves) {
        printf("  Move disk %d from %c to %c\n", n, source, dest);
    }

    
    towers_of_hanoi(n - 1, aux, source, dest, print_moves);
}

int main() {
    
    printf(" TOWERS OF HANOI (ToH) SIMULATION & ANALYSIS  \n");
    

    int demo_discs = 3;
    move_count = 0;
    printf("--- Step-by-Step Moves for n = %d discs ---\n", demo_discs);
    towers_of_hanoi(demo_discs, 'A', 'B', 'C', 1);
    printf("Total Moves for %d discs: %lld\n\n", demo_discs, move_count);

   
    
    printf("%-10s | %-18s | %-18s\n", "Discs (n)", "Simulated Moves", "Theoretical (2^n - 1)");
   

    int max_discs = 20; 
    for (int n = 1; n <= max_discs; n++) {
        move_count = 0;
        
        towers_of_hanoi(n, 'A', 'B', 'C', 0); 

        long long theoretical_moves = (1LL << n) - 1; 

        printf("%-10d | %-18lld | %-18lld\n", n, move_count, theoretical_moves);
    }

    

    return 0;
}

/* Sample output :
TOWERS OF HANOI (ToH) SIMULATION & ANALYSIS  
--- Step-by-Step Moves for n = 3 discs ---
  Move disk 1 from A to C
  Move disk 2 from A to B
  Move disk 1 from C to B
  Move disk 3 from A to C
  Move disk 1 from B to A
  Move disk 2 from B to C
  Move disk 1 from A to C
Total Moves for 3 discs: 7

Discs (n)  | Simulated Moves    | Theoretical (2^n - 1)
1          | 1                  | 1                 
2          | 3                  | 3                 
3          | 7                  | 7                 
4          | 15                 | 15                
5          | 31                 | 31                
6          | 63                 | 63                
7          | 127                | 127               
8          | 255                | 255               
9          | 511                | 511               
10         | 1023               | 1023              
11         | 2047               | 2047              
12         | 4095               | 4095              
13         | 8191               | 8191              
14         | 16383              | 16383             
15         | 32767              | 32767             
16         | 65535              | 65535             
17         | 131071             | 131071            
18         | 262143             | 262143            
19         | 524287             | 524287            
20         | 1048575            | 1048575 */
