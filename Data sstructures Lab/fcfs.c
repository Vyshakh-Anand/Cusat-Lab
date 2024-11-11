#include <stdio.h>
#include <string.h>

int main() {
    char pn[10][10];        // Process names
    int arr[10], bur[10];   // Arrival times and Burst times
    int star[10], finish[10], tat[10], wt[10]; // Start time, Finish time, Turnaround time, Waiting time
    int i, n;
    int totwt = 0, tottat = 0; // Totals for waiting time and turnaround time

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input details for each process
    for (i = 0; i < n; i++) {
        printf("Enter the Process Name, Arrival Time & Burst Time: ");
        scanf("%s %d %d", pn[i], &arr[i], &bur[i]);
    }

    // Sort the processes based on Arrival Time using bubble sort
    for (i = 0; i < n; i++) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j]) {
                // Swap arrival times
                int temp_arr = arr[i];
                arr[i] = arr[j];
                arr[j] = temp_arr;

                // Swap burst times
                int temp_bur = bur[i];
                bur[i] = bur[j];
                bur[j] = temp_bur;

                // Swap process names
                char temp_pn[10];
                strcpy(temp_pn, pn[i]);
                strcpy(pn[i], pn[j]);
                strcpy(pn[j], temp_pn);
            }
        }
    }

    // Calculate Start Time, Waiting Time, Finish Time, and Turnaround Time for each process
    for (i = 0; i < n; i++) {
        if (i == 0) {
            star[i] = arr[i];  // Start time for the first process is its arrival time
            wt[i] = star[i] - arr[i];  // Waiting time = Start time - Arrival time
            finish[i] = star[i] + bur[i];  // Finish time = Start time + Burst time
            tat[i] = finish[i] - arr[i];  // Turnaround time = Finish time - Arrival time
        } else {
            star[i] = finish[i - 1];  // Start time for subsequent processes
            wt[i] = star[i] - arr[i];  // Waiting time = Start time - Arrival time
            finish[i] = star[i] + bur[i];  // Finish time = Start time + Burst time
            tat[i] = finish[i] - arr[i];  // Turnaround time = Finish time - Arrival time
        }
    }

    // Print Process details and calculate total waiting time and turnaround time
    printf("\nPName  Arrtime  Burtime  Start  TAT  Finish\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", pn[i], arr[i], bur[i], star[i], tat[i], finish[i]);
        totwt += wt[i];
        tottat += tat[i];
    }

    // Calculate and print the averages
    printf("\nAverage Waiting time: %.2f", (float)totwt / n);
    printf("\nAverage Turn Around Time: %.2f", (float)tottat / n);

    return 0;
}

