void sdkills()
{
	clearGyro();
	clearDriveEnc();

	driveTurn(900, 9999999999999);

	driveTurn(targetHeading-1197, 99999999999999);
	clearDriveEnc();

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

	driveKeepHeading(-200); // bcjkward parellel to bar

	driveTurn(-1350); // perpendic to bar
	clearDriveEnc();

	driveKeepHeading(100);
	startTask(mogoDownTask);
	driveKeepHeading(300); // forward
													 //mogo down
	drive(-30, -30);
	wait1Msec(200);

	mogoDriveUp(); // mogo up

	driveKeepHeading(-133); // robot backwards
}
///BADDDfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
