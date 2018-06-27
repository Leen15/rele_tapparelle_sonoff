# Rollers control with sonoff
This sketch allow to control rollers with sonoff output  (ON roller UP, OFF roller down) with a single arduino nano.
Outputs have state inverted for work with sainsmart relay modules.   
   

# Configuration

In the first part of the sketch you can find the configuration for every roller:
```
Tapp1_IN_Pin = 2; -> input from sonoff
Tapp1_OUT_Pin_UP = 3; -> output to first relay 
Tapp1_OUT_Pin_DOWN = 4; -> output to second relay
Tapp1_UP_duration = 25000; -> time for up (milliseconds)
Tapp1_DOWN_duration = 19000; -> time for down (milliseconds)
inverted_delay = 500; -> this is a delay if you change the state before the roller cycle
```
