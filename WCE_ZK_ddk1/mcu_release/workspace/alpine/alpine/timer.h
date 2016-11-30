#ifndef TIMER_H
#define TIMER_H


void handler_timer();
void set_timer(int id, int delay);
int wait_timer(int id);
void kill_timer(int id);

#endif