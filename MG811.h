/**
    Powered by Smart Technology Benin
    
    @autor: AMOUSSOU Z. Kenneth
    @date: 14-09-2018
    @version: 1.0
*/
#ifndef H_MG811
#define H_MG811

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define DEBUG

class MG811{
    public:
        MG811(uint8_t input);
        void begin(float v400, float v4000);
        float raw();         // return raw data (in volt) from the sensor
        void calibrate();   // set up the sensor by calibrating two references
        float read();       // return the air quality in 'ppm'
        
    private:
        uint8_t _input;
        float _V400;
        float _V40000;
};

#endif
