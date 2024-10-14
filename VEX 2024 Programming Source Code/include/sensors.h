#ifndef SENSORS_H
#define SENSORS_H
#include "v5_vcs.h"
#include "robot-config.h"
#include "queue"
#include "math-tools.h"
#include "parameters.h"

class Sensors {
  private:
    float base_left_pos, base_right_pos, base_left_vel, base_right_vel;
    float base_heading, base_rotation;
    Sensors() {};
    ~Sensors() {};
  public:
    static Sensors *getInstance(){
        static Sensors *p = NULL;
        if (p == NULL){
            p = new Sensors();
        }
        return p;
    }
    static void deleteInstance(){
        Sensors *p = Sensors::getInstance();
        if(p != NULL){
            delete p;
            p = NULL;
        }
    }
    void updateSensors(void);
    float getBaseLeftPos(void);
    float getBaseRightPos(void);
    float getBaseForwardPos(void);
    void resetBaseLeftPos(void);
    void resetBaseRightPos(void);
    void resetBasePos(void);
    float getBaseLeftVel(void);
    float getBaseRightVel(void);
    float getBaseForwardVel(void);
    float getBaseHeading(void);
    void setBaseHeading(float);
    void resetBaseHeading(void);
    float getBaseRotation(void);
    void setBaseRotation(float);
    void resetBaseRotation(void);
};

void autonSensors(void);

#endif 