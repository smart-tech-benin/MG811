# MG811

In Indoor Air Quality (IAQ) measurement unit, the MG811 could be used to evaluate 
the amount of `C02` in the air. The aim of this project is to provide a library 
for simple usage of these modules.

## How does the sensor work

Checkout the `docs` directory to found interresting documents about this sensor 
and the way it operate.

## Electricial requirement

While it is useful to checkout the documents on the sensor, it is important to 
accentuated that the sensor require `140mA ± 20mA` for is heater. So, when using 
this sensor with multiple others on the Arduino board, make sure to have enought 
current or it.

|Characteristics | Value|
|:---------------:|:--------:|
|Model | MG811 |
|Sensor type | Solid Electrolyte |
|Target gas | CO2 |
|Detection range | 350ppm - 10000ppm |
|Heater resistance | 35Ω ± 3Ω |
|Heater current | 140 ± 20mA |
|Heater voltage | 6.0V ± 0.1V AC or DC |
|Heater consumption | 850mW ± 120mW |
|Standard working condition | 20 ~ 50°C, under 95%RH |
|Zero point EMF | 200mV - 600mV |
|DEMF output signal | ≧ 25mV/1000ppm CO2 |

## Usage

This library is quite straightforward. 

```C++
    MG811 mySensor = MG811(A0) // Analog pin A0
```

For the sensor's calibration follow the steps describe below:

Power on the sensor
              
- **First step**
    - Put the sensor outdoor or indoor with good ventilation
    - Wait at least two (02) hours - for warming up
    - Read it's measurement - You get 400ppm reference voltage

- **Second step**
    - Put the sensor in a bag filled with exhaled air
    - Wait a couple of minutes
    - Read it's measurement - You get 40000ppm reference voltage

The reference values measured should be used with  the `begin` method in order
to use the sensor. The method `calibrate` helps you out with the calibration process.

```C++
    mySensor.calibrate()
```


**Note:** The sensor must be first calibrated to get some reference value.

After calibration, you can keep going with the following:

```C++
    float v400 = 4.535;     // should be set after calibration
    float v40000 = 3.206;   // should be set after calibration
    
    mySensor.begin(v400, v40000); // set the reference values in the library
```

The sensor could be used then by reading the raw voltage value or `CO2 concentration` in 
`ppm`

```C++
    mySensor.raw();     // read raw value
    mySensor.read();    // read CO2 concentration in ppm
```


