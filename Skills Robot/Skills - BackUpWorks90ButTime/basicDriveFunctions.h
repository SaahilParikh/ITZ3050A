#pragma systemFile
void drive(int powerL, int powerR){
	motor[driveBFLeft] = motor[driveBBLeft] = motor[driveFLeft] = powerL;
	motor[driveBBRight] = motor[driveBFRight] = motor[driveFRight] = powerR;
}
