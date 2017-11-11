#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    potLeft,        sensorPotentiometer)
#pragma config(Sensor, in2,    potRight,       sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  encRight,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  clawOpen,       sensorTouch)
#pragma config(Sensor, dgtl5,  encLeft,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  liftDown,       sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           driveFrontLeft, tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           mogoleft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           driveBackLeft, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           liftRight,     tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           liftLeft,      tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           driveBackRight, tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           mogoRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          driveFrontRight, tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Mogo Posititions
////////////////////////down   1    2      3    4      5    6     7      8
const int mogoPos[9] = {315, 1660, 1660, 1640, 1820, 1990, 2250, 2600, 2750};
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
/////////////////////
const int armPos[9] = {-75, 365, 365, 360, 350, 340, 350, 330, 310};
#define zeroA 0
#define oneA 0
#define twoA 0
#define threeA 0
#define fourA 0
#define fiveA 0
#define sixA 0
#define sevenA 0
#define eightA 0

#define driverLoad 200

#define potBand 50

#define potDiff 13

#define potR (SensorValue[potRight]-potDiff)
#define potL (SensorValue[potLeft])

#define driveRightEnc -SensorValue[encRight]
#define driveLeftEnc SensorValue[encLeft]
#define getHeading SensorValue[gyro]


bool isMove = true;
bool mogoIsFront = false;
bool breaker = false;
bool loopIsRunning = false;


int mogoPosTarget = mogoPos[0];
int armPosTarget= armPos[0];
int drivePosTarget = 0;
int targetHeading = 0;

int coneCount = 1; // how many cones we jave



bool pressMU = false;
bool pressMD = false;
bool inc = false;
bool dec = false;
bool rest = false;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
void drive(int powerL, int powerR){
motor[driveBackLeft] = motor[driveFrontLeft] = powerL;
motor[driveBackRight] = motor[driveFrontRight] = powerR;
}

void liftMogo (int powerL, int powerR){
motor[mogoleft] = powerL;
motor[mogoRight] = powerR;
}

void liftArm(int powerL, int powerR){
motor[liftLeft] = powerL;
motor[liftRight] = powerR;
}

void powClaw(int power){
motor[claw] = power;
}

int getPot(){
if(potL < 290 && potL > 100)
	return potR;
if(potR < 290 && potR > 100)
	return potL;
return ((potL+potR)/2);
}

int getLiftEnc(){
return (-nMotorEncoder[liftLeft]-nMotorEncoder[liftRight])/2;
}

void clearLiftEnc(){
nMotorEncoder[liftLeft] = 0;
nMotorEncoder[liftRight] = 0;
}

void clearGyro()
{
	getHeading = 0;
}

int getDriveEnc(){
return (SensorValue[encLeft] + SensorValue[encRight])/2;
}

void clearDriveEnc(){
SensorValue[encLeft] = 0;
SensorValue[encRight] = 0;
}

void go2Stack(){

mogoPosTarget = mogoPos[coneCount];

while( mogoPosTarget > getPot()+100 ){}

armPosTarget = armPos[coneCount];

while(-nMotorEncoder[liftLeft] < armPosTarget||-nMotorEncoder[liftRight] < armPosTarget ){}

}

task mogo(){
while(1){
	if(vexRT[Btn7L] ==1 && !(dec==vexRT[Btn7L])){
		coneCount--;
	}
	else if(vexRT[Btn7R] ==1 && !(inc==vexRT[Btn7R])){
		coneCount++;
	}
	else if(coneCount == -1){
		coneCount = 8;
	}
	else if(coneCount == 9){
		coneCount = 1;
	}
	else if(vexRT[Btn7D] ==1 && !(rest==vexRT[Btn7D])){
		coneCount = 1;
	}
	rest = vexRT[Btn7D];
	dec = vexRT[Btn7L];
	inc = vexRT[Btn7R];
	delay(10);
}
}

