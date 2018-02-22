void sdkills()
{
	clearGyro();
	clearDriveEnc();

	driveTurn(900, 9999999999999);

	driveTurn(5000, 99999999);

}

void skills()
{

	clearGyro();
	clearDriveEnc();
	SensorFullCount[gyro] = 7200;

	startTask(mogoDownTask); //MobileGoalLiftDown for the first Mogo
	driveKeepHeading(1340, 0 ,-1500); // Drive into the first mogo

	drive(30, 30);
	wait1Msec(250);
	startTask(mogoUpTask);
	drive(30, 30);
	wait1Msec(850);

	startTask(coneDrop);

	driveKeepHeading(150, 0, -1000); //drive back just infront of starting position

	driveTurn(-450); // turn 45 degrees to line up with starting pole, parrallel.
	clearDriveEnc();

	driveKeepHeading(-900); // bcjkward parellel to bar

	driveTurn(-1350); // perpendic to bar
	clearDriveEnc();

	driveKeepHeading(700);
	startTask(mogoDownTask);
	driveKeepHeading(900); // forward
													 //mogo down
	drive(-30, -30);
	wait1Msec(500);

	mogoDriveUp(); // mogo up

	driveKeepHeading(253); // robot backwards

	driveTurn(targetHeading-1194, -1500);
	clearDriveEnc();

	//driveKeepHeading(-510);
	stopTask(mogoUpTask);

	startTask(mogoDownTask);

	driveKeepHeading(1666, targetHeading, -1420);

	drive(8, 8);
	wait1Msec(540);

	drive(25, 25);
	wait1Msec(280);
	startTask(mogoUpTask);
	drive(30, 30);
	wait1Msec(750);

	driveKeepHeading(-70, targetHeading, -1270);

	driveTurn(targetHeading+1194);
	clearDriveEnc();

	startTask(mogoDownTask);//2ndmogo drop

	driveKeepHeading(170);

	driveKeepHeading(-160);

	driveTurn(targetHeading+900);
	clearDriveEnc();

	driveKeepHeading(495);

	driveTurn(targetHeading+900);
	clearDriveEnc();

	driveKeepHeading(660);

	drive(30, 30);
	wait1Msec(250);
	startTask(mogoUpTask); // pick 3rd
	drive(30, 30);
	wait1Msec(850);

	driveKeepHeading(0);

	driveTurn(targetHeading+1800);
	clearDriveEnc();

	startTask(mogoDownTask); // drop 3rd
	driveKeepHeading(420);

	powMogo(60);

	driveKeepHeading(240);

	powMogo(0);

	driveTurn(targetHeading-900);
	clearDriveEnc();

	startTask(mogoDownTask);

	driveKeepHeading(880);

	driveTurn(targetHeading-900);
	clearDriveEnc();

	driveKeepHeading(650);

	drive(30, 30);
	wait1Msec(250);
	startTask(mogoUpTask);
	drive(30, 30);
	wait1Msec(850);

	driveKeepHeading(0);

	driveTurn(targetHeading-1800);
	clearDriveEnc();

	startTask(mogoDownTask);
	driveKeepHeading(270);

	driveKeepHeading(100);

	startTask(mogoUpTask);

	driveTurn(targetHeading+1770);
	clearDriveEnc();

	startTask(mogoDownTask);

	driveKeepHeading(1500, targetHeading, -700, 30);

	drive(30, 30);
	wait1Msec(250);
	startTask(mogoUpTask);
	drive(30, 30);
	wait1Msec(850);

	driveKeepHeading(2400, targetHeading, -700, 30);

	driveTurn(targetHeading-127);
	clearDriveEnc();

	driveKeepHeading(1220);

	startTask(mogoDownTask);

	driveTurn(targetHeading+127);
	clearDriveEnc();

	driveKeepHeading(200);


	wait1Msec(300);

	startTask(mogoUpTask);

	driveKeepHeading(0);
	wait1Msec(400);


	driveKeepHeading(-300);
/*
	driveTurn(targetHeading+1218);
	clearDriveEnc();

	stopTask(mogoUpTask);

	startTask(mogoDownTask);

	driveKeepHeading(1700, targetHeading, -1500, 30);

	drive(30, 30);
	wait1Msec(250);
	startTask(mogoUpTask);
	drive(30, 30);
	wait1Msec(850);

	driveKeepHeading(0, targetHeading, -1300, 30);

	driveTurn(targetHeading-1218);
	clearDriveEnc();

	startTask(mogoDownTask);
	driveKeepHeading(300);

	driveKeepHeading(0);

*/
	driveTurn(targetHeading-900);
	clearDriveEnc();

	startTask(mogoDownTask);

	driveKeepHeading(480);

	driveTurn(targetHeading-900);
	clearDriveEnc();

	driveKeepHeading(630);

	drive(30, 30);
	wait1Msec(250);
	startTask(mogoUpTask);
	drive(30, 30);
	wait1Msec(850);

	driveTurn(targetHeading-1650);
	clearDriveEnc();

	driveKeepHeading(900, targetHeading, -900, 30);
	startTask(mogoDownTask);
	driveKeepHeading(1200);
	drive(-127, -42);
}
///BADDDfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
