#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    powerExpander,  sensorNone)
#pragma config(Sensor, in3,    pot,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,  claw,           sensorDigitalOut)
#pragma config(Sensor, dgtl2,  hangLock,       sensorDigitalOut)
#pragma config(Sensor, dgtl3,  liftBottom,     sensorTouch)
#pragma config(Sensor, dgtl4,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  Piston,         sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           driveRightFront, tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           driveLeftBack, tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port3,           liftRightEnc,  tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port4,           liftLeftIn,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           liftRightTop,  tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           liftLeftTop,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           liftRightIn,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           liftLeftEnc,   tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port9,           driveRightBack, tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port10,          driveLeftFront, tmotorVex393HighSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"


#include "functions.h";
#include "LCD.h";

int autonomousChoice = 0;
bool auton = false;

task doubleCheck()
{
	while(bIfiRobotDisabled && bIfiAutonomousMode)
	{
		delay(1);
	}
	auton = true;
}

void pre_auton()
{
	startTask(doubleCheck);
	bLCDBacklight = true;
	// bStopTasksBetweenModes = true;
	clearLCD();
	while(!auton)
	{
			centerLine(0,autonomousMenu[autonomousChoice]);
			centerLine(1, "Auton | Settings");

			waitForPress();

			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				autonomousChoice = autonChooser();
			}

			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				settings();
			}

			else if(nLCDButtons == centerButton)
			{
				waitForRelease();
				preAutonBattery();
			}

		}
	}


/////////////////////////////////////////////////////////////////////////////////////////
//                                 Autonomous Task
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	//Clear LCD
	bLCDBacklight = false;
	clearLCD();

	centerLine(0,autonomousMenu[autonomousChoice]);
	centerLine(1,"Target>Error");

	switch(autonomousChoice){
	case 0:				break;
	case 1:       break;
	case 2:       break;
	case 3:       break;
	case 4:       break;
	case 5:       break;
	case 6:       break;
	case 7:       break;
	case 8:       break;
	case 9:       break;

	default:
		displayLCDCenteredString(0, "This should");
		displayLCDCenteredString(1, "never happen");
		auton = true;
		wait1Msec(15000);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//                                 User Control Task
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{

	bLCDBacklight = false;
	clearLCD();
	startTask(batteryLCD);

	while (true)
	{




		wait1Msec(10);
	}
}
