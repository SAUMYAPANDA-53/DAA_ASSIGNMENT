#include <stdio.h>
#include <math.h>

#define GRAPH_WIDTH 25

// Helper function for clean spacing and alignment
void print_ascii_bar(double cost, double max_val, const char* label) {
    int stars = (int)((cost / max_val) * GRAPH_WIDTH);
    if (stars == 0 && cost > 0) stars = 1;
    if (stars > GRAPH_WIDTH) stars = GRAPH_WIDTH;

    printf("[");
    for (int j = 0; j < stars; j++) printf("*");
    for (int j = stars; j < GRAPH_WIDTH; j++) printf(" ");
    printf("]  %-12s\n", label);
}

int main() {
    int n;

    printf("====================================================\n");
    printf(" LAB Q1: ASCII TIME COMPLEXITY VISUALIZER (User Input)\n");
    printf("====================================================\n");
    printf("Enter the input size (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Defaulting n = 1000.\n");
        n = 1000;
    }

    double max_cost = (double)n;
    double log_val = log2(n);
    if (log_val < 1) log_val = 1;

    // 1. Search(D, k)
    printf("\n--- 1. SEARCH(D, k) for n = %d ---\n", n);
    printf("1. Unsorted Array       : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("2. Sorted Array         : "); print_ascii_bar(log_val, max_cost, "O(log n)");
    printf("3. Singly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("4. Singly Sorted List   : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("5. Doubly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("6. Doubly Sorted List   : "); print_ascii_bar(n, max_cost, "O(n)");

    // 2. Insert(D, x)
    printf("\n--- 2. INSERT(D, x) for n = %d ---\n", n);
    printf("1. Unsorted Array       : "); print_ascii_bar(1.0, max_cost, "O(1)");
    printf("2. Sorted Array         : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("3. Singly Unsorted List : "); print_ascii_bar(1.0, max_cost, "O(1)");
    printf("4. Singly Sorted List   : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("5. Doubly Unsorted List : "); print_ascii_bar(1.0, max_cost, "O(1)");
    printf("6. Doubly Sorted List   : "); print_ascii_bar(n, max_cost, "O(n)");

    // 3. Delete(D, x)
    printf("\n--- 3. DELETE(D, x) for n = %d ---\n", n);
    printf("1. Unsorted Array       : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("2. Sorted Array         : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("3. Singly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("4. Singly Sorted List   : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("5. Doubly Unsorted List : "); print_ascii_bar(1.0, max_cost, "O(1) [Note 1]");
    printf("6. Doubly Sorted List   : "); print_ascii_bar(1.0, max_cost, "O(1) [Note 1]");

    // 4. Maximum(D)
    printf("\n--- 4. MAXIMUM(D) for n = %d ---\n", n);
    printf("1. Unsorted Array       : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("2. Sorted Array         : "); print_ascii_bar(1.0, max_cost, "O(1)");
    printf("3. Singly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("4. Singly Sorted List   : "); print_ascii_bar(1.0, max_cost, "O(1) [Note 2]");
    printf("5. Doubly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("6. Doubly Sorted List   : "); print_ascii_bar(1.0, max_cost, "O(1) [Note 2]");

    // 5. Minimum(D)
    printf("\n--- 5. MINIMUM(D) for n = %d ---\n", n);
    printf("1. Unsorted Array       : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("2. Sorted Array         : "); print_ascii_bar(1.0, max_cost, "O(1)");
    printf("3. Singly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("4. Singly Sorted List   : "); print_ascii_bar(1.0, max_cost, "O(1) [Note 2]");
    printf("5. Doubly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("6. Doubly Sorted List   : "); print_ascii_bar(1.0, max_cost, "O(1) [Note 2]");

    // 6. Predecessor(D, x)
    printf("\n--- 6. PREDECESSOR(D, x) for n = %d ---\n", n);
    printf("1. Unsorted Array       : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("2. Sorted Array         : "); print_ascii_bar(log_val, max_cost, "O(log n)");
    printf("3. Singly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("4. Singly Sorted List   : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("5. Doubly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("6. Doubly Sorted List   : "); print_ascii_bar(1.0, max_cost, "O(1) [Note 3]");

    // 7. Successor(D, x)
    printf("\n--- 7. SUCCESSOR(D, x) for n = %d ---\n", n);
    printf("1. Unsorted Array       : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("2. Sorted Array         : "); print_ascii_bar(log_val, max_cost, "O(log n)");
    printf("3. Singly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("4. Singly Sorted List   : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("5. Doubly Unsorted List : "); print_ascii_bar(n, max_cost, "O(n)");
    printf("6. Doubly Sorted List   : "); print_ascii_bar(1.0, max_cost, "O(1) [Note 3]");

    printf("\n====================================================\n");
    printf(" CONDITIONS / NOTES:\n");
    printf("  [Note 1] Assumes a direct pointer to the item to be deleted is provided[cite: 1].\n");
    printf("  [Note 2] Assumes head/tail pointers are maintained for O(1) access.\n");
    printf("  [Note 3] Given a pointer to element x in a sorted doubly linked list.\n");
    printf("====================================================\n");

    return 0;
}

/* Sample output :
====================================================
 LAB Q1: ASCII TIME COMPLEXITY VISUALIZER (User Input)
====================================================
Enter the input size (n): 6

--- 1. SEARCH(D, k) for n = 6 ---
1. Unsorted Array       : [*************************]  O(n)        
2. Sorted Array         : [**********               ]  O(log n)    
3. Singly Unsorted List : [*************************]  O(n)        
4. Singly Sorted List   : [*************************]  O(n)        
5. Doubly Unsorted List : [*************************]  O(n)        
6. Doubly Sorted List   : [*************************]  O(n)        

--- 2. INSERT(D, x) for n = 6 ---
1. Unsorted Array       : [****                     ]  O(1)        
2. Sorted Array         : [*************************]  O(n)        
3. Singly Unsorted List : [****                     ]  O(1)        
4. Singly Sorted List   : [*************************]  O(n)        
5. Doubly Unsorted List : [****                     ]  O(1)        
6. Doubly Sorted List   : [*************************]  O(n)        

--- 3. DELETE(D, x) for n = 6 ---
1. Unsorted Array       : [*************************]  O(n)        
2. Sorted Array         : [*************************]  O(n)        
3. Singly Unsorted List : [*************************]  O(n)        
4. Singly Sorted List   : [*************************]  O(n)        
5. Doubly Unsorted List : [****                     ]  O(1) [Note 1]
6. Doubly Sorted List   : [****                     ]  O(1) [Note 1]

--- 4. MAXIMUM(D) for n = 6 ---
1. Unsorted Array       : [*************************]  O(n)        
2. Sorted Array         : [****                     ]  O(1)        
3. Singly Unsorted List : [*************************]  O(n)        
4. Singly Sorted List   : [****                     ]  O(1) [Note 2]
5. Doubly Unsorted List : [*************************]  O(n)        
6. Doubly Sorted List   : [****                     ]  O(1) [Note 2]

--- 5. MINIMUM(D) for n = 6 ---
1. Unsorted Array       : [*************************]  O(n)        
2. Sorted Array         : [****                     ]  O(1)        
3. Singly Unsorted List : [*************************]  O(n)        
4. Singly Sorted List   : [****                     ]  O(1) [Note 2]
5. Doubly Unsorted List : [*************************]  O(n)        
6. Doubly Sorted List   : [****                     ]  O(1) [Note 2]

--- 6. PREDECESSOR(D, x) for n = 6 ---
1. Unsorted Array       : [*************************]  O(n)        
2. Sorted Array         : [**********               ]  O(log n)    
3. Singly Unsorted List : [*************************]  O(n)        
4. Singly Sorted List   : [*************************]  O(n)        
5. Doubly Unsorted List : [*************************]  O(n)        
6. Doubly Sorted List   : [****                     ]  O(1) [Note 3]

--- 7. SUCCESSOR(D, x) for n = 6 ---
1. Unsorted Array       : [*************************]  O(n)        
2. Sorted Array         : [**********               ]  O(log n)    
3. Singly Unsorted List : [*************************]  O(n)        
4. Singly Sorted List   : [*************************]  O(n)        
5. Doubly Unsorted List : [*************************]  O(n)        
6. Doubly Sorted List   : [****                     ]  O(1) [Note 3]

====================================================
 CONDITIONS / NOTES:
  [Note 1] Assumes a direct pointer to the item to be deleted is provided[cite: 1].
  [Note 2] Assumes head/tail pointers are maintained for O(1) access.
  [Note 3] Given a pointer to element x in a sorted doubly linked list.
====================================================
*/