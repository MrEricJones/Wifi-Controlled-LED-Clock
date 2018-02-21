#define latchPin 14  // D5
#define clockPin 12  // D6
#define dataPin 13   // D7

#define plusPin 0   // D3
#define minusPin 4   // D2
#define runPin 2   // D4
#define pausePin 5   // D1 

//--------------------------------

void checktime () {
  if ( mintens + minunits + sectens + secunits  >= 1 )  //  if time still left on countdown
  {
    timeleft = HIGH;
  }
  else {
    timeleft = LOW ;
    pause = HIGH;
  }

  if (timeleft == HIGH ) {
    if ( pause == LOW ) {  //  which means its counting down   i.e. not paused in countdown         
      static unsigned long previousMillis;
      if(millis() > previousMillis)
      {
        previousMillis = millis() + 1010;
        secunits -- ;             // countdown 1 sec
        if ( secunits  < 0 ){
          secunits = 9; 
          sectens -- ;
        }
        if ( sectens   < 0 ){
          sectens = 5; 
          minunits -- ;
        }
        if ( minunits  < 0 ){
          minunits = 9; 
          mintens -- ;
        }
        // mintens cant get to -1 or it would have to have been 0000 and paused
                Serial.print(mintens); 
                Serial.print(minunits); 
                Serial.print(" : ");
                Serial.print(sectens); 
                Serial.print(secunits);
                Serial.print("   Button Status: ");
                Serial.print("Start: ");
                Serial.print(runbutton);
                Serial.print("  Pause: ");
                Serial.print(pausebutton);
                Serial.print("  UP: ");
                Serial.print(plus);
                Serial.print("  DOWN: ");
                Serial.println(minus);
                
        showtime ();

        if ( mintens + minunits + sectens + secunits  >= 1 ){
          timeleft = HIGH;
        }
//        else {
//          digitalWrite( hornPin, HIGH ) ;
//          timeleft = LOW ;
//          pause = HIGH ;
//          delay ( 2000 );
//        }// milliseconds hornPin goes high
//        digitalWrite( hornPin, LOW );

      }
      dotState = HIGH;
    } // keeps dots on while countdown
    else
      if ( blank == LOW ) {
      flashdots ();
    }

  }
} // END OF CHECKTIME

void serialdebug(){
  Serial.print(mintens); 
  Serial.print(minunits); 
  Serial.print(" : ");
  Serial.print(sectens); 
  Serial.print(secunits);
  Serial.print("   Button Status: ");
  Serial.print("Start: ");
  Serial.print(runbutton);
  Serial.print("  Pause: ");
  Serial.print(pausebutton);
  Serial.print("  UP: ");
  Serial.print(plus);
  Serial.print("  DOWN: ");
  Serial.println(minus);
}

void checkbutton ()
{   
  plus = digitalRead( plusPin );
  if ( plus == LOW && pause == HIGH) {
    delay ( 200 );     
    if ( secunits !=0 ){     
      secunits=0;   
    }   
    if ( sectens !=0 ){     
      sectens=0;   
    }
    minunits ++;
    resetmtens = mintens;
    resetmunit = minunits;
    resetstens = sectens;
    resetsunit = secunits;     
  }

  if ( minunits > 9 ){     
    minunits=0;       
    mintens ++;
    resetmtens = mintens;
    resetmunit = minunits;
    resetstens = sectens;
    resetsunit = secunits; 

  }

  if ( mintens >5 ){       
    mintens = 0 ;   
  }

  minus = digitalRead( minusPin );
  if ( minus == LOW && pause == HIGH) { 
    secunits --;
    resetmtens = mintens;
    resetmunit = minunits;
    resetstens = sectens;
    resetsunit = secunits; 

  }

  if ( secunits  < 0 ){       
    secunits = 9;       
    sectens -- ;   
    resetmtens = mintens;
    resetmunit = minunits;
    resetstens = sectens;
    resetsunit = secunits; 

  }
  if ( sectens   < 0 ){       
    sectens = 5;       
    minunits -- ;   
    resetmtens = mintens;
    resetmunit = minunits;
    resetstens = sectens;
    resetsunit = secunits; 

  }
  if ( minunits  < 0 ){       
    minunits = 9;       
    mintens -- ;   
    resetmtens = mintens;
    resetmunit = minunits;
    resetstens = sectens;
    resetsunit = secunits; 

  } 
  if ( mintens < 0 ){       
    mintens =5 ;     
    resetmtens = mintens;
    resetmunit = minunits;
    resetstens = sectens;
    resetsunit = secunits; 

  }


  //  CHANGE THIS DELAY TO SET COUNTSPEED WHEN + or - BUTTON HELD IN
  if ( plus || minus == LOW ){ 
    delay ( 100 ) ;     
    showtime ();
  } 

  // when run button pressed release pause
  runbutton = digitalRead( runPin );
  if ( runbutton == LOW ) {
    pause = LOW ;
  }

  // when pause button pressed  set pause
  pausebutton = digitalRead( pausePin ); 
  if ( pausebutton == LOW ) {
    pause = HIGH ;
  }

  // when pause and run button pressed reset to start value
  if (runbutton == LOW && pausebutton == LOW) {
    mintens = resetmtens;
    minunits = resetmunit;
    sectens = resetstens;
    secunits = resetsunit;
  }

}  // end of checkbutton function

void flashdots () {
  unsigned long currentdotMillis = millis();
  if(currentdotMillis - previousdotMillis > 500) {
    previousdotMillis = currentdotMillis;   
    if (dotState == LOW)
    {
      dotState = HIGH;
    }
    else  {
      dotState = LOW;
    }     
    showtime (); 
  }
  if ( pause == LOW ) {
    dotState = HIGH ;
  } 
} //  end of flashdots routins

void showtime ()   //  DISPLAY ROUTINE
{   
  int mintendisp = (mintens) ? digitTable [ mintens ] : 0;  //  zero blanking tens minutes
  int minunitsdisp = digitTable [ minunits ];
  int sectensdisp = digitTable [ sectens ];
  int secunitsdisp = digitTable [ secunits ];
  if ( dotState == HIGH ){

    //minunitsdisp = minunitsdisp|00000001 ;
    mintendisp = mintendisp|00000001 ;
  }      //   adds msb to minunit to light dots when dotState high



  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, LSBFIRST, secunitsdisp);
  shiftOut(dataPin, clockPin, LSBFIRST, sectensdisp);
  shiftOut(dataPin, clockPin, LSBFIRST, minunitsdisp);
  shiftOut(dataPin, clockPin, LSBFIRST, mintendisp);

  digitalWrite(latchPin, HIGH);
}




