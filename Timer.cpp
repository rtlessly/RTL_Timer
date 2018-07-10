#define DEBUG 0

#include <Arduino.h>
#include <Debug.h>
#include <EventSource.h>

#include "Timer.h"


DEFINE_CLASSNAME(Timer);

void Timer::Start(uint32_t interval, uint8_t sourceID)
{
    if (interval != 0) _interval = interval;

    _expired = false;
    _sourceID = sourceID;
    _startTime = millis();

    TRACE(Logger(_classname_, this) << F("Start: interval=") << _interval << endl);
}


void Timer::Cancel()
{
    _expired = true;
    _sourceID = 0;
}


void Timer::Poll()
{
    TRACE(Logger(_classname_, this) << F("Poll") << endl);

    if (_expired) return;

    auto now = millis();
    auto elapsed = now - _startTime;

    if (elapsed >= _interval)
    {
        _expired = true;
        TRACE(Logger(_classname_, this) << F("Fired: elapsed=") << elapsed << endl);

        TimerEvent event(elapsed, _sourceID);

        DispatchEvent(event);
        _sourceID = 0;
    }
}

