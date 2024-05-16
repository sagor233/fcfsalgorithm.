#include <stdio.h>

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateTimes(struct Process proc[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            proc[i].completionTime = proc[i].arrivalTime + proc[i].burstTime;
        }
        else
        {
            if (proc[i].arrivalTime > proc[i-1].completionTime)
            {
                proc[i].completionTime = proc[i].arrivalTime + proc[i].burstTime;
            }
            else
            {
                proc[i].completionTime = proc[i-1].completionTime + proc[i].burstTime;
            }
        }
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
    }
}

void findAverageTime(struct Process proc[], int n)
{
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    calculateTimes(proc, n);

    printf("Processes   Arrival Time   Burst Time   Completion Time   Waiting Time   Turnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
        printf("   %d ", proc[i].pid);
        printf("             %d ", proc[i].arrivalTime);
        printf("             %d ", proc[i].burstTime);
        printf("             %d ", proc[i].completionTime);
        printf("             %d ", proc[i].waitingTime);
        printf("             %d\n", proc[i].turnaroundTime);
    }

    printf("Average waiting time = %.2f\n", (float)totalWaitingTime / (float)n);
    printf("Average turnaround time = %.2f\n", (float)totalTurnaroundTime / (float)n);
}

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrivalTime);
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burstTime);
    }

    findAverageTime(proc, n);
    return 0;
}
