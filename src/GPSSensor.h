#ifndef GPSSENSOR_H_
#define GPSSENSOR_H_

#include ""

namespace Quadcopter {

public class GPSSensor : public Device {
public:
    GPSSensor() : Device(ID_GPS,"GPS Sensor") {}
    
protected:
private:

};

}

#endif/*GPSSENSOR_H_*/
