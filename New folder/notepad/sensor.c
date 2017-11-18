#pragma systemFile
//Sensors

#warning "getLeftDriveEncoder"
int getLeftDriveEncoder()
{
	
	return SensorValue[encoderDriveLeft];
	
}

#warning "getRightDriveEncoder"
int getRightDriveEncoder()
{
	
	return SensorValue[encoderDriveRight];
	
}

#warning "getDriveEncoderAvg"
int getDriveEncoderAvg()
{
	
	return (getRightDriveEncoder() + getLeftDriveEncoder())/2;
	
}

#warning "getPot"
int getPot()
{
	
	return SensorValue[pot];	
	
}

#warning "findCoterminalAngle"
int findCoterminalAngle(
	int degrees)
{
	while (degrees < -1800)
	{
		degrees += 3600;
	}

		while (degrees > 1800)
	{
		degrees -= 3600;
	}
}

#warning "getRawHeading"
int getRawHeading()
{
	
	return SensorValue(gyro);
	
}

#warning "getHeading"
int getHeading()
{
	
	return findConterminalAngle(getRawHeading());
	
}




