#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    potLeft,        sensorPotentiometer)
#pragma config(Sensor, in2,    potRight,       sensorPotentiometer)
#pragma config(Sensor, dgtl1,  encRight,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  clawOpen,       sensorTouch)
#pragma config(Sensor, dgtl4,  coneIn,         sensorTouch)
#pragma config(Sensor, dgtl5,  encLeft,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  liftDown,       sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           driveFrontLeft, tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           mogoleft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           driveBackLeft, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           liftRight,     tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           liftLeft,      tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           driveBackRight, tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           mogoRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          driveFrontRight, tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int clawDirection = 1; // 1 is open -1 is close


//Mogo Posititions
const int mogoPos[9] = {350, 1790, 1790, 1890, 2040, 2190, 2590, 2790, 2990}
#define zeroM 350
#define oneM (bottom + 1300),
#define twoM (bottom + 1400)
#define threeM (bottom + 1500)
#define fourM (bottom + 1600)
#define fiveM (bottom + 1800)
#define sixM (bottom + 2300)
#define sevenM (bottom + 2500)
#define eightM (bottom + 2700)}

//Arm Postitions
const int armPos[9] = {0, 400, 400, 400, 380, 380, 350, 350, 350}
#define zeroA 0
#define oneA 0
#define twoA 0
#define threeA 0
#define fourA 0
#define fiveA 0
#define sixA 0
#define sevenA 0
#define eightA 0

#define potBand 50

#define potDiff 17

#define potR (SensorValue[potRight]+potDiff)
#define potL (SensorValue[potLeft])


bool isMove = true;
bool mogoIsFront = false;

int mogoPosTarget = zeroM;
int armPosTarget= 0;

int coneCount = 1; // how many cones we jave


int intr = 0;



bool pressMU = false;
bool pressMD = false;
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
	if(potL < 1000 && potL > 100)
		return potR;
	if(potR < 1000 && potR > 100)
		return potL;
	return ((potL+potR)/2);
}

int getLiftEnc()
{
	return (-nMotorEncoder[liftLeft]-nMotorEncoder[liftRight])/2;
}

void clearLiftEnc()
{
	nMotorEncoder[liftLeft] = 0;
	nMotorEncoder[liftRight] = 0
}

void go2Stack()
{
mogoPosTarget = mogoPos[coneCount];
while( mogoPosTarget > getPot()+100)
{
}
armPosTarget = armPos[coneCount];
while(getLiftEnc() < armPosTarget )
{
}
}

task clawDrive()
{
	armPosTarget = 0;
	while(1)
	{
		if(SensorValue[coneIn] == 0 && vexRT[Btn6U] == 0)
		{
			if(SensorValue[clawOpen] == 0)
				powClaw(-127);
			else
				powClaw(-10);
		}
		else
		{
			powClaw(50);
			wait1Msec(100);
			go2Stack();
			wait1Msec(100);
			powClaw(-90);
			armPosTarget = armPos[0];
			while(SensorValue[liftDown] == 0)
			{
			}
			wait1Msec(100);
			coneCount++;
			mogoPosTarget = mogoPos[coneCount];
			wait1Msec(100);
		}
	}
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

/////////////////////////////////////////////////////////////////////////MOGO PID///////////////////////////////////////////////////

int mogoPIDCalculation(
	int targetMogoPos,
	PID controller,
	int sensorVal
	)
{
	if(SensorVal > 280)
	{



	controller.Error = targetMogoPos - sensorVal;

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
else
	return -1000000
}

task mogoPID()
{
	PID mogoController;
	initPID(mogoController, 0.12, 0.0, 0.17);
	while(true)
	{
		int mogoPowerR = mogoPIDCalculation(mogoPosTarget, mogoController, potR);
		int mogoPowerL = mogoPIDCalculation(mogoPosTarget, mogoController, potL);


	//	if(potL > potR-potBand)
		//	liftMogo(mogoPower, 5*mogoPower);
		//else if(potL < potR+potBand)
		//	liftMogo(5*mogoPower, mogoPower);
	//	else
		if(mogoPowerR == -1000000)
			liftMogo(mogoPowerL, mogoPowerL);
		else if(mogoPowerL == -1000000)
			liftMogo(mogoPowerR, mogoPowerR);
		else
			liftMogo(mogoPowerR, mogoPowerL);

		writeDebugStreamLine("Mogo Target: %d MogoPowerR: %f MogoPowerL: %f getPot: %d getPotLeft: %d getPotRight: %d", mogoPosTarget, mogoPowerR,mogoPowerL, getPot(), potL, potR);
		delay(10);
	}
}
////////////////////////////////////////////////MOGO PID////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////LIFT PID ////////////////////////////////////////////////////////
int armPIDCalculation(
	int targetArmPos,
	PID controller)
{

	controller.Error = targetArmPos - getLiftEnc();

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

task armPID()
{
	PID armController;
	initPID(armController, 0.3, 0.0, 0.05);
	while(true)
	{
		int armPower = armPIDCalculation(armPosTarget, armController);
		liftArm(-armPower);
		writeDebugStreamLine("liftPid: Target: %d Power: %f getEnc: %d leftEnc: %d rightEnc: %d", armPosTarget, armPower, getLiftEnc(), nMotorEncoder[liftLeft] , nMotorEncoder[liftRight]);
		delay(10);
	}
}
///////////////////////////////////////////////////////LIFT PID///////////////////////////////////////////////////////////////



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
startTask(clawDrive);
startTask(armPID);
  while (true)
  {
  	if(mogoIsFront)
  	 drive(vexRT[Ch3], vexRT[Ch2]);
		else
		 drive(-vexRT[Ch2], -vexRT[Ch3]);

		 if(vexRT[Btn7L] == 1)
		 	mogoIsFront = !mogoIsFront;

	//	liftArm(15+(127*vexRT[Btn6D])+(-90*vexRT[Btn6U]));

  	/*if(vexRT[Btn5D] == 1 && !(press==vexRT[Btn5D]))
  		intr++;

  	press = vexRT[Btn5D];

  	if(intr > 6)
  		intr = 0;
		else if(vexRT[Btn8R] == 1)
			intr = 0;*/

			if(vexRT[Btn5U] == 1 && !(pressMU==vexRT[Btn5U]))
			{
				stopTask(mogoPID);
				liftMogo(90, 90);
				mogoPosTarget = getPot();
				isMove = true;
			}
			else if(vexRT[Btn5D] == 1 && !(pressMD==vexRT[Btn5D]))
			{
				stopTask(mogoPID);
				liftMogo(-90, -90);
				mogoPosTarget = getPot();
				isMove = true;
			}
			else
			{
				if(isMove)
				{
					startTask(mogoPID);
					isMove = false;
				}
			}

		/*
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
*/
	if(SensorValue[liftDown] == 1)
		clearLiftEnc();


  	/*if(vexRT[Btn5U] ==1 && !(clawPress==vexRT[Btn5U]))
  	{
  		if(clawDirection ==1)
  			clawDirection = -1;
  		else
  			clawDirection = 1;
  	}
 		clawPress = vexRT[Btn5U];
*/



  }
}
