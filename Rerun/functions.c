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

setLeftDrive(int speed)
{
#warning "motor[leftSide] = speed; has not been set"
}

setRightDrive(int speed)
{
#warning "motor[RightSide] = speed; has not been set"
}

setLiftSpeed(int speed)
{
#warning "motor[LiftMotors] = speed; has not been set"
}

setDrive(int rightSpeed, int leftSpeed)
{
	setRightDrive(rightSpeed);
	setLeftDrive(leftSpeed);
}

setLiftSpeed(int speed)
{
#warning "motor[LiftMotors] = speed; has not been set"
}
