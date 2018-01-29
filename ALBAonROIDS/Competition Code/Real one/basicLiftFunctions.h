
#pragma systemFile
void liftArm(int powerL, int powerR){
motor[liftLeft] = powerL;
motor[liftRight] = powerR;
}
void liftMogo (int powerL, int powerR){
motor[mogoleft] = powerL;
motor[mogoRight] = powerR;
}
