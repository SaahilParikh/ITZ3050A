/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Functions
//
/////////////////////////////////////////////////////////////////////////////////////////

//Hault Functions//

void haultDrive( int time )
{
	motor[driveRightFront] = 0;
	motor[driveRightBack] = 0;
	motor[driveLeftFront] = 0;
	motor[driveLeftBack] = 0;
	wait1Msec(time);
}

void haultLift( int time )
{
	motor[liftLeftEnc] = 0;
	motor[liftLeftIn] = 0;
	motor[liftLeftTop] = 0;
	motor[liftRightEnc] = 0;
	motor[liftRightIn] = 0;
	motor[liftRightTop] = 0;
	wait1Msec(time);
}

void haultAll(int time)
{
	haultDrive(time);
	haultLift(time);
}


//Clear Functions//

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


//Drive Functions//

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

#warning "Tune Autocorrection Threshhold - 2/13/2017";

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

		if(Encoder < 0)
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

void driveEnc(int speed, int Encoder)
{
	int bias = 3;
	while (nMotorEncoder[driveLeftBack] < Encoder || nMotorEncoder[driveRightBack] < Encoder)
	{
		if (SensorValue(gyro) > 10)
		{
			motor[driveRightFront] = speed;
			motor[driveRightBack] = speed;
			motor[driveLeftFront] = speed/bias;
			motor[driveLeftBack] = speed/bias;
		}
		else if (SensorValue(gyro) < 10)
		{
			motor[driveRightFront] = speed/bias;
			motor[driveRightBack] = speed/bias;
			motor[driveLeftFront] = speed;
			motor[driveLeftBack] = speed;
		}
		else
		{
			motor[driveRightFront] = speed;
			motor[driveRightBack] = speed;
			motor[driveLeftFront] = speed;
			motor[driveLeftBack] = speed;
		}
	}
}

void driveTime(int speed, int time)
{
	motor[driveRightFront] = speed;
	motor[driveRightBack] = speed;
	motor[driveLeftFront] = speed;
	motor[driveLeftBack] = speed;
	wait1Msec(time);
}

void drive(int rightSide, int leftSide, int time)
{
	motor[driveRightFront] = rightSide;
	motor[driveRightBack] = rightSide;
	motor[driveLeftFront] = leftSide;
	motor[driveLeftBack] = leftSide;
	wait1Msec(time);
}


//Lift Function//
void liftTime(int speed, int time)
{
	motor[liftLeftEnc] = speed;
	motor[liftLeftIn] = speed;
	motor[liftLeftTop] = speed;
	motor[liftRightEnc] = speed;
	motor[liftRightIn] = speed;
	motor[liftRightTop] = speed;
	wait1Msec(time);
}

void liftEnc(int speed, int Enc)
{
	while(nMotorEncoder[liftLeftEnc] < Enc && nMotorEncoder[liftRightEnc] < Enc)
	{
		motor[liftLeftEnc] = speed;
		motor[liftLeftIn] = speed;
		motor[liftLeftTop] = speed;
		motor[liftRightEnc] = speed;
		motor[liftRightIn] = speed;
		motor[liftRightTop] = speed;
	}
}

void lift2Bottom()
{
	while(SensorValue(liftBottom) != 1)
	{
		motor[liftLeftEnc] = -107;
		motor[liftLeftIn] = -107;
		motor[liftLeftTop] = -107;
		motor[liftRightEnc] = -107;
		motor[liftRightIn] = -107;
		motor[liftRightTop] = -107;
	}
	clearLift();
}

//Claw functions//

void openClaw()
{
}

void closeClaw()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	while (true)
	{
		motor[driveRightFront] = vexRT[Ch2];
		motor[driveRightBack] = vexRT[Ch2];
		motor[driveLeftFront] = vexRT[Ch3];
		motor[driveLeftBack] = vexRT[Ch3];

		if(SensorValue(liftBottom) == 1)
		{
			nMotorEncoder(liftLeftEnc) = 0;
			nMotorEncoder(liftRightEnc) = 0;
		}

		if(vexRT[Btn5D] == 1 || abs(nMotorEncoder[liftRightEnc]) > releaseThreshold || abs(nMotorEncoder[liftLeftEnc]) > releaseThreshold)
		{
			openClaw();
		}
		else if (vexRT[Btn5U] == 1)
		{
			closeClaw();
		}

		if(vexRT[Btn6U] == 1)
		{
			closeClaw();
			motor[liftLeftEnc] = 127;
			motor[liftLeftIn] = 127;
			motor[liftLeftTop] = 127;
			motor[liftRightEnc] = 127;
			motor[liftRightIn] = 127;
			motor[liftRightTop] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[liftLeftEnc] = -127;
			motor[liftLeftIn] = -127;
			motor[liftLeftTop] = -127;
			motor[liftRightEnc] = -127;
			motor[liftRightIn] = -127;
			motor[liftRightTop] = -127;
		}

		else
		{
			if(isDone)
			{
				motor[liftLeftEnc] = 0;
				motor[liftLeftIn] = 0;
				motor[liftLeftTop] = 0;
				motor[liftRightEnc] = 0;
				motor[liftRightIn] = 0;
				motor[liftRightTop] = 0;
			}
			else if(SensorValue[liftBottom] == 0)
			{
				motor[liftLeftEnc] = heightThreshold;
				motor[liftLeftIn] = heightThreshold;
				motor[liftLeftTop] = heightThreshold;
				motor[liftRightEnc] = heightThreshold;
				motor[liftRightIn] = heightThreshold;
				motor[liftRightTop] = heightThreshold;
			}
			else
			{
				motor[liftLeftEnc] = -10;
				motor[liftLeftIn] = -10;
				motor[liftLeftTop] = -10;
				motor[liftRightEnc] = -10;
				motor[liftRightIn] = -10;
				motor[liftRightTop] = -10;

			}
		}
	}
}
