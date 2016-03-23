#ifndef GPSSENSOR_H_
#define GPSSENSOR_H_

#include <string>

using namespace std;
namespace Quadcopter {

public class GPSSensor : public Device {
public:

    struct NMEAData {
        double longitude, latitude;
        double speed;
        double altitude;
        double geoid;
        int fixQuality;
        int numSats;
        double hDilution;
    };

    GPSSensor() : Device(ID_GPS,"GPS Sensor"), nmea("") {}
    void init(Blackboard* bb);
    void update(Blackboard* bb);    
    virtual ~GPSSensor();
    NMEAData parse(string s);

private:
    string nmea;
    NMEAData mostRecent;
};

}

#endif/*GPSSENSOR_H_*/
