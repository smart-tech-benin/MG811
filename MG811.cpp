/**
    Powered by Smart Technology Benin
    
    @autor: AMOUSSOU Z. Kenneth
    @date: 14-09-2018
    @version: 1.0
*/
#include "MG811.h"

/**
    Constructor
*/
MG811::MG811(uint8_t input = A0){
    _input = input;
    _V400 = 4.535;  // init value - must be calibrated
    _V40000 = 3.206; // init value - must be calibrated
}

/**
    function: begin
    @summary: Initialize the usage of the sensor with calibrated value
    @parameter:
        v400: the voltage measured by the sensor when placed in a 400ppm C02 
              environment (outdoor or indoor with very good aeration
        v40000: the voltage measured by the sensor when placed in a 40000ppm C02 
              environment
    @return: none
*/
void MG811::begin(float v400, float v40000){
    _V400 = v400;
    _V40000 = v40000;
}

/**
    function: raw
    @summary: measure multiple raw data from the sensor and compute the mean
    @parameter: none
    @return:
        float: return the voltage measured from the sensor
*/
float MG811::raw(){
    uint8_t i = 0;
    float buffer = 0;
    for(i = 0; i < 10; i++){
        buffer += analogRead(_input);
        delay(20); // 20ms
    }
    buffer /= i; // compute the mean
    return map(buffer, 0, 1023, 0, 5);
}

/**
    function: read
    @summary: measure voltage from the sensor and compute the CO2 ppm value
    @parameter: none
    @return:
        float: return the CO2 concentration in 'ppm'
        
        Formulas:
            deltaV = (V400 - V40000)
            A = deltaV/(log10(400) - log10(40000))
            B = log10(400)
            C = (<measurement from sensor in volt> - V400)/A + B
            <CO2 ppm> = pow(10, C)
*/
float MG811::read(){
    float buffer = 0;
    buffer = (_V400 - _V40000)/(log10(400) - log10(40000)); // Delta V
    buffer = (raw() - _V400)/buffer;
    buffer += log10(400);
    return pow(10, buffer);
}

/**
    function: calibrate
    @summary: calibrate the sensor to get reference value for measurement
              
              Power on the sensor
              
              [0] Put the sensor outdoor or indoor with good ventilation
                  Wait at least two (02) hours - for warming up
                  Read it's measurement - You get 400ppm reference voltage
              
              [1] Put the sensor in a bag filled with exhaled air
                  Wait a couple of minutes
                  Read it's measurement - You get 40000ppm reference voltage
              
              The reference value measured by this function should be used with 
              the `begin` method in order to use tthe sensor
              
    @see: this function needs Serial communication to be enabled to print out   
          information
          
          Serial.begin(9600)
    @parameter: none
    @return: none
*/
void MG811::calibrate(){
    uint8_t i = 0;
    Serial.println("Time (mn) \t\t Measurement (volt)");
    for(i = 0; i < 120; i++){
        delay(60000); // wait 1 minute
        Serial.print(i);
        Serial.print("\t\t ");
        Serial.println(raw(), 3);
    }
}


