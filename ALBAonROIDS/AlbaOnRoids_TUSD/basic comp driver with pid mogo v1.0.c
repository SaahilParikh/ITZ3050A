#pragma config(Sensor, in1,    potLeft,           sensorPotentiometer)
#pragma config(Sensor, in2,    potRight,           sensorPotentiometer)
#pragma config(Motor,  port1,           driveFrontLeft, tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           mogoleft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           driveBackLeft, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           liftRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftLeft,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           driveBackRight, tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           mogoRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          driveFrontRight, tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int clawDirection = 1; // 1 is open -1 is close

#define bottom 1550
#define first bottom+1300
#define third first+200
#define five third+300
#define six five+500
#define seven six+200
#define eight seven+200

#define potBand 50

#define potDiff 1295

#define sensorValue[potRight] sensorValue[potRight]+potDiff

bool mogoIsFront = true;

int mogoPosTarget = bottom;
int intr = 0;



bool press = false;
bool clawPress = false;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
void drive(int powerL, int powerR)
{
	motor[driveBackLeft] = motor[driveFrontLeft] = powerL;
	motor[driveBackRight] = motor[driveFrontRight] = powerR;
}

void liftMogo (int powerL, int powerR)
{
	motor[mogoleft] = powerL;
	motor[mogoRight] = powerR;
}

void liftArm(int power)
{
	motor[liftLeft] = motor[liftRight] = power;
}

void powClaw(int power)
{
	motor[claw] = power;
}

int getPot()
{
	if(SensorValue[potLeft] < 251 && SensorValue[potLeft] > 245)
		return SensorValue[potRight];
	if(SensorValue[potRight] < 251 && SensorValue[potRight] > 245)
		return SensorValue[potLeft];
	return ((SensorValue[potLeft]+SensorValue[potRight])/2);
}

typedef struct{

	float kP, kI, kD;

	int Error, Integral, Derivitive, prevError, integralLimit;

	int maxIntegral, maxOutput, minSpeed;

} PID;

void resetPID(
	PID controller)
{

	controller.Error = 0;
	controller.Integral = 0;
	controller.Derivitive = 0;
	controller.prevError = 0;

}

void initPID(
	PID controller,
	float kP,
	float kI,
	float kD)
{

	controller.kP = kP;
	controller.kI = kI;
	controller.kD = kD;

	controller.maxIntegral = 0;
	controller.maxOutput = 0;
	controller.minSpeed = 0;
	controller.integralLimit = 100;

	resetPID(controller);

}

int mogoPIDCalculation(
	int targetArmPos,
	PID controller)
{

	controller.Error = targetArmPos - getPot();

	if(controller.integralLimit > abs(controller.Error) &&
		controller.integralLimit != 0 &&
		controller.Integral < 10000)
		controller.Integral += controller.Error;
	else
		controller.Integral = 0;


	if (controller.maxIntegral != 0)
	{
		if (controller.Integral > controller.maxIntegral)
			controller.Integral = controller.maxIntegral;

		if (controller.Integral < -controller.maxIntegral)
			controller.Integral = -controller.maxIntegral;
	}

	controller.Derivitive = controller.Error - controller.prevError;
	controller.prevError = controller.Error;

	int returnValue = ((int)abs((controller.Error*controller.kP +
							controller.Integral*controller.kI -
							controller.Derivitive*controller.kD)) > controller.minSpeed)
										?
										(int)(controller.Error*controller.kP +
							controller.Integral*controller.kI -
							controller.Derivitive*controller.kD)
										:
										controller.minSpeed*sgn((int)(controller.Error*controller.kP + controller.Integral*controller.kI - controller.Derivitive*controller.kD));

	if (controller.maxOutput != 0)
	{
    if (returnValue > controller.maxOutput)
      returnValue = controller.maxOutput;

    if (returnValue < -controller.maxOutput)
      returnValue = -controller.maxOutput;
	}
	return returnValue;
}

task mogoPID()
{
	PID mogoController;
	initPID(mogoController, 0.09, 0.0, 0.05);
	while(true)
	{
		int mogoPower = mogoPIDCalculation(mogoPosTarget, mogoController);

		if(SensorValue[potLeft] > SensorValue[potRight]-potBand)
			liftMogo(mogoPower/2, mogoPower);
		else if(SensorValue[potLeft] < SensorValue[potRight]+potBand)
			liftMogo(mogoPower, mogoPower/2);
		else
			liftMogo(mogoPower, mogoPower);

		writeDebugStreamLine("%d %f %d %d %d", mogoPosTarget, mogoPower, getPot(), SensorValue[potLeft], SensorValue[potRight]);
		delay(10);
	}
}

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  // User control code here, inside the loop

startTask(mogoPID);

  while (true)
  {
  	if(mogoIsFront)
  	 drive(vexRT[Ch3], vexRT[Ch2]);
		else
		 drive(-vexRT[Ch2], -vexRT[Ch3]);

		 if(vexRT[Btn7L] == 1)
		 	mogoIsFront = !mogoIsFront;

		liftArm(15+(127*vexRT[Btn6D])+(-127*vexRT[Btn6U]));

  	if(vexRT[Btn5U] == 1 && !(press==vexRT[Btn5U]))
  		intr++;

  	press = vexRT[Btn5U];

  	if(intr > 6)
  		intr = 0;

  	if (intr == 0)
  		mogoPosTarget = bottom;
  	else if (intr == 1)
  		mogoPosTarget = first;
  	else if (intr == 2)
  		mogoPosTarget = third;
  	else if (intr == 3)
  		mogoPosTarget = five;
  	else if (intr == 4)
  		mogoPosTarget = six;
  	else if (intr == 5)
  		mogoPosTarget = seven;
  	else if (intr == 6)
  		mogoPosTarget = eight;

  	if(vexRT[Btn5D] ==1 && !(clawPress==vexRT[Btn5D]))
  	{
  		if(clawDirection ==1)
  			clawDirection = -1;
  		else
  			clawDirection = 1;
  	}
 		clawPress = vexRT[Btn5D];

  	powClaw(clawDirection*35);


  }
}
