#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  encRight,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encLeft,        sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  mogoDown,       sensorTouch)
#pragma config(Sensor, dgtl6,  mogoUp,         sensorTouch)
#pragma config(Motor,  port1,           driveBBLeft,   tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           driveBFRight,  tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           driveFLeft,    tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           mogoLeft,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           mogoRight,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           driveFRight,   tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           driveBFLeft,   tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          driveBBRight,  tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"


#include "function.h";

//float ticsPerDegree = (37870/36000);

int autonomousChoice = 0;
bool auton = false;

task doubleCheck()
{
	while(bIfiRobotDisabled && !bIfiAutonomousMode)
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

		//	waitForPress();

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
	case 0:	skills();			break;
	case 1:	     break;
	case 2:       break;
	case 3:       break;
	case 4:      	  break;
	case 5:          break;
	case 6:       break;
	case 7:       break;
	case 8:       break;
	case 9:       break;
	case 10:       break;
	case 11:       break;

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

			drive((vexRT[Ch3]-(vexRT[Btn5U]*driveSlowSpeed)), (vexRT[Ch2]-(vexRT[Btn5U]*driveSlowSpeed)));
			powMogo((vexRT[Btn6U] - vexRT[Btn6D])*127+vexRT[Btn5D]*6);


		wait1Msec(10);
	}
}
