void lift(int speed)
{
		motor[liftLeftEnc] = speed;
		motor[liftLeftIn] = speed;
		motor[liftLeftTop] = speed;
		motor[liftRightEnc] = speed;
		motor[liftRightIn] = speed;
		motor[liftRightTop] = speed;
}
