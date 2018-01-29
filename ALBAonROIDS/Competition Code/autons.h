void blueRight24pt()
{
	doneWithCone = true;
	clearDriveEnc();
	clearGyro();
	startTask(drivePID);
	powClaw(70);

	startTask(drivePID);
	startTask(mogoPID);
	drivePosTarget = 500;


	liftArm(80, 80);
	mogoPosTarget = 0;
	while(getPot() >600)
	{}
	while(SensorValue[liftDown] == 0)
	{
	}
	liftArm(0, 0);
	clearLiftEnc();
	wait1Msec(500);

	drivePosTarget = 1400;

	while(driveRightEnc < 1280)
	{

	}
	wait1Msec(500);

	startTask(armPID);
	wait1Msec(10);
	startTask(cone);
	wait1Msec(10);

	mogoPosTarget = mogoPos[1];
	while(getPot() <900)
	{}
	coneCount = 1;
	wait1Msec(1700);
	drivePosTarget = 450;

	while(driveRightEnc > 500)
	{
	}

	while(driveLeftEnc > 500)
	{
	}
wait1Msec(200);
	targetHeading = -1575;
wait1Msec(900);
	while(SensorValue[liftDown] == 0)
	{

	}
	clearDriveEnc();
	drivePosTarget = 0;
	wait1Msec(200);
	clearDriveEnc();
	drivePosTarget = -630; // drive to cone
	wait1Msec(500);


	powClaw(120);
	wait1Msec(200);
	powClaw(30);
	wait1Msec(100);
	startTask(cone);

	wait1Msec(10);
	targetHeading = -1900;
	wait1Msec(200);
	clearDriveEnc();
	drivePosTarget = 1300;

	while(driveRightEnc < 1200)
	{
	}
	clearDriveEnc();

	targetHeading = -2400;
	while(SensorValue(gyro) > -2300)
	{}
	wait1Msec(100);
	clearDriveEnc();

	drivePosTarget = 190;
	while(driveRightEnc < 160)
	{
	}

	//doneWithCone =true;
	targetHeading = -1480;
	wait1Msec(1200);
	clearDriveEnc();
	drivePosTarget = 1700;
	wait1Msec(1700);
	//wait1Msec(250);
	mogoPosTarget = mogoPos[0];
	wait1Msec(1000);
	drivePosTarget = 0;


}

void blueRight24ptBackup()
{
	doneWithCone = true;
	clearDriveEnc();
	clearGyro();
	startTask(drivePID);
	powClaw(70);

	startTask(drivePID);
	startTask(mogoPID);
	drivePosTarget = 500;


	liftArm(80, 80);
	mogoPosTarget = 0;
	while(getPot() >600)
	{}
	while(SensorValue[liftDown] == 0)
	{
	}
	liftArm(0, 0);
	clearLiftEnc();
	wait1Msec(500);

	drivePosTarget = 1400;

	while(driveRightEnc < 1280)
	{

	}
	wait1Msec(500);

	startTask(armPID);
	wait1Msec(10);
	startTask(cone);
	wait1Msec(10);

	mogoPosTarget = mogoPos[1];
	while(getPot() <900)
	{}
	coneCount = 1;
	wait1Msec(1700);
	drivePosTarget = 500;

	while(driveRightEnc > 570)
	{
	}

	while(driveLeftEnc > 570)
	{
	}
wait1Msec(600);
	targetHeading = -1600;
wait1Msec(600);
	wait1Msec(200);
	while(SensorValue[liftDown] == 0)
	{

	}
	clearDriveEnc();
	drivePosTarget = 0;
	wait1Msec(1000);
	clearDriveEnc();
	drivePosTarget = -600; // drive to cone
	wait1Msec(600);


	powClaw(120);
	wait1Msec(200);
	powClaw(30);
	wait1Msec(400);
	startTask(cone);

	wait1Msec(500);
	targetHeading = -1900;
	wait1Msec(200);
	clearDriveEnc();
	drivePosTarget = 1030;

	while(driveRightEnc < 970)
	{
	}
	clearDriveEnc();

	targetHeading = -2400;
	while(SensorValue(gyro) > -2300)
	{}
	wait1Msec(100);
	clearDriveEnc();

	drivePosTarget = 250;
	while(driveRightEnc < 210)
	{
	}

	//doneWithCone =true;
	targetHeading = -1580;
	wait1Msec(1200);
	clearDriveEnc();
	drivePosTarget = 2500;
	wait1Msec(1300);
	//wait1Msec(250);
	mogoPosTarget = mogoPos[0];
	wait1Msec(1000);
	drivePosTarget = 0;


}

void redRight24pt()
{
	doneWithCone = true;
	clearDriveEnc();
	clearGyro();
	startTask(drivePID);
	powClaw(70);

	startTask(drivePID);
	startTask(mogoPID);
	drivePosTarget = 500;


	liftArm(80, 80);
	mogoPosTarget = 0;
	while(getPot() >600)
	{}
	while(SensorValue[liftDown] == 0)
	{
	}
	liftArm(0, 0);
	clearLiftEnc();
	wait1Msec(500);

	drivePosTarget = 1400;

	while(driveRightEnc < 1280)
	{

	}
	wait1Msec(500);

	startTask(armPID);
	wait1Msec(10);
	startTask(cone);
	wait1Msec(10);

	mogoPosTarget = mogoPos[1];
	while(getPot() <900)
	{}
	coneCount = 1;
	wait1Msec(700);
	drivePosTarget = 600;

	while(driveRightEnc > 640)
	{
	}

	while(driveLeftEnc > 640)
	{
	}
wait1Msec(600);
	targetHeading = -1520;
wait1Msec(600);
	wait1Msec(200);
	while(SensorValue[liftDown] == 0)
	{

	}
	clearDriveEnc();
	drivePosTarget = 0;
	wait1Msec(1000);
	clearDriveEnc();
	drivePosTarget = -500; // drive to cone
	wait1Msec(600);


	powClaw(120);
	wait1Msec(200);
	powClaw(30);
	wait1Msec(400);
	startTask(cone);

	wait1Msec(500);
	targetHeading = -1900;
	wait1Msec(200);
	clearDriveEnc();
	drivePosTarget = 1030;

	while(driveRightEnc < 970)
	{
	}
	clearDriveEnc();

	targetHeading = -2400;
	while(SensorValue(gyro) > -2300)
	{}
	wait1Msec(100);
	clearDriveEnc();

	drivePosTarget = 250;
	while(driveRightEnc < 210)
	{
	}

	//doneWithCone =true;
	targetHeading = -1550;
	wait1Msec(1200);
	clearDriveEnc();
	drivePosTarget = 2500;
	wait1Msec(1300);
	//wait1Msec(250);
	mogoPosTarget = mogoPos[0];
	wait1Msec(1000);
	drivePosTarget = 0;


}
