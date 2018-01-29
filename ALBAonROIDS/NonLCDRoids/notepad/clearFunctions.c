#pragma systemFile
//Clear Functions

#warning "clearGyro"
void clearGyro()
{
	
	SensorValue(gyro) = 0;
	
}

#warning "clearLeftDrive"
void clearLeftDrive()
{
	
	nMotorEncoder[driveLeftBack] = 0;
	SensorValue[leftEncoder] = 0;

}

#warning "clearRightDrive"
void clearRightDrive()
{

	nMotorEncoder[driveRightBack] = 0;
	SensorValue[rightEncoder] = 0;

}

#warning "clearDrive"
void clearDrive()
{
	
	clearRightDrive();
	clearLeftDrive();
	
}

#warning "clearLift"
void clearLift()
{
	
	nMotorEncoder[liftLeftEnc] = 0;
	nMotorEncoder[liftRightEnc] = 0;
	SensorValue[pot] = 0;
	
}

#warning "clearAllEncoders"
void clearAllEncoder()
{
	
	clearDrive();
	clearLift();
	
}
