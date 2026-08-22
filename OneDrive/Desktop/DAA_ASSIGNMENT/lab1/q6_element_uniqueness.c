
#include <stdio.h>

#define MAX 100

int has_Duplicates(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
                return 1;
        }
    }
    return 0;
}

void print_Array(int arr[], int n)
{
    printf("\nArray: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[MAX];
    int n;

    printf("****** Element Uniqueness Check ******\n");

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d numbers:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    print_Array(arr, n);

    if (has_Duplicates(arr, n))
        printf("\nDuplicate elements are present.\n");
    else
        printf("all elements are unique.\n");

    printf("\nTime Complexity  : O(n^2)\n");
    printf("Space Complexity : O(1)\n");

    printf("\nConclusion:\n");
    printf("This method compares every pair of elements.\n");
    printf("For sufficiently large values of n, it becomes slow because\n");
    printf("the number of comparisons grows quadratically.\n");
    printf("More efficient methods such as sorting or hashing can be used for large datasets.\n");

    return 0;
}
/*        sample input :
****** Element Uniqueness Check ******
Enter number of elements: 5
Enter 5 numbers:
1 4 7 8 3*/

/*       sample output :
Array: 1 4 7 8 3 
all elements are unique.

Time Complexity  : O(n^2)
Space Complexity : O(1)

Conclusion:
This method compares every pair of elements.
For sufficiently large values of n, it becomes slow because
the number of comparisons grows quadratically.
More efficient methods such as sorting or hashing can be used for large datasets.*/
