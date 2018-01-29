#pragma systemFile

//Functions
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
armPosTarget = stationaryArmPos;

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
	else if(coneCount == 1){
		coneCount = 1;
	}
	else if(coneCount == 9){
		coneCount = 8;
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
				powClaw(-127);
			else
				powClaw(-15);
			if(vexRT[Btn5D] ==1 && vexRT[Btn6D] ==1)
			{
				powClaw(127);
				wait1Msec(100);
				powClaw(30);
				while(vexRT[Btn5D] == 1)
				{
				}
				armPosTarget = stationaryArmPos;
				while(vexRT[Btn5D] == 0)
				{
				}
				while(vexRT[Btn5D] == 1)
				{
				}
				powClaw(-127);
				wait1Msec(100);
				powClaw(-10);
				while(vexRT[Btn5D] == 0)
				{
				}
				while(vexRT[Btn5D] == 1)
				{
				}
				armPosTarget = armPos[0];

			}
		}
		else{
			loopIsRunning = true;
			while(!breaker && loopIsRunning){
				powClaw(127);
				wait1Msec(100);
				powClaw(30);
				while(vexRT[Btn5U] == 1 && vexRT[Btn5D] == 0)
				{
				}
				if(vexRT[Btn5D] == 1)
					break;
				go2Stack();
				while(vexRT[Btn5D] == 1)	{}
				while(SensorValue[clawOpen] == 0)
					powClaw(-127);
				powClaw(-10);
				coneCount++;
				if(coneCount > 8 || coneCount <0){
					coneCount=8;
				}
				mogoPosTarget = mogoPos[coneCount];
				wait1Msec(200);
				armPosTarget = bottom+90;
				while(SensorValue[liftDown] == 0 && vexRT[Btn5D] == 0 && armPosTarget <200) {}
				wait1Msec(100);
				loopIsRunning = false;
			}
			armPosTarget = bottom;
		}
	}
}
}

task driverLoads()
{
armPosTarget = driverLoadArmPos;
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
		armPosTarget = driverLoadArmPos;
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
controller.maxOutput = 127;
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
initPID(mogoController, 0.17, 0.0, 0.17);
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
PID armControllerBegain, armControllerMiddle, armControllerEnd, armControllerDown, armControllerFine, armControllerDL, armControllerTopArm;
initPID(armControllerBegain, 0.26, 0.0, 0.4);
initPID(armControllerMiddle, 0.75, 0.0, 0.4);
initPID(armControllerEnd, 0.65, 0.0, 0.4);
initPID(armControllerDown, 0.2, 0.0, 0.4);
initPID(armControllerTopArm, 0.9, 0.0, 0.3);
initPID(armControllerFine, 1.0, 0.01, 0.4);
initPID(armControllerDL, 0.2, 0.05, 0.4);
//setMinSpeedPID(armController, -20);

while(true)
{
	int armPowerL, armPowerR;
	if(armPosTarget < 50)
	{
		armPowerL = (armPIDCalculation(armPosTarget, armControllerDown, -nMotorEncoder[liftLeft]));
		armPowerR = (armPIDCalculation(armPosTarget, armControllerDown, -nMotorEncoder[liftRight]));
	}
	if(armPosTarget >= 50 && armPosTarget < driverLoadArmPos)
	{
		armPowerL = armPIDCalculation(armPosTarget, armControllerDL, -nMotorEncoder[liftLeft]);
		armPowerR = armPIDCalculation(armPosTarget, armControllerDL, -nMotorEncoder[liftRight]);
	}
	else if(armPosTarget >= driverLoadArmPos+1 && armPosTarget < 300)
	{
		armPowerL = armPIDCalculation(armPosTarget, armControllerFine, -nMotorEncoder[liftLeft]);
		armPowerR = armPIDCalculation(armPosTarget, armControllerFine, -nMotorEncoder[liftRight]);
	}
	else if(armPosTarget == 300)
	{
		armPowerL = armPIDCalculation(armPosTarget, armControllerTopArm, -nMotorEncoder[liftLeft]);
		armPowerR = armPIDCalculation(armPosTarget, armControllerTopArm, -nMotorEncoder[liftRight]);
	}
	else if(armPosTarget >300 && armPosTarget < 360)
	{
		armPowerL = armPIDCalculation(armPosTarget, armControllerEnd, -nMotorEncoder[liftLeft]);
		armPowerR = armPIDCalculation(armPosTarget, armControllerEnd, -nMotorEncoder[liftRight]);
	}
	else if(armPosTarget >= 360 && armPosTarget <450)
	{
		armPowerL = armPIDCalculation(armPosTarget, armControllerMiddle, -nMotorEncoder[liftLeft]);
		armPowerR = armPIDCalculation(armPosTarget, armControllerMiddle, -nMotorEncoder[liftRight]);
	}
	else if(armPosTarget >=450)
	{
		armPowerL = armPIDCalculation(armPosTarget, armControllerBegain, -nMotorEncoder[liftLeft]);
		armPowerR = armPIDCalculation(armPosTarget, armControllerBegain, -nMotorEncoder[liftRight]);
	}
	else
	{
		armPowerL = armPIDCalculation(armPosTarget, armControllerMiddle, -nMotorEncoder[liftLeft]);
		armPowerR = armPIDCalculation(armPosTarget, armControllerMiddle, -nMotorEncoder[liftRight]);
	}

	if(armPosTarget == armPos[0])
		liftArm(-armPowerL+35, -armPowerR+35);
	else
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
initPID(driveController, 0.4, 0.007, 0.03);

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

powClaw(-127);
while(SensorValue[clawOpen] == 0)
{}

powClaw(-10);
coneCount++;
if(coneCount > 8 || coneCount <0){
	coneCount=8;
}
mogoPosTarget = mogoPos[coneCount];

while(coneCount == 3 && !doneWithCone)
{

}

wait1Msec(300);
armPosTarget = armPos[0];
while(SensorValue[liftDown] == 0){
}
wait1Msec(100);
}

task coneStay()
{
powClaw(70);
wait1Msec(100);
go2Stack();

powClaw(-127);
while(SensorValue[clawOpen] == 0)
{}

powClaw(-10);
coneCount++;
if(coneCount > 8 || coneCount <0){
	coneCount=8;
}
mogoPosTarget = mogoPos[coneCount];

while(coneCount == 3 && !doneWithCone)
{

}

wait1Msec(300);
armPosTarget = stationaryArmPos;

wait1Msec(100);
}


void setDrive(int target, int addedTime)
{
		time1[T1] = 0;

		while((time1[T1]+addedTime) < (wheelDiameter*target*timeConstDrive))
		{
			drivePosTarget = target;
		}
}

void setLift(int target, int addedTime)
{
		time1[T2] = 0;

		while((time1[T2]+addedTime) < (target*timeConstLift))
		{
			armPosTarget = target;
		}
}

void setMogo(int target, int addedTime)
{
		time1[T3] = 0;

		while((time1[T3]+addedTime) < (target*timeConstMogo))
		{
			mogoPosTarget = target;
		}
}
