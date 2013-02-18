#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "utils/utils.h"
#include "WPILib.h"
#include "robot/Shooter.h"
#include "robot/Collector.h"
#include "robot/DriveTrain.h"
#include "robot/Conveyor.h"
#include "robot/Auger.h"
#include "robot/ScrewLift.h"

class Components
{
public:
    static Components& getInstance()
    {
        static Components instance;
        return instance;
    }
    FilteredGamePad driver;
    FilteredGamePad shooter;
    DriveTrain driveTrain;
    Shooter shooterMotor;
    Collector collectorMotor;
    Conveyor conveyorMotor;
    Auger augerMotor;
    ScrewLift screwLiftMotor;
    MutablePIDInput* angleInput;
    MutablePIDInput* rotationInput;
    PIDController rotationPID;
    PIDController anglePID;

private:
    //Controler slots
    static const unsigned short DRIVER_PORT = 1;
    static const unsigned short SHOOTER_PORT = 2;
    //Drive train
    static const unsigned short BACK_RIGHT_WHEEL = 1;
    static const unsigned short FRONT_RIGHT_WHEEL = 3;
    static const unsigned short FRONT_LEFT_WHEEL = 4;
    static const unsigned short BACK_LEFT_WHEEL = 2;
    //Conveyor
    static const unsigned short CONVEYOR_MOTOR = 9;
    //Shooter
    static const unsigned short SHOOTER_MOTOR_1 = 2;
    static const unsigned short SHOOTER_MOTOR_2 = 1;
    static const unsigned short SHOOTER_MOTOR_3 = 7;
    static const unsigned short SHOOTER_MOTOR_4 = 7;
    //Collector
    static const unsigned short COLLECTOR_MOTOR_1 = 1;
    static const unsigned short COLLECTOR_MOTOR_2 = 2;
    static const unsigned short COLLECTOR_MOTOR_3 = 4;
    static const unsigned short COLLECTOR_INPUT_1 = 12;
    static const unsigned short COLLECTOR_INPUT_2 = 13;
    //Auger
    static const unsigned short AUGER_MOTOR = 5;
    static const unsigned short AUGER_INPUT1 = 9;
    static const unsigned short AUGER_INPUT2 = 1;
    //Screwlift
    static const unsigned short SCREWLIFT_MOTOR = 3;
    static const unsigned short SCREWLIFT_INPUT = 1;
    static const unsigned short SCREWLIFT_LOWER = 10;
    static const unsigned short SCREWLIFT_UPPER = 11;
    //Rotation PID
    static const unsigned short ROTATION_P = 1;
    static const unsigned short ROTATION_I = 0;
    static const unsigned short ROTATION_D = 0;
    //Angle PID
    static const unsigned short ANGLE_P = 1;
    static const unsigned short ANGLE_I = 0;
    static const unsigned short ANGLE_D = 0;

    Components() :
                driver(DRIVER_PORT),
                shooter(SHOOTER_PORT),
                driveTrain(FRONT_LEFT_WHEEL, BACK_LEFT_WHEEL,
                        FRONT_RIGHT_WHEEL, BACK_RIGHT_WHEEL),
                shooterMotor(SHOOTER_MOTOR_1, SHOOTER_MOTOR_2, SHOOTER_MOTOR_3,
                        SHOOTER_MOTOR_4),
                collectorMotor(COLLECTOR_MOTOR_1, COLLECTOR_MOTOR_2,
                        COLLECTOR_MOTOR_3, COLLECTOR_INPUT_1, COLLECTOR_INPUT_2),
                conveyorMotor(CONVEYOR_MOTOR),
                augerMotor(AUGER_MOTOR, AUGER_INPUT1, AUGER_INPUT2),
                screwLiftMotor(SCREWLIFT_MOTOR, SCREWLIFT_INPUT,
                        SCREWLIFT_LOWER, SCREWLIFT_UPPER),
                angleInput(MutablePIDInput::getPointer()),
                rotationInput(MutablePIDInput::getPointer()),
                rotationPID(ROTATION_P, ROTATION_I, ROTATION_D, rotationInput,
                        NullPIDOutput::getPointer()),
                anglePID(ANGLE_P, ANGLE_I, ANGLE_D, angleInput,
                        NullPIDOutput::getPointer())
    {
        CubicFilter* q = new CubicFilter();
        DeadZoneFilter* d = new DeadZoneFilter();
        driver.addFilter(smartptr<GamePadFilter> (q));
        driver.addFilter(smartptr<GamePadFilter> (d));
        q = new CubicFilter(); //Not sure if this second allocation is necessary
        d = new DeadZoneFilter(); //Not sure if this second allocation is necessary
        shooter.addFilter(smartptr<GamePadFilter> (q));
        shooter.addFilter(smartptr<GamePadFilter> (d));
    }
};
#endif
