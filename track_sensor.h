#ifndef TRACK_SENSOR_H
#define TRACK_SENSOR_H

const int TRACK_SENSOR_PINS = 4;
void init_track_sensors();
int get_track_sensor_state(int id);

#endif