void loop ()
{ 
  //serialdebug();
  checktime();

  if ( mintens + minunits + sectens + secunits  >= 1 ){
    timeleft = HIGH;
  }    // check again after countdown
  else
  {
    timeleft = LOW ;
    pause = HIGH;   
  }     //  flashing dots
  unsigned long currentdotMillis = millis();
  if(currentdotMillis - previousdotMillis > 500) {
    previousdotMillis = currentdotMillis;   
    if (dotState == LOW)
    {
      dotState = HIGH;
    }   
    else     {
      dotState = LOW;
    }
      showtime ();
  }
  if ( pause == LOW ) {   // change this to HIGH if you only want the dots flashing while counting
    dotState = HIGH ;
  }

  //     blank =0;  //  brings display out of standbye with any button pressed

  checkbutton ();   
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
  webSocket.loop();
  server.handleClient();
}
