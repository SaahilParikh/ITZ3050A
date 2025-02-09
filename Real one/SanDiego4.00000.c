#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    potLeft,        sensorNone)
#pragma config(Sensor, in2,    potRight,       sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  encRight,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  clawOpen,       sensorTouch)
#pragma config(Sensor, dgtl5,  encLeft,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  liftDown,       sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           driveFrontLeft, tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           mogoleft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           driveBackLeft, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           liftRight,     tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           liftLeft,      tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           driveBackRight, tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           mogoRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          driveFrontRight, tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"


#include "function.h";


int autonomousChoice = 0;
bool auton = false;

task doubleCheck()
{
	while(bIfiRobotDisabled && !bIfiAutonomousMode)
	{
		delay(1);
	}
	auton = true;
}

void pre_auton()
{
	startTask(doubleCheck);
	bLCDBacklight = true;
	// bStopTasksBetweenModes = true;
	clearLCD();
	while(!auton)
	{
		centerLine(0,autonomousMenu[autonomousChoice]);
		centerLine(1, "Auton | Settings");

		//	waitForPress();

		if(nLCDButtons == leftButton)
		{
			waitForRelease();
			autonomousChoice = autonChooser();
		}

		else if(nLCDButtons == rightButton)
		{
			waitForRelease();
			settings();
		}

		else if(nLCDButtons == centerButton)
		{
			waitForRelease();
			preAutonBattery();
		}

	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//                                 Autonomous Task
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	//Clear LCD
	bLCDBacklight = false;
	clearLCD();

	centerLine(0,autonomousMenu[autonomousChoice]);
	centerLine(1,"Target>Error");

	switch(autonomousChoice){
	case 0:	blueRight22pt();			break;
	case 1:	blueRight24pt();      break;
	case 2:       break;
	case 3:       break;
	case 4: redLeft24pt();     	  break;
	case 5: redLeft9pt();         break;
	case 6: blueRight24pt();      break;
	case 7: blueRight9pt();       break;
	case 8:       break;
	case 9:       break;
	case 10: blueRight22pt();      break;
	case 11: redLeft22pt();      break;

	default:
		displayLCDCenteredString(0, "This should");
		displayLCDCenteredString(1, "never happen");
		auton = true;
		wait1Msec(15000);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//                                 User Control Task
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{

	bLCDBacklight = false;
	clearLCD();
	startTask(batteryLCD);
	startTask(mogoPID);
	startTask(clawDrive);
	startTask(armPID);
	startTask(mogo);
	clearLiftEnc();
	armPosTarget = armPos[0];
	while (true)
	{
		if(mogoIsFront)
			drive(vexRT[Ch3], vexRT[Ch2]);
		else
			drive(-vexRT[Ch2], -vexRT[Ch3]);

		if(vexRT[Btn8R] == 1)
		{
			//mogoIsFront = !mogoIsFront;


		}

		//	breaker = vexRT[Btn8R];

		if(vexRT[Btn6D] == 1 && getPot()<450)
		{
			stopTask(mogoPID);
			liftMogo(-20, -20);
			mogoPosTarget = getPot();
			isMove = true;
		}
		else if(coneCount > 5 && vexRT[Btn6D] == 1 && getPot()<1600)
		{
			stopTask(mogoPID);
			liftMogo(5, 5);
			mogoPosTarget = getPot();
			isMove = true;
		}
		else if(vexRT[Btn6U] == 1)
		{
			stopTask(mogoPID);
			liftMogo(90, 90);
			mogoPosTarget = getPot();
			isMove = true;
		}
		else if(vexRT[Btn6D] == 1)
		{
			stopTask(mogoPID);
			liftMogo(-127, -127);
			mogoPosTarget = getPot();
			isMove = true;
		}
		else
		{
			if(isMove)
			{
				startTask(mogoPID);
				mogoPosTarget = getPot();
				isMove = false;
			}
		}





		if(SensorValue[liftDown] == 1)
		{
			clearLiftEnc();
		}

		if(vexRT[Btn8D]==1)
		{
			bottom = driverLoadArmPos;
			armPosTarget = bottom;
		}
		else if(vexRT[Btn8U] == 1)
		{
			bottom = armPos[0];
			armPosTarget = bottom;
		}

		if(vexRT[Btn8L] == 1)
		{
			stopTask(armPID)
			while(SensorValue[liftDown] == 0)
			{
				liftArm(60, 60)
			}
			clearLiftEnc();
			liftArm(0,0);
			startTask(armPID);
		}
		wait1Msec(10);
	}
}
