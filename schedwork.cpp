#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
  const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCnt,
    size_t day
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
    size_t n= avail.size();
    size_t k =avail[0].size();
    sched.assign(n, vector<Worker_T>());
    vector<size_t> shiftCnt(k,0);
    return scheduleHelper(avail,dailyNeed,maxShifts,sched,shiftCnt,0);

}

bool scheduleHelper(
  const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCnt,
    size_t day
    ){
      if(day==avail.size()){
        return true;
      }
      size_t k = avail[0].size();

      if(sched[day].size() == dailyNeed){
        return scheduleHelper(avail, dailyNeed,maxShifts,sched,shiftCnt,day+1);        
      }
      for(size_t w =0; w<k; ++w){
        if(shiftCnt[w]<maxShifts && find(sched[day].begin(),sched[day].end(),w)==sched[day].end() && avail[day][w]){
          sched[day].push_back(w);
          shiftCnt[w]++;

          if(scheduleHelper(avail,dailyNeed,maxShifts,sched,shiftCnt,day)){
            return true;
          }

          sched[day].pop_back();
          shiftCnt[w]--;
        }
      }
      return false;
    }
