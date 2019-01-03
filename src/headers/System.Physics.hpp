#ifndef _SYSTEM_PHYSICS_HPP
#define _SYSTEM_PHYSICS_HPP

#include "System.hpp"

namespace System {
namespace Physics {

//Distance conversions
const long double AU_TO_M = 1.49597870700E11;
const long double M_TO_AU = 1.0 / AU_TO_M;

const long double AU_TO_KM = 1.496E8;
const long double KM_TO_AU = 1.0 / AU_TO_KM;

const long double KM_TO_M = 1000;
const long double M_TO_KM = 1.0 / KM_TO_M;

const long double M_TO_CM = 100;
const long double CM_TO_M = 1.0 / M_TO_CM;

const long double CM_TO_MM = 10;
const long double MM_TO_CM = 1.0 / CM_TO_MM;

//Time conversions
const long double YEARS_TO_DAYS = 365.25;
const long double DAYS_TO_YEARS = 1.0 / YEARS_TO_DAYS;

const long double DAYS_TO_HOURS = 24;
const long double HOURS_TO_DAYS = 1.0 / DAYS_TO_HOURS;

const long double HOURS_TO_MINUTES = 60;
const long double MINUTES_TO_HOURS = 1.0 / HOURS_TO_MINUTES;

const long double MINUTES_TO_SECONDS = 60;
const long double SECONDS_TO_MINUTES = 1.0 / MINUTES_TO_SECONDS;

//Mass conversions

//Mass constants
const long double EARTH_MASS_KG = 5.9742E24;

//https://docs.unity3d.com/ScriptReference/Rigidbody.html
/*class Rigidbody {
    public:

};

class ISimulation {
    public:
        virtual void Step(long double timestep) = 0;
};*/

}
}

#endif