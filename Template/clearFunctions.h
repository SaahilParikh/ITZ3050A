#pragma systemFile
//Functions

void clearGyro()
{
	SensorValue(gyro) = 0;
}

void clearDrive()
{
	nMotorEncoder[driveLeftBack] = 0;
	nMotorEncoder[driveRightBack] = 0;
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
}

void clearLift()
{
	nMotorEncoder[liftLeftEnc] = 0;
	nMotorEncoder[liftRightEnc] = 0;
	SensorValue[pot] = 0;
}

void clearAllEncoder()
{
	clearDrive();
	clearLift();
}
