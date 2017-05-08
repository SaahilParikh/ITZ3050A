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
	// I Guess this works...
}



void clearLift()
{
	nMotorEncoder[liftLeftEnc] = 0;
	nMotorEncoder[liftRightEnc] = 0;
}

void clearAllEncoder()
{
	clearDrive();
	clearLift();
}

void setLeftDrive(int speed)
{
					motor[driveLeftFront] = speed;
					motor[driveLeftBack] = speed;
}



void setRightDrive(int speed)
{
  motor[driveRightFront] = speed;
	motor[driveRightBack] = speed;
}



void lift(int speed)
{
  #warning "motor[LiftMotors] = speed; has not been set"
}



void drive(int rightSpeed, int leftSpeed)
{
  setRightDrive(rightSpeed);
  setLeftDrive(leftSpeed);
}
