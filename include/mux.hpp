#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "commonstate.hpp"
#include "param.hpp"
#include "board.hpp"


namespace rosflight {

class Mux {
public:
    typedef enum
    {
        RATE, // Channel is is in rate mode (mrad/s)
        ANGLE, // Channel command is in angle mode (mrad)
        THROTTLE, // Channel is direcly controlling throttle max/1000
        ALTITUDE, // Channel is commanding a specified altitude in cm
        PASSTHROUGH, // Channel directly passes PWM input to the mixer
    } control_type_t;

    typedef struct
    {
        bool active; // Whether or not the channel is active
        control_type_t type;  // What type the channel is
        float value; // The value of the channel
    } control_channel_t;

    typedef struct
    {
        control_channel_t x;
        control_channel_t y;
        control_channel_t z;
        control_channel_t F;
    } control_t;
public:
    void init(CommonState* _common_state, Board* _board, Params* _params);
    bool mux_inputs();

    control_t& rc_control() { return _rc_control; }
    control_t& offboard_control() { return _offboard_control; }
    control_t& combined_control() { return _combined_control; }

    void set_new_command(bool val) { _new_command = val; }

private:
    CommonState* common_state;
    Params* params;
    Board* board;

    control_t _rc_control;
    control_t _offboard_control;
    control_t _combined_control;

    bool _new_command;

    control_t _failsafe_control = {
        {true, ANGLE, 0.0},
        {true, ANGLE, 0.0},
        {true, RATE, 0.0},
        {true, THROTTLE, 0.0}};
};

} //namespace