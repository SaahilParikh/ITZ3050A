void clearGyro()
{
//	SensorValue(gyro) = 0;
}

void clearDrive()
{
//	nMotorEncoder[driveLeftBack] = 0;
//	nMotorEncoder[driveRightBack] = 0;
	// I Guess this works...
}

void clearLift()
{
//	nMotorEncoder[liftLeftEnc] = 0;
//	nMotorEncoder[liftRightEnc] = 0;
}

void clearAllEncoder()
{
	clearDrive();
	clearLift();
}

int getDriveEncoder()
{
	return (SensorValue[Drive1] + SensorValue[Drive2])/2;
}

int getLiftEncoder()
{
	return SensorValue[Lift1];
}

int getGyro()
{
	return SensorValue[Gyro];
}

void setLeftDrive(int speed)
{
#warning "motor[leftSide] = speed; has not been set"
}

void setRightDrive(int speed)
{
#warning "motor[RightSide] = speed; has not been set"
}

void setLiftSpeed(int speed)
{
#warning "motor[LiftMotors] = speed; has not been set"
}

void setDrive(int rightSpeed, int leftSpeed)
{
	setRightDrive(rightSpeed);
	setLeftDrive(leftSpeed);
}
