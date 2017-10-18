#pragma systemFile
// PID

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

void liftPIDCalculation(
	int targetArmPos,
	PID controller)
{


	controller.Error = targetArmPos - getpot();

	if(controller.integralLimit > abs(controller.Error) &&
		controller.integralLimit != 0 &&
		controller.Integral < 10000)
		controller.Integral += controller.Error;
	else
		controller.Integral = 0;


	if (pid.maxIntegral != 0)
	{
		if (pid.Integral > pid.maxIntegral)
			pid.Integral = pid.maxIntegral;

		if (pid.Integral < -pid.maxIntegral)
			pid.Integral = -pid.maxIntegral;
	}

	controller.Derivitive = controller.Error - controller.prevError;
	controller.prevError = controller.Error;

	int returnValue = ((int)abs((controller.Error*controller.kP +
							controller.Integral*controller.kI +
							controller.Derivitive*controller.kD)) > controller.minSpeed)
										?
										(int)(error*kp+integral*ki+der*kd)
										:
										minSpeed*sgn((int)(error*kp+integral*ki+der*kd));

	if (pid.maxOutput != 0)
	{
    if (returnValue > pid.maxOutput)
      returnValue = pid.maxOutput;

    if (returnValue < -pid.maxOutput)
      returnValue = -pid.maxOutput;
	}

	return returnValue;


}

int armPosTarget = BOTTOM;

task liftPID()
{
	PID liftController;
	initPID(&liftController, 0.3, 0, 0);

	while(true)
	{

		int liftPower = liftPIDCalculation(armPosTarget, &liftController);
		lift(liftPower);
		writeDebugStreamLine("%d %f %d", armPosTarget, liftPower, motor[liftL1]);
		delay(10);

	}
}
