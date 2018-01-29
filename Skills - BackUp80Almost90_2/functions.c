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
return (SensorValue[encLeft] + SensorValue[encRight])/2;
}

void clearDriveEnc(){
SensorValue[encLeft] = 0;
SensorValue[encRight] = 0;
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
initPID(driveController, 0.1, 0.007, 0.03);

PID turnController;
initPID(turnController, 0.25, 0.00, 0.00);

while(true)
{
	int drivePowerL = drivePIDCalculation(drivePosTarget, driveController, (getDriveEnc()/2);


	int driveTurnPower = turnToHeadingCalucation(targetHeading, turnController);

	drive(drivePower- driveTurnPower, drivePower+driveTurnPower);

	writeDebugStreamLine("drivePid: Target: %d DrivePower: %f turnPower: %f leftEnc: %d rightEnc: %d", drivePosTarget, drivePower ,driveTurnPower, -SensorValue[encLeft], SensorValue[encRight]);

	delay(10);
}
}
gjhglgjhgk
void setDrive(int target, int addedTime = 0)
{
		time1[T1] = 0;

		drivePosTarget = target;
		int this = getDriveEnc();
		int statCount = 0;

		while((time1[T1]-addedTime) < (abs(wheelDiameter*(target-this)*timeConstDrive)) || statCount > 2000)
		{
			if(	abs(getDriveEnc()-target) < 25 )
		{
			statCount++;
		}
		 else
		{
			statCount = 0;
		}

		}
}

void setTurn(int target, int addedTime = 0)
{
		time1[T2] = 0;

		targetHeading = target;
		int this = getHeading;
		int statCount = 0;

		clearDriveEnc();
		drivePosTarget = 0;

		while((time1[T2]+addedTime) < (abs(wheelDiameter*(target-this)*timeConstDrive)) || statCount > 2000)
		{

		clearDriveEnc();

		if(	abs(getHeading-target) < 5 )
		{
			statCount++;
		}
		 else
		{
			statCount = 0;
		}

		}

}


void mogoDriveUp(int addedTime = 0)
{
		time1[T3] = 0;
		while((time1[T3]) < addedTime || SensorValue[mogoUp] != 1)
		{
				powMogo(127);
		}
		powMogo(0);
}

void mogoDriveDown(int addedTime = 0)
{
		time1[T3] = 0;
		while((time1[T3]) < addedTime || SensorValue[mogoDown] != 1)
		{
				powMogo(-127);
		}
		powMogo(0);
}
