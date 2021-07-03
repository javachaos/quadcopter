#ifndef GPSSENSOR_H_
#define GPSSENSOR_H_

#include <string>
#include <bits/shared_ptr.h>

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
    void init(shared_ptr<Blackboard> bb);
    void update(shared_ptr<Blackboard> bb);
    virtual ~GPSSensor();
    NMEAData parse(string s);

private:
    string nmea;
    NMEAData mostRecent;
};

}

#endif/*GPSSENSOR_H_*/
