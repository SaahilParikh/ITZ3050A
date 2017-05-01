
task main()
{
	time1[T1] = 0;
	//clearLCDLine(0);

  //displayNextLCDString("Hello");
	clearDebugStream();

	while (time1[T1] <15000)
	{
		//int t = time1[T1];
	if(time1[T1]%1000 == 0)
		writeDebugStreamLine("setDrive(%d);/r/n", time1[T1]);
		displayLCDNumber(1, 5, time1[T1], 4);
	}
		wait10Msec(200);



}