task clawDrive(){
armPosTarget = 0;
while(1){
	while(!breaker){
		loopIsRunning = false;
		if(vexRT[Btn5U] == 0){
			if(SensorValue[clawOpen] == 0)
				powClaw(-80);
			else
				powClaw(-15);
		}
		else{
			loopIsRunning = true;
			while(!breaker && loopIsRunning){
				powClaw(60);
				wait1Msec(100);
				powClaw(20);
				while(vexRT[Btn5U] == 1 && vexRT[Btn5D] == 0)
				{
				}
					if(vexRT[Btn5D] == 1)
						break;
				go2Stack();
				//while(vexRT[Btn5U] == 0){}

					while(vexRT[Btn5D] == 1)
					{
					}
				while(SensorValue[clawOpen] == 0)
					powClaw(-127);

				powClaw(-10);
				coneCount++;
				if(coneCount > 8 || coneCount <0){
					coneCount=8;
				}
				mogoPosTarget = mogoPos[coneCount];


				wait1Msec(200);
				armPosTarget = 40;
				while(SensorValue[liftDown] == 0 && vexRT[Btn5U] == 0 ){
				}
				wait1Msec(100);
				loopIsRunning = false;
			}
			armPosTarget = armPos[0];
		}
	}
}
}

task driverLoads()
{
armPosTarget = driverLoad;
while(1)
{
	if(vexRT[Btn5U] == 0)
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
		wait1Msec(50);
		powClaw(-90);
		wait1Msec(50);
		armPosTarget = driverLoad;
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

void setMinSpeedPID(
PID controller,
int minSpeed
)
{
controller.minSpeed = minSpeed;
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
int mogoPot
)
{
if(mogoPot > 280)
{
	controller.Error = targetMogoPos - mogoPot;

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
	if(mogoPowerR == -1000000)
		liftMogo(mogoPowerL, mogoPowerL);
	else if(mogoPowerL == -1000000)
		liftMogo(mogoPowerR, mogoPowerR);
	else
		liftMogo(mogoPowerR, mogoPowerL);

	//writeDebugStreamLine("Mogo Target: %d MogoPowerR: %f MogoPowerL: %f getPot: %d getPotLeft: %d getPotRight: %d", mogoPosTarget, mogoPowerR,mogoPowerL, getPot(), potL, potR);
	delay(10);
}
}
////////////////////////////////////////////////MOGO PID////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////LIFT PID ////////////////////////////////////////////////////////
int armPIDCalculation(
int targetArmPos,
PID controller,
int liftEnc)
{

controller.Error = targetArmPos - liftEnc;

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
PID armControllerBegain, armControllerMiddle, armControllerEnd, armControllerDown;
initPID(armControllerBegain, 0.26, 0.0, 0.4);
initPID(armControllerMiddle, 0.39, 0.0, 0.4);
initPID(armControllerEnd, 0.65, 0.0, 0.4);
initPID(armControllerDown, 0.2, 0.0, 0.4);
//setMinSpeedPID(armController, -20);

while(true)
{
	int armPowerL, armPowerR;
	if(armPosTarget < 50)
	{
		 armPowerL = armPIDCalculation(armPosTarget, armControllerDown, -nMotorEncoder[liftLeft]);
		 armPowerR = armPIDCalculation(armPosTarget, armControllerDown, -nMotorEncoder[liftRight]);
	}
	else if(armPosTarget >= 50 && armPosTarget < armPos[3])
	{
		 armPowerL = armPIDCalculation(armPosTarget, armControllerEnd, -nMotorEncoder[liftLeft]);
		 armPowerR = armPIDCalculation(armPosTarget, armControllerEnd, -nMotorEncoder[liftRight]);
	}
	else if(armPosTarget >= 360 && armPosTarget <400)
	{
		 armPowerL = armPIDCalculation(armPosTarget, armControllerMiddle, -nMotorEncoder[liftLeft]);
		 armPowerR = armPIDCalculation(armPosTarget, armControllerMiddle, -nMotorEncoder[liftRight]);
	}
	else if(armPosTarget >=401)
	{
		 armPowerL = armPIDCalculation(armPosTarget, armControllerBegain, -nMotorEncoder[liftLeft]);
		 armPowerR = armPIDCalculation(armPosTarget, armControllerBegain, -nMotorEncoder[liftRight]);
	}
	else
	{
		 armPowerL = armPIDCalculation(armPosTarget, armControllerMiddle, -nMotorEncoder[liftLeft]);
		 armPowerR = armPIDCalculation(armPosTarget, armControllerMiddle, -nMotorEncoder[liftRight]);
	}
	liftArm(-armPowerL, -armPowerR);
	writeDebugStreamLine("liftPid: Target: %d PowerL: %d PowerR: %f leftEnc: %d rightEnc: %d", armPosTarget, armPowerL, armPowerR, -nMotorEncoder[liftLeft] , -nMotorEncoder[liftRight]);
	delay(10);
}
}



//////////////////////////////////////////////////////////LIFT PID////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////Drive PID///////////////////////////////////////////////////////////
int drivePIDCalculation(
int targetDrivePos,
PID controller,
int driveEnc)
{

controller.Error = targetDrivePos - driveEnc;

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

int turnToHeadingCalucation(int targetHeading, PID controller){

	controller.Error = targetHeading - getHeading;

	if(abs(controller.Error) < 100){
		controller.Integral += controller.Error;
	}

	if(controller.Error == 0 || abs(controller.Error) < 10){
		controller.Integral = 0;
	}
	if(abs(controller.Error) < 150){
		controller.Derivitive = controller.prevError - controller.error;
		}else{
		controller.Derivitive = 0;
	}

	controller.prevError = controller.error;
	int returnValue = controller.Error * controller.kP + controller.Integral * controller.kI + controller.Derivitive * controller.kD;

	return returnValue;
}

task drivePID()
{
PID driveController;
initPID(driveController, 0.2, 0.004, 0.03);

PID turnController;
initPID(turnController, 0.9, 0.00, 0.00);

while(true)
{
	int drivePowerL = drivePIDCalculation(drivePosTarget, driveController, driveLeftEnc);
	int drivePowerR = drivePIDCalculation(drivePosTarget, driveController, driveRightEnc);

	int driveTurnPower = turnToHeadingCalucation(targetHeading, turnController);

	drive(drivePowerL- driveTurnPower, drivePowerR+driveTurnPower);
	writeDebugStreamLine("drivePid: Target: %d LeftPower: %f RightPower: %f turnPower: %f leftEnc: %d rightEnc: %d", drivePosTarget, drivePowerL, drivePowerR,driveTurnPower, SensorValue[encLeft], SensorValue[encRight]);
	delay(10);
}
}

task cone()
{
				powClaw(70);
				wait1Msec(100);
				go2Stack();
				wait1Msec(200);
				powClaw(-90);
				wait1Msec(100);
				coneCount++;
				if(coneCount > 8 || coneCount <0){
					coneCount=8;
				}
				mogoPosTarget = mogoPos[coneCount];

				armPosTarget = armPos[0];
				while(SensorValue[liftDown] == 0){
				}
				wait1Msec(100);
}


////////////////////////////////////////////DRIVE PID//////////////////////////////////////////////////////////////////////////



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
/*
wait1Msec(100);
motor[driveBackLeft] = 127;
motor[driveBackRight] = 127;
motor[driveFrontLeft] = 127;
motor[driveFrontRight] = 127;
wait1Msec(300);
motor[driveBackLeft] = 0;
motor[driveBackRight] = 0;
motor[driveFrontLeft] = 0;
motor[driveFrontRight] = 0;
wait1Msec(100);
liftArm(80);
while(SensorValue[liftDown] == 0)
{
}
liftArm(0);
clearLiftEnc();
startTask(mogoPID);


mogoPosTarget = mogoPos[0];
wait1Msec(1100);
motor[driveBackLeft] = 127;
motor[driveBackRight] = 127;
motor[driveFrontLeft] = 127;
motor[driveFrontRight] = 127;
wait1Msec(250);
motor[driveBackLeft] = 0;
motor[driveBackRight] = 0;
motor[driveFrontLeft] = 0;
motor[driveFrontRight] = 0;
wait1Msec(100);

mogoPosTarget = mogoPos[1];
wait1Msec(1000);

motor[driveBackLeft] = -127;
motor[driveBackRight] = -127;
motor[driveFrontLeft] = -127;
motor[driveFrontRight] = -127;
wait1Msec(200);
motor[driveBackLeft] = 0;
motor[driveBackRight] = 0;
motor[driveFrontLeft] = 0;
motor[driveFrontRight] = 0;
wait1Msec(500);

motor[driveBackLeft] = 127;
motor[driveBackRight] = -127;
motor[driveFrontLeft] = 127;
motor[driveFrontRight] = -127;
wait1Msec(200);
motor[driveBackLeft] = 0;
motor[driveBackRight] = 0;
motor[driveFrontLeft] = 0;
motor[driveFrontRight] = 0;
wait1Msec(500);

//mogoPosTarget = mogoPos[0];



wait1Msec(100);
motor[driveBackLeft] = 127;
motor[driveBackRight] = 127;
motor[driveFrontLeft] = 127;
motor[driveFrontRight] = 127;

liftArm(80, 80);
while(SensorValue[liftDown] == 0)
{
}
liftArm(0, 0);
clearLiftEnc();
wait1Msec(900);

//	startTask(mogoPID);


//mogoPosTarget = mogoPos[0];
motor[driveBackLeft] = 0;
motor[driveBackRight] = 0;
motor[driveFrontLeft] = 0;
motor[driveFrontRight] = 0;
wait1Msec(100);



//clearDriveEnc();


//startTask(drivePID);
//drivePosTarget = 1000;
*/


clearDriveEnc();
clearGyro();

powClaw(70);
startTask(drivePID);
startTask(mogoPID);
drivePosTarget = 500;

mogoPosTarget = 0;


liftArm(80, 80);
while(SensorValue[liftDown] == 0)
{
}
liftArm(0, 0);
clearLiftEnc();
wait1Msec(900);

drivePosTarget = 1500;

while(driveRightEnc < 1350 )
{

}
wait1Msec(200);
mogoPosTarget = mogoPos[1];
while(getPot() <mogoPosTarget)
{}
coneCount = 1;


startTask(armPID);
startTask(cone);

drivePosTarget = 100;
while(driveRightEnc > 200)
{

}



targetHeading = 450;

wait1Msec(1100);
clearDriveEnc();
//drivePosTarget = -350;
wait1Msec(1200);
targetHeading = 1550;
wait1Msec(1000);
clearDriveEnc();
//drivePosTarget = 600;
//wait1Msec(250);
mogoPosTarget = mogoPos[0];
wait1Msec(1000);
drivePosTarget = -400;

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
startTask(mogo);
clearLiftEnc();
armPosTarget = armPos[0];
while (true)
{
	if(mogoIsFront)
		drive(vexRT[Ch3], vexRT[Ch2]);
	else
		drive(-vexRT[Ch2], -vexRT[Ch3]);


	//liftArm(15+(127*vexRT[Btn6D])+(-90*vexRT[Btn6U]));

	/*if(vexRT[Btn5D] == 1 && !(press==vexRT[Btn5D]))
	intr++;

	press = vexRT[Btn5D];

	if(intr > 6)
	intr = 0;
	else if(vexRT[Btn8R] == 1)
	intr = 0;*/

	if(vexRT[Btn6U] == 1 && !(pressMU==vexRT[Btn6U]))
	{
		stopTask(mogoPID);
		liftMogo(90, 90);
		mogoPosTarget = getPot();
		isMove = true;
	}
	else if(vexRT[Btn6D] == 1 && !(pressMD==vexRT[Btn6D]))
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

	breaker = vexRT[Btn8R];



	if(SensorValue[liftDown] == 1)
		clearLiftEnc();
	if(SensorValue[Btn8U] == 1)
	{
		//powClaw(100);
	//armPosTarget = 300
	}
	if(SensorValue[Btn8D] == 1)
	{
		powClaw(-130);
		//startTask(armPID);
	}


	/*
	if(SensorValue[Btn8U] == 1)
	{
	stopTask(armPID);
	startTask(driverLoads);
	}
	else if(SensorValue[Btn8D] == 1)
	{
	stopTask(driverLoads);
	startTask(armPID);
	}
	*/



}
}
