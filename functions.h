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

void drivePid(int Encoder, int minSpeed = 20)
{
	double kP = 0.6;
	double kI = 0.001;
	double kD = 0.8;

	int integral;
	int der;
	int error;
	int prevErr;

	int speed;
	int bias = 3;
	int threshold = 3; // TUNE THIS VALUE - 2/13/2017

	#warning "Tune PID  - 2/13/2017";

	while(nMotorEncoder[driveRightBack] < Encoder && nMotorEncoder[driveLeftBack] < Encoder)
	{
		error = ((abs(Encoder) - abs(nMotorEncoder[driveRightBack]))/2  +
						 (abs(Encoder) - abs(nMotorEncoder[driveLeftBack]))/2   ) ; //error is both encoder values

		if(error > 100)
		{
			integral = 0;
		}
		else
		{
			integral += error;
		}

		der = prevErr - error;
		prevErr = error;

		speed = ((int)(error*kp + integral*ki + der*kd) > minSpeed)?(int)(error*kp+integral*ki+der*kd):minSpeed;

		if(Encoder > 0)
		{
			if(abs(nMotorEncoder[driveRightBack]) < abs(nMotorEncoder[driveLeftBack])-threshold) // If the left side has more encoder ticks than the right
				{																																			// Make the right side faster, Has bias
					motor[driveRightFront] = speed;
					motor[driveRightBack] = speed;
					motor[driveLeftFront] = speed/bias;
					motor[driveLeftBack] = speed/bias;
				}
			else if(abs(nMotorEncoder[driveRightBack])-threshold > abs(nMotorEncoder[driveLeftBack]))	// Other  way around from top comment
				{
					motor[driveRightFront] = speed/bias;
					motor[driveRightBack] = speed/bias;
					motor[driveLeftFront] = speed;
					motor[driveLeftBack] = speed;
				}
			else
				{
					motor[driveRightFront] = speed; 																				// Go normal speed value
					motor[driveRightBack] = speed;
					motor[driveLeftFront] = speed;
					motor[driveLeftBack] = speed;
				}
		}
	else
	{
		if(abs(nMotorEncoder[driveRightBack])-threshold < abs(nMotorEncoder[driveLeftBack])) // If the left side has more encoder ticks than the right
		{																																			// Make the right side faster, Has bias
			motor[driveRightFront] = speed;
			motor[driveRightBack] = speed;
			motor[driveLeftFront] = speed/bias;
			motor[driveLeftBack] = speed/bias;
		}
		else if(abs(nMotorEncoder[driveRightBack]) >abs( nMotorEncoder[driveLeftBack])-threshold)	// Other  way around from top comment
		{
			motor[driveRightFront] = speed/bias;
			motor[driveRightBack] = speed/bias;
			motor[driveLeftFront] = speed;
			motor[driveLeftBack] = speed;
		}
		else
		{
			motor[driveRightFront] = speed; 																				// Go normal speed value
			motor[driveRightBack] = speed;
			motor[driveLeftFront] = speed;
			motor[driveLeftBack] = speed;
		}
	}

		}
}

void driveBackwardPid(int Encoder, int minSpeed = -90)
{

	double kP = 0.6;
	double kI = 0.001;
	double kD = 0.8;

	int integral;
	int der;
	int error;
	int prevErr;

	int speed;
	int bias = 3;
	int threshold = 2; // TUNE THIS VALUE - 2/13/2017

	#warning "Tune Autocorrect Threshhold - 2/13/2017";

	while(nMotorEncoder[driveRightBack] > -Encoder && nMotorEncoder[driveLeftBack] > -Encoder)
	{
		error = ((-Encoder - -nMotorEncoder[driveRightBack])+(-Encoder - nMotorEncoder[driveLeftBack]))/2 ; //error is both encoder values

		if(error < -100)
		{
			integral = 0;
		}
		else
		{
			integral += error;
		}

		der = prevErr - error;
		prevErr = error;

		speed = ((int)(error*kp + integral*ki + der*kd) > minSpeed)?(int)(error*kp+integral*ki+der*kd):minSpeed;

		if(abs(nMotorEncoder[driveRightBack])-threshold < abs(nMotorEncoder[driveLeftBack])) // If the left side has more encoder ticks than the right
		{																																			// Make the right side faster, Has bias
			motor[driveRightFront] = speed;
			motor[driveRightBack] = speed;
			motor[driveLeftFront] = speed/bias;
			motor[driveLeftBack] = speed/bias;
		}
		else if(abs(nMotorEncoder[driveRightBack]) >abs( nMotorEncoder[driveLeftBack])-threshold)	// Other  way around from top comment
		{
			motor[driveRightFront] = speed/bias;
			motor[driveRightBack] = speed/bias;
			motor[driveLeftFront] = speed;
			motor[driveLeftBack] = speed;
		}
		else
		{
			motor[driveRightFront] = speed; 																				// Go normal speed value
			motor[driveRightBack] = speed;
			motor[driveLeftFront] = speed;
			motor[driveLeftBack] = speed;
		}
		}
}

