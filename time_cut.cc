#include<time.h>
const double TIME_LIMIT = 0.95;
clock_t time_start;
void time_cut_start(){time_start = clock();}
bool check_time_cut(){return 1. * (clock()-time_start) / CLOCKS_PER_SEC < TIME_LIMIT;}
