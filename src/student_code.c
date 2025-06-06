//
// Created by Sam Ogden on 8/8/23.
//

#include "student_code.h"

void finalize_stats(SCHEDULER_STATS* stats) {
    stats->average_response_time = (stats->sum_of_response_time / stats->num_processes_completed);
    stats->average_turnaround_time = (stats->sum_of_turnaround_times / stats->num_processes_completed);
}

void mark_process_start(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
    stats->num_processes_started++;
    stats->sum_of_response_time += (curr_time - p->entry_time);
}

void mark_process_run(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
    p->time_remaining -= time_slice;
}

void mark_process_end(SCHEDULER_STATS* stats, PROCESS* p, float end_time, float time_slice_remaining) {
    stats->sum_of_turnaround_times += (end_time - p->entry_time);
    stats->num_processes_completed++;
}

int compare_priority(PROCESS p1, PROCESS p2) {
    return (int)p2.priority - (int)p1.priority;
}

PROCESS* priority_process_selector(PROCESS_LIST* pl) {
    if(is_empty(pl)){return NULL;} //body of function modified from get_minimum() in process_list.c
    PROCESS* maximum = pl->processes[0];
    for (int i = 1; i < pl->num_processes; i++) {
        if (compare_priority(*maximum, *pl->processes[i]) < 0) {
            // Then the other function is better than the current best
            maximum = pl->processes[i];
        }
    }
    return maximum;
}

PROCESS* fifo_process_selector(PROCESS_LIST* pl) {
    if(is_empty(pl)){return NULL;}
    PROCESS *p = pl->processes[0]; //select first process
    for(int i = 0; i < pl->num_processes; i++){
        if(pl->processes[i]->entry_time < p->entry_time){
            p = pl->processes[i];
        }
    }
    return p;
}

PROCESS* rr_process_selector(PROCESS_LIST* pl) {
    if(is_empty(pl)){return NULL;}
    PROCESS* p = get_next(pl);
    return p;
}

PROCESS* sjf_process_selector(PROCESS_LIST* pl) {
    if(is_empty(pl)){return NULL;}
    PROCESS *p = pl->processes[0]; //select first process
    for(int i = 0; i < pl->num_processes; i++){
        if(pl->processes[i]->length < p->length){
            p = pl->processes[i];
        }
    }
    return p;
}

PROCESS* lifo_process_selector(PROCESS_LIST* pl) {
    if(is_empty(pl)){return NULL;}
    PROCESS *p = pl->processes[0]; //select first process
    for(int i = 0; i < pl->num_processes; i++){
        if(pl->processes[i]->entry_time > p->entry_time){
            p = pl->processes[i];
        }
    }
    return p;
}

PROCESS* stcf_process_selector(PROCESS_LIST* pl) {
    if(is_empty(pl)){return NULL;}
    PROCESS *p = pl->processes[0]; //select first process
    for(int i = 0; i < pl->num_processes; i++){
        if(pl->processes[i]->time_remaining < p->time_remaining){
            p = pl->processes[i];
        }
    }
    return p;
}