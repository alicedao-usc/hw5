#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
void schedFill(const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched);
bool isValid(const size_t maxShifts, const int worker, DailySchedule& sched);
bool scheduleHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day,
    int col
    );

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below


    //recursive solution is based around dates
    //if all days are filled up then we know a valid solution can be made
    //we will recurse through each day and for each day we will find the workers that are available and 
    //slot them in
    //if our assignment is not valid, then we can just back track


    schedFill(avail, dailyNeed, sched);
    bool valid = scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0);
    return valid;
}

void schedFill(const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched){
    for(unsigned int i = 0; i < avail.size(); i++){
        vector<Worker_T> t;
        for(unsigned int j = 0; j < dailyNeed; j++){
            t.push_back(INVALID_ID);
        }
        sched.push_back(t);
    }
}


bool scheduleHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day,
    int col)
    {

    if((unsigned int)day == avail.size()){
        return true;
    }

    if((unsigned int)col == dailyNeed){
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, day + 1, 0);

    }
    else if(sched[day][col] == INVALID_ID){
        for(unsigned int i=0; i< avail[day].size(); i++){
            if(avail[day][i] == 1){
                sched[day][col] = i;
                if(isValid(maxShifts, i, sched)){
                    if(scheduleHelper(avail, dailyNeed, maxShifts, sched, day, col + 1)){
                        return true;
                    }
                }
            }
        }
        sched[day][col] = INVALID_ID;
    }

    return false;

}


bool isValid(const size_t maxShifts, const int worker, DailySchedule& sched){
    
    unsigned int dailyS = 0;
    unsigned int weeklyS = 0;

    for(unsigned int i = 0; i < sched.size(); i++){
        for(unsigned int j = 0; j < sched[i].size(); j++){
            if(sched[i][j] == (unsigned int)worker){
                dailyS++;
                weeklyS++;
            }
        }
        if(dailyS > 1){
            return false;
        }
        dailyS = 0;
    }
    if(weeklyS > maxShifts){
        return false;
    }
    return true;
}
