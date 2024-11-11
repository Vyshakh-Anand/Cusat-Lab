#include<stdio.h>

void main()
{
    int ms, mp[10], i, temp, n = 0;  // Declare variables
    char ch = 'y';  // Variable to control the loop for user input

    // Ask the user to enter the total available memory
    printf("\nEnter the total memory available (in Bytes)-- ");
    scanf("%d", &ms);  // Input total memory available in bytes

    temp = ms;  // Copy the total memory to 'temp' which will track remaining memory

    // Loop for entering process memory requests
    // It continues as long as the user wants (ch == 'y')
    for(i = 0; ch == 'y'; i++, n++)  // i is the index for process, n counts the allocated processes
    {
        // Ask the user for memory required by the next process
        printf("\nEnter memory required for process %d (in Bytes) -- ", i + 1);
        scanf("%d", &mp[i]);  // Input the memory requirement for the current process

        // Check if enough memory is available to allocate for this process
        if(mp[i] <= temp)
        {
            // If yes, allocate memory for this process and update remaining memory
            printf("\nMemory is allocated for Process %d ", i + 1);
            temp = temp - mp[i];  // Decrease the remaining available memory
        }
        else
        {
            // If there is not enough memory, print a message and exit the loop
            printf("\nMemory is Full");
            break;  // Exit the loop since no more processes can be allocated
        }

        // Ask the user if they want to continue adding more processes
        printf("\nDo you want to continue(y/n) -- ");
        scanf(" %c", &ch);  // Input to continue or stop. Notice the space before %c to handle newline characters from previous inputs
    }

    // Print the final summary of memory allocation
    printf("\n\nTotal Memory Available -- %d", ms);  // Print total memory available

    // Print the table header for allocated memory
    printf("\n\n\tPROCESS\t\t MEMORY ALLOCATED ");
    
    // Print the memory allocated to each process
    for(i = 0; i < n; i++)  // Iterate over all allocated processes
    {
        printf("\n \t\t%d\t\t\t\t%d", i + 1, mp[i]);  // Process number and allocated memory
    }

    // Print the total memory allocated
    printf("\n\nTotal Memory Allocated is %d", ms - temp);  // Total memory allocated is the original memory minus the remaining memory

    // Print the amount of external fragmentation (unused memory left)
    printf("\nTotal External Fragmentation is %d", temp);  // Remaining memory is the external fragmentation
}

