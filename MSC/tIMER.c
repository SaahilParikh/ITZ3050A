
task main()
{
	time1[T1] = 0;
	//clearLCDLine(0);

  //displayNextLCDString("Hello");
  writeDebugStream("HEDLLO");
	while (time10[T1] <1500)
	{
		int t = time1[T1];
		displayLCDNumber(1, 4, t, 4);
	}
		wait10Msec(200);



}
