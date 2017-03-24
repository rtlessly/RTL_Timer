#define DEBUG 0

#include <Arduino.h>
#include <Debug.h>
#include <EventSource.h>

#include "Timer.h"


static DebugHelper Debug("Timer");


//EVENT_ID Timer::TIMER_FIRED_EVENT = EventSource::GenerateEventID();


void Timer::Start(uint32_t interval, uint8_t sourceID)
{
    if (interval != 0) _interval = interval;

    _expired = false;
    _sourceID = sourceID;
    _startTime = millis();
    
    Debug.Log("Start => interval=%l", _interval);
}


void Timer::Cancel()
{
    _expired = true;
    _sourceID = 0;
}


void Timer::Poll()
{
    if (_expired) return;

    uint32_t now = millis();
    uint32_t elapsed = now - _startTime;

    if (elapsed >= _interval)
    {
        _expired = true;
        Debug.Log("Poll => Fired elapsed=%l", elapsed);
        
        TimerEvent event(elapsed, _sourceID);
        
        DispatchEvent(&event);
        _sourceID = 0;
    }
}

