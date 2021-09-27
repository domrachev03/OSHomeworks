#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct Process {
  char *id;
  int burst, arrival;
};

struct ExecutedProcess {
  struct Process proc;
  int termination_time, remaining_time;
};

struct AlgoStats {
  int processes_amount;
  struct ExecutedProcess *processesStats;
  double AvgTurnaround, AvgWaiting;
};

#define Process struct Process
#define ExecutedProcess struct ExecutedProcess
#define AlgoStats struct AlgoStats

void swap(Process *p1, Process *p2) {
  Process tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}

void sort_processes(int n, Process *procs) {
  for (int i = 0; i < n; ++i) {
    for (int k = 1; k < n - i; ++k) {
      if (procs[k - 1].arrival > procs[k].arrival) {
        swap((procs + k - 1), (procs + k));
      }
    }
  }
}

int next_process(int n, ExecutedProcess *procs, int time_passed,
                 int cur_position) {
  int it = cur_position;
  do {
    it = (it + 1) % n;

    if (procs[it].remaining_time != 0 && procs[it].proc.arrival <= time_passed)
      return it;
  } while (it != cur_position);

  int closest_pos = cur_position;

  do {
    it = (it + 1) % n;
    if (procs[it].remaining_time != 0 &&
        procs[closest_pos].proc.arrival > procs[it].proc.arrival) {
      closest_pos = it;
    }
  } while (it != cur_position);

  return closest_pos;
}

AlgoStats RoundRobin(int n, Process *procs) {
  printf("*** RoundRobin algorithm ***\n");

  int quant;
  printf("IMPORTANT: enter the quant:");
  scanf("%d", &quant);

  ExecutedProcess *processes_info =
      (ExecutedProcess *)malloc(n * sizeof(ExecutedProcess));
  for (int i = 0; i < n; ++i) {
    processes_info[i].proc = procs[i];
    processes_info[i].remaining_time = procs[i].burst;
    processes_info[i].termination_time = 0;
  }

  AlgoStats stats = {n, processes_info, 0, 0};
  int processes_terminated = 0, time_passed = 0, cur_pos = 0;

  while (processes_terminated < n) {
    ExecutedProcess *bestProcess = processes_info + cur_pos;

    time_passed += MAX(bestProcess->proc.arrival - time_passed, 0);
    if (bestProcess->remaining_time == procs[cur_pos].burst)
      stats.AvgWaiting += time_passed;

    time_passed += MIN(quant, bestProcess->remaining_time);
    bestProcess->remaining_time -= MIN(quant, bestProcess->remaining_time);

    if (bestProcess->remaining_time == 0) {
      stats.AvgTurnaround += time_passed - bestProcess->proc.arrival;
      bestProcess->termination_time = time_passed;
      processes_terminated++;
    }

    if (processes_terminated == n)
      break;

    do {
      cur_pos = (cur_pos + 1) % n;
    } while (processes_info[cur_pos].remaining_time == 0);
  }

  stats.AvgWaiting = stats.AvgWaiting * 1.0 / n;
  stats.AvgTurnaround = stats.AvgTurnaround * 1.0 / n;

  return stats;
}

ExecutedProcess *shortest_process(int n, ExecutedProcess *procs, int time) {
  ExecutedProcess *bestProcess = NULL;
  for (int i = 0; i < n; ++i) {
    if (procs[i].remaining_time > 0 && procs[i].proc.arrival <= time &&
        (!bestProcess ||
         bestProcess->remaining_time > procs[i].remaining_time)) {
      bestProcess = procs + i;
    }
  }

  if (!bestProcess) {
    for (int i = 0; i < n; ++i) {
      if (procs[i].remaining_time > 0) {
        bestProcess = procs + i;
      }
    }
  }

  return bestProcess;
}

AlgoStats shortest_job_first(int n, Process *procs) {
  printf("*** Shortest job first Algorithm ***\n");

  ExecutedProcess *processes_info =
      (ExecutedProcess *)malloc(n * sizeof(ExecutedProcess));
  for (int i = 0; i < n; ++i) {
    processes_info[i].proc = procs[i];
    processes_info[i].remaining_time = procs[i].burst;
    processes_info[i].termination_time = 0;
  }

  AlgoStats stats = {n, processes_info, 0, 0};
  int processes_terminated = 0, time_passed = 0;

  while (processes_terminated < n) {
    ExecutedProcess *bestProcess =
        shortest_process(n, processes_info, time_passed);

    time_passed += MAX(bestProcess->proc.arrival - time_passed, 0);
    stats.AvgWaiting += time_passed;

    time_passed += bestProcess->proc.burst;
    stats.AvgTurnaround += bestProcess->proc.burst;
    bestProcess->remaining_time = 0;
    bestProcess->termination_time = time_passed;

    processes_terminated++;
  }

  stats.AvgWaiting = stats.AvgWaiting * 1.0 / n;
  stats.AvgTurnaround = stats.AvgTurnaround * 1.0 / n;

  return stats;
}

AlgoStats FCFS(int n, Process *procs) {
  printf("*** First come - first serve algorithm *** \n");

  ExecutedProcess *processes_info =
      (ExecutedProcess *)malloc(n * sizeof(ExecutedProcess));
  for (int i = 0; i < n; ++i) {
    processes_info[i].proc = procs[i];
    processes_info[i].remaining_time = procs[i].burst;
    processes_info[i].termination_time = 0;
  }

  AlgoStats stats = {n, processes_info, 0, 0};
  int cur_process = 0, time_passed = 0;

  while (cur_process < n) {
    time_passed +=
        MAX(processes_info[cur_process].proc.arrival - time_passed, 0);
    stats.AvgWaiting += time_passed;

    time_passed += procs[cur_process].burst;
    stats.AvgTurnaround += procs[cur_process].burst;
    processes_info[cur_process].remaining_time = 0;
    processes_info[cur_process].termination_time = time_passed;

    cur_process++;
  }

  stats.AvgWaiting = stats.AvgWaiting * 1.0 / n;
  stats.AvgTurnaround = stats.AvgTurnaround * 1.0 / n;
  return stats;
}

void simulation(int processes_amount, Process *procs,
                AlgoStats (*Scheduler)(int, Process *)) {
  int steps;
  sort_processes(processes_amount, procs);

  printf(
      "-------------------------------------------------------------------\n");
  AlgoStats stats = (*Scheduler)(processes_amount, procs);
  printf("\nAlgo finished!\n\nStatistics:\n  Processes list:\n");
  for (int i = 0; i < processes_amount; ++i) {
    printf(
        "    %s:Completion time: %d, Turnaround time: %d, Waiting time: %d\n",
        procs[i].id, stats.processesStats[i].termination_time,
        stats.processesStats[i].termination_time - procs[i].arrival,
        stats.processesStats[i].termination_time - procs[i].arrival -
            procs[i].burst);
  }
  printf("  Average Turnaround time: %lf \n  Average waiting time: %lf \n",
         stats.AvgTurnaround, stats.AvgWaiting);
}

int main() {
  int n;
  scanf("%d", &n);

  Process *processes = (Process *)malloc(n * sizeof(Process));
  for (int i = 0; i < n; ++i) {
    processes[i].id = (char *)malloc(n * sizeof(char));
    scanf("%s%d%d", processes[i].id, &processes[i].burst,
          &processes[i].arrival);
  }

  simulation(n, processes, *FCFS);
  // simulation(n, processes, *shortest_job_first);
  // simulation(n, processes, *RoundRobin);
  return 0;
}
