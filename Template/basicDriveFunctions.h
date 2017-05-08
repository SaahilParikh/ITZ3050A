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

void drive(int rightSpeed, int leftSpeed)
{
	setRightDrive(rightSpeed);
	setLeftDrive(leftSpeed);
}
