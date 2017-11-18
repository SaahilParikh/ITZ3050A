#pragma systemFile
//Basic Functions

#define NUM_DRIVE_MOTORS 4
#define NUM_LIFT_MOTORS 6

//Start of T code taken From BNS_2017, Thank You 
//I do not understand the concept of dutyCycle but I assume it will only help
#warning "Test How To Use This"
#warning "SetMotorLinear"
void SetMotorLinear(
	tMotor mot, 
	float dutyCycle)
{
	
  // Cortex's internal motor controller.
  // The relationship between motor value and pwm is perfectly
  // proportional.  Ex. 60/127 = 0.47, so the duty cycle is 47%.
  if (mot == port1 || mot == port10)
  {
    motor[mot] = (int)(dutyCycle * 127.0);
  }
  // External MC29's.
  // The relationship between motor value is linear, but goes from 6->86.
  else
  {
    if (fabs(dutyCycle) <= 0) motor[mot] = 0;
    if (dutyCycle >= 0.97) motor[mot] = 127;
    if (dutyCycle <= -0.97) motor[mot] = -127;
    else motor[mot] = (int)(82.91 * dutyCycle + 5.0854);
  }
  
}

#warning "setMotor"
void setMotor(
	tMotor* motor,
	float dutyCycle)
{
	
	SetMotorLinear(motor, dutyCycle/127);
	
}
//End of Code taken from BNS_2017

#warning "setLeftDrive"
void setleftDrive(
	int power)
{	

	if(NUM_DRIVE_MOTORS/2 == 1){
		setMotorLinear(driveL1, power/127);
		
	}
	else if(NUM_DRIVE_MOTORS/2 == 2) {
		setMotorLinear(driveL1, power/127);
		setMotorLinear(driveL2, power/127);
	}
	else if(NUM_DRIVE_MOTORS/2 == 3) {
		setMotorLinear(driveL1, power/127);
		setMotorLinear(driveL2, power/127);
		setMotorLinear(driveL3, power/127);
	}
	else if(NUM_DRIVE_MOTORS/2 == 4) {
		setMotorLinear(driveL1, power/127);
		setMotorLinear(driveL2, power/127);
		setMotorLinear(driveL3, power/127);
		setMotorLinear(driveL4, power/127);
	}
	
}

#warning "setRightDrive"
void setRightDrive(
	int power)
{
	
	if(NUM_DRIVE_MOTORS/2 == 1){
		setMotorLinear(driveR1, power/127);	
	}
	else if(NUM_DRIVE_MOTORS/2 == 2) {
		setMotorLinear(driveR1, power/127);
		setMotorLinear(driveR2, power/127);
	}
	else if(NUM_DRIVE_MOTORS/2 == 3) {
		setMotorLinear(driveR1, power/127);
		setMotorLinear(driveR2, power/127);
		setMotorLinear(driveR3, power/127);
	}
	else if(NUM_DRIVE_MOTORS/2 == 4) {
		setMotorLinear(driveR1, power/127);
		setMotorLinear(driveR2, power/127);
		setMotorLinear(driveR3, power/127);
		setMotorLinear(driveR4, power/127);
	}
	
}

#warning "drive"
void drive(
	int leftpower,
	int rightpower)
{
	
	setLeftDrive(leftpower);
	setRightDrive(rightpower);	

}	

#warning "lift"
void lift(
	int power)
{
	switch(NUM_LIFT_MOTORS)
	{
		case 1:
			SetMotorLinear(Lift1, power);
		break;
		case 2:
			SetMotorLinear(Lift1, power);
			SetMotorLinear(Lift2, power);
		break;
		case 3:
			SetMotorLinear(Lift1, power);
			SetMotorLinear(Lift2, power);
			SetMotorLinear(Lift3, power);
		break;
		case 4:
			SetMotorLinear(Lift1, power);
			SetMotorLinear(Lift2, power);
			SetMotorLinear(Lift3, power);
			SetMotorLinear(Lift4, power);
		break;
		case 5:
			SetMotorLinear(Lift1, power);
			SetMotorLinear(Lift2, power);
			SetMotorLinear(Lift3, power);
			SetMotorLinear(Lift4, power);
			SetMotorLinear(Lift5, power);
		break;
		case 6:
			SetMotorLinear(Lift1, power);
			SetMotorLinear(Lift2, power);
			SetMotorLinear(Lift3, power);
			SetMotorLinear(Lift4, power);
			SetMotorLinear(Lift5, power);
			SetMotorLinear(Lift6, power);
		break;
		case 7:
			SetMotorLinear(Lift1, power);
			SetMotorLinear(Lift2, power);
			SetMotorLinear(Lift3, power);
			SetMotorLinear(Lift4, power);
			SetMotorLinear(Lift5, power);
			SetMotorLinear(Lift6, power);
			SetMotorLinear(Lift7, power);
		break;
		case 8:
			SetMotorLinear(Lift1, power);
			SetMotorLinear(Lift2, power);
			SetMotorLinear(Lift3, power);
			SetMotorLinear(Lift4, power);
			SetMotorLinear(Lift5, power);
			SetMotorLinear(Lift6, power);
			SetMotorLinear(Lift7, power);
			SetMotorLinear(Lift8, power);
		break;
	}
}



