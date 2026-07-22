#include <print>
#include "plib/plib.h"

int main (int /*argc*/, char** /*argv*/) {
    PChrono apptiming("");
    // PFile file("data/mission01.test");
    PFile file("data/mission01.data");
    char* bytes = file.getRawData();
    u64 len = file.getSize();

    // State
    const u8 ktime = 0;
    const u8 kid = 1;
    const u8 kevent = 2;

    u8 state = 0;

    u32 time = 0;
    u32 id = 0;
    c8 event; 

    const u64 maxids = 50;
    u64 disabletimes[maxids] = {};
    u64 maxdisabledtimes[maxids] = {};

    u64 capacity = 50;
    u64 mincapacity = 50;
    u64 mincapacitystart = 0;
    u64 mincapacitytime = 0;
    bool inmincapacity = false;

    for(u64 i=2; i<len; i++) {
        if(state == ktime) {
            time = uint_at(bytes, &i);
            i++;
            state = kid;
        } else if(state == kid) {
            id = uint_at(bytes, &i);
            state = kevent;
        } else {
            event = bytes[i];

            if(event == 'd') {
                // disabled
                disabletimes[id] = time;

                capacity--;
                if(capacity < mincapacity) {
                    // new low
                    mincapacity = capacity;
                    mincapacitytime = 0;
                }

                if(capacity == mincapacity) {
                    inmincapacity = true;
                    mincapacitystart = time;
                }
                
                i += 10; // skip >  isabled\nt   the = will be skipped on the for ++
            } else {
                // enabled
                capacity++;

                if(inmincapacity) {
                    inmincapacity = false;
                    u64 newmincapacitytime = time - mincapacitystart;
                    if(newmincapacitytime > mincapacitytime) {
                        mincapacitytime = newmincapacitytime;
                    }
                }

                u64 delay = time - disabletimes[id];
                if(delay > maxdisabledtimes[id]) {
                    maxdisabledtimes[id] = delay;
                    disabletimes[id] = 0;
                }

                i += 9; // skip >  nabled\nt    the = will be skipped on the for ++
            }
            state = ktime;
        }
    }
  
    time++; // for final time
    for(id = 0; id < maxids; id++) {
        if(disabletimes[id] > 0) {
            u64 delay = time - disabletimes[id];
            if(delay > maxdisabledtimes[id]) {
                maxdisabledtimes[id] = delay;
                disabletimes[id] = 0;
            }
        }
    }

    if(inmincapacity) {
        u64 newmincapacitytime = time - mincapacitystart;
        if(newmincapacitytime > mincapacitytime) {
            mincapacitytime = newmincapacitytime;
        }
    }

    u64 maxdelay = 0;
    for(id = 0; id < maxids; id++) {
        if(maxdisabledtimes[id] > maxdelay) {
            maxdelay = maxdisabledtimes[id];
        }
    }

    std::println("Running  >  {}", __FILE_NAME__);
    std::println("Result 1    Max Delay: {}", maxdelay);
    std::println("Result 2    Min Capacity: {}   for {} time", mincapacity, mincapacitytime);

    return 0;
}
