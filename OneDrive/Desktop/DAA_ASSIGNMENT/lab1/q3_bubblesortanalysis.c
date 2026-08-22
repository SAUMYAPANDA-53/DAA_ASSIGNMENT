
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 25

int comparison_1 = 0;
int comparison_2 = 0;

void generateRandom(int arr[], int n)
{
    for(int i=0;i<n;i++)
        arr[i]=rand()%100;
}

void copy_array(int src[], int dest[], int n)
{
    for(int i=0;i<n;i++)
        dest[i]=src[i];
}

void bubbleSort_EarlyStop(int arr[], int n)
{
    comparison_1=0;

    for(int i=0;i<n-1;i++)
    {
        int swapped=0;

        for(int j=0;j<n-i-1;j++)
        {
            comparison_1++;
            if(arr[j]>arr[j+1])
            {
                int t=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=t;
                swapped=1;
            }
        }

        if(!swapped)
            break;
    }
}

void bubbleSortFullPass(int arr[], int n)
{
    comparison_2=0;

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            comparison_2++;
            if(arr[j]>arr[j+1])
            {
                int t=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=t;
            }
        }
    }
}

void print_array(int arr[],int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void createCSV(int n)
{
    FILE *fp=fopen("bubble_sort_analysis.csv","w");
    if(fp==NULL)
    {
        printf("Unable to create CSV file.\n");
        return;
    }

    fprintf(fp,"algorithm Comparisons\n");
    fprintf(fp,"early Termination,%d\n",comparison_1);
    fprintf(fp,"full Pass,%d\n",comparison_2);

    fclose(fp);
    printf("\nCSV file 'toh.csv' created successfully.\nOpen it in Excel, LibreOffice or Google Sheets and insert a Line Chart.\n");
}

void print_graph()
{
    printf("\nComparison Graph\n");

    printf("Early Termination : ");
    for(int i=0;i<comparison_1;i+=5)
        printf("*");
    printf(" (%d)\n",comparison_1);

    printf("Full Pass         : ");
    for(int i=0;i<comparison_2;i+=5)
        printf("\u2677");
    printf(" (%d)\n",comparison_2);
}

int main()
{
    int n;
    int arr[MAX],a1[MAX],a2[MAX];

    srand(time(NULL));

    printf(" Bubble Sort Performance Analysis \n");
    printf("Enter number of elements (max %d): ",MAX);
    scanf("%d",&n);

    generateRandom(arr,n);

    copy_array(arr,a1,n);
    copy_array(arr,a2,n);

    printf("\nRandom Array:\n");
    print_array(arr,n);

    bubbleSort_EarlyStop(a1,n);
    bubbleSortFullPass(a2,n);

    printf("\nComparisons (early Termination) : %d\n",comparison_1);
    printf("Comparisons (full Pass) : %d\n",comparison_2);

    createCSV(n);
    print_graph();

    printf(" Time Complexity: \n");
    printf("Early Termination : Best O(n), Worst O(n^2)\n");
    printf("Full Pass : O(n^2)\n");
    printf("Space Complexity  : O(1)\n");

    printf(".. Conclusion: ..");
    printf("The early termination version perform fewer comparisons\n");
    printf("when the array becomes sorted before all passes.\n");
    printf("The full-pass version always perform all passes making it less efficient.");
    

    return 0;
}

/*sample input :
Bubble Sort Performance Analysis 
Enter number of elements (max 25): 10
*/

/*sample output :
Random Array:
7 53 33 58 47 75 17 36 25 43 

Comparisons (early Termination) : 42
Comparisons (full Pass) : 45

CSV file 'toh.csv' created successfully.
Open it in Excel, LibreOffice or Google Sheets and insert a Line Chart.

Comparison Graph
Early Termination : ********* (42)
Full Pass         : ΓÖ╖ΓÖ╖ΓÖ╖ΓÖ╖ΓÖ╖ΓÖ╖ΓÖ╖ΓÖ╖ΓÖ╖ (45)
 Time Complexity: 
Early Termination : Best O(n), Worst O(n^2)
Full Pass : O(n^2)
Space Complexity  : O(1)
.. Conclusion: ..The early termination version perform fewer comparisons
when the array becomes sorted before all passes.
The full-pass version always perform all passes making it less efficient.
*/
