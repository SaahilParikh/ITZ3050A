#pragma systemFile

//Functions
void powClaw(int power){
motor[claw] = power;
}

void powMogo(int power){
	motor[mogoLeft] = power;
	motor[mogoRight] = power;
}

void clearGyro()
{
getHeading = 0;
}

int getDriveEnc(){
return (driveRightEnc + driveLeftEnc)/2;
}

int getGyro(){
return getHeading;
}

void clearDriveEnc(){
SensorValue[encLeft] = 0;
SensorValue[encRight] = 0;
}

int limit(int number, int max)
{

	if(abs(max)<abs(number))
		return sgn(number)*abs(max);
	else
		return number;
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
controller.maxOutput = 127;
controller.minSpeed = 0;
controller.integralLimit = 100;

resetPID(controller);

}

//////////////////////////////////////////////////////////Drive PID///////////////////////////////////////////////////////////
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

controller.Error = targetHeading - (getHeading)*(ticsPerDegree);

if(abs(controller.Error) < 100){
	controller.Integral += controller.Error;
}

if(controller.Error == 0 || abs(controller.Error) < 10){
	controller.Integral = 0;
}
//if(abs(controller.Error) < 150){
	controller.Derivitive = controller.prevError - controller.error;
	//}else{
	//controller.Derivitive = 0;
//}

controller.prevError = controller.error;
int returnValue = controller.Error * controller.kP + controller.Integral * controller.kI - controller.Derivitive * controller.kD;

return returnValue;
}
/*
task drivePID()
{
PID driveController;
initPID(driveController, 0.170, 0.005, 0.9);

PID turnController;
initPID(turnController, 0.34, 0.00, 0.1);

while(true)
{
	int drivePower = drivePIDCalculation(drivePosTarget, driveController, getDriveEnc());


	int driveTurnPower = turnToHeadingCalucation(targetHeading, turnController);


	if(	abs(targetHeading-getHeading) < 100 )
		drive(drivePower- driveTurnPower, drivePower+driveTurnPower);
	else
		drive(-driveTurnPower, driveTurnPower);
	//writeDebugStreamLine("drivePid: Target: %d DrivePower: %f turnPower: %f leftEnc: %d rightEnc: %d", drivePosTarget, drivePower ,driveTurnPower, -SensorValue[encLeft], SensorValue[encRight]);

	delay(10);
}
}*/

void driveKeepHeading(int encoderCount, int gyroHeading = targetHeading, int addedTime = 0, int stationaryCount = driveStraightStationaryCountThresh, bool display = false)
{

	PID driveController;
	initPID(driveController, 0.75, 0.000, 0.55);

	PID turnController;
	initPID(turnController, 0.5, 0.00, 0.1);

	int statCount = 0;
	time1[T1] = 0;
	int estimatedTime = abs(driveTimeConst*(encoderCount-getDriveEnc());

	int driveTurnPower = 0;
	int drivePowerR = 0;
	int drivePowerL = 0;

	while( ((time1[T1]-addedTime) < estimatedTime) && (statCount < stationaryCount))
	{

		drivePowerR = limit(drivePIDCalculation(encoderCount, driveController, driveRightEnc), 127);
		drivePowerL = limit(drivePIDCalculation(encoderCount, driveController, driveLeftEnc), 127);

		if(abs(targetHeading-getHeading)>10)
			driveTurnPower = turnToHeadingCalucation(gyroHeading, turnController);
		else
			driveTurnPower = 0;

		drive(drivePowerL - driveTurnPower, drivePowerR + driveTurnPower);

		if(display)
			writeDebugStreamLine("%d,,,, %d,      ,%d, target: %d, GetDriveend(): %f, driveTimeConst, %f ,   abs(getDriveEnc()-encoderCount): %d", driveTurnPower, statCount , (-(time1[T1]-addedTime) + estimatedTime), encoderCount, getDriveEnc(), driveTimeConst, (abs(encoderCount-getDriveEnc())) );

		if(	abs(targetHeading-getHeading) < 5 && (abs(drivePosTarget-getDriveEnc()) < 30 )
		{
			statCount++;
		}
		else
		{
			statCount = 0;
		}

		delay(5);
	}
	drive(0,0);
}

void driveTurn (int targetHeadings, int addedTime = 0, float kPTurn = 0.30, int stationaryCount = turnStraightStationaryCountThresh, bool display = false)
{

		targetHeading = targetHeadings;

		PID turnController;
		//initPID(turnController, kPTurn, 0.0001, 11.8);
		initPID(turnController, kPTurn, 0.0000, 3.7);
		time1[T2] = 0;

		int statCount = 0;

		int estimatedTime = ( (turnTimeConst) * abs((targetHeadings-getHeading)) );

		while((time1[T2]-addedTime) < (estimatedTime) && statCount < stationaryCount)
		{

			int driveTurnPower = turnToHeadingCalucation(targetHeadings, turnController);

			/*if(abs(driveTurnPower) > 50)
			{
				driveTurnPower = sgn(driveTurnPower)*50;
			}*/

			drive( -driveTurnPower ,  driveTurnPower );
			if(display)
				writeDebugStreamLine("statCount: %d, estimatedTime: %d, (time1[T2]-addedTime): %d, getHeading: %d, targetHeading: %d", statCount, estimatedTime, (time1[T2]-addedTime), getHeading, targetHeadings);

			if(	abs(targetHeading - (getHeading)*(ticsPerDegree)) < 17 )
			{
				statCount++;

			}
		 	else
			{
				statCount = 0;
			}
			delay(5);
		}
		drive(0,0);
}




void driveSmoothTurn ( int medianSpeed,  int targetHeadings, int addedTime = 0 ,int stationaryCount = 200, bool display = false)
{
	PID turnController;
	initPID(turnController, 0.1, 0.00, 1000);

	targetHeading = targetHeadings

	time1[T3] = 0;

	int estimatedTime = abs(turnTimeConst*(targetHeadings-getHeading));
	int statCount = 0;
	int driveTurnPower = 1;


	while( (time1[T3]-addedTime) < estimatedTime && statCount < stationaryCount)
	{
		driveTurnPower = turnToHeadingCalucation(targetHeadings, turnController);
		drive(medianSpeed + driveTurnPower*sgn(medianSpeed), medianSpeed - driveTurnPower*sgn(medianSpeed));

		if(display)
			writeDebugStreamLine("statCount: %d, estimatedTime: %d, (time1[T2]-addedTime): %d, getHeading: %d, targetHeading: %d", statCount, estimatedTime, (time1[T2]-addedTime), getHeading, targetHeadings);


		if(	abs(targetHeadings-getHeading) < 20 )
		{
			statCount++;
		}
		else
		{
			statCount = 0;
		}

	}
	drive(0,0);
}

void mogoDriveUp(int addedTime = 0)
{
		time1[T4] = 0;
		while((time1[T4]) < addedTime || SensorValue[mogoUp] != 1)
		{
				powMogo(127);
		}
		powMogo(20);
}



void mogoDriveDown(int addedTime = 0)
{
		time1[T4] = 0;
		while((time1[T4]) < addedTime || SensorValue[mogoDown] != 1)
		{
				powMogo(-127);
		}
		powMogo(-10);
}

task mogoUpTask(){
		while(SensorValue[mogoUp] != 1)
		{
				powMogo(127);
		}
		powMogo(20);
}

task mogoDownTask(){

		while(SensorValue[mogoDown] != 1)
		{
				powMogo(-127);
		}
		powMogo(-10);

}

task coneDrop
{
	wait1Msec(1000);
	powClaw(-90)
	wait1Msec(1000);
	powClaw(0);

}
