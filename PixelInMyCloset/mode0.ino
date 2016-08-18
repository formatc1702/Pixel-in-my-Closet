void mode0() {
  //toSend=BlackPixelStream;

  // RECEIVE SIGNAL

  cur=analogRead(audioinputpin); // get signal from opamp

  // CALCULATE AND AVERAGE SCALE

  if(cur>maxes[curmaxcounter]) // get the maximum amplitude in this sampling cycle
    maxes[curmaxcounter]=cur;


  if(millis()-maxavgmil>600 || cur>avgmax) { // create average maximum
    int tempmax=0;
    for(i=0;i<10;i++) {
      tempmax+=maxes[i]; // take the last ten samples
    }
    avgmax=tempmax/10; // and average them
    curmaxcounter++; // then move to the next sample slot
    if(curmaxcounter==10)
      curmaxcounter=0;
    maxes[curmaxcounter]=0; // and start with a value of 0
    maxavgmil=millis();
  }

  if(cur<10)
    cur=0;
  cur=min(map(cur,0,avgmax,0,255),255); // Map the audio signal to a norm of 0-255
  cur=max(map(cur,0,255,-128,255),0);
  //cur=((long)cur)*((long)cur)/255;

    //cur=0.01058*cur*cur-1.69841*cur;
  //cur=pow(1.021968,cur);
  //cur=0.0000209966*pow(cur,3)-0.00407406*pow(cur,2)+0.6696592*cur+1;


  // SMOOTH GOING DOWN

  if(cur>smooth) // react to peaks immediately, +40 to avoid extreme flicker
    smooth=cur;
  if(millis()-smoothmil>2) { // but let them fade out gradually
    if(cur>smooth) {
      smooth=min(smooth,255);
    }
    if(cur<smooth) {
      smooth -=1;
      smooth=max(smooth,0);
    }
    smoothmil=millis();
  }

  //smooth=cur;

  // TOP BAR

  if(cur>topbar) { // react to peaks immediately
    topbar=cur;
    topbarmil=millis(); 
  }
  if(millis()-topbarmil>10) { // but make the top bar drop slowly
    topbar-=2;
    topbarmil=millis(); 
  }

  // ANALYSE SIGNAL AND GENERATE VU OUTPUT

  if(millis()-ledmil>10) { // update LEDs
    ledcount=min(smooth*6/255,6);
    for(i=0;i<=ledcount-1;i++) {
      toSend.pixels[i]=VUThemes[CurrentTheme].pixels[i];
    }
    if(ledcount<6) {
      dim=(6*smooth)%255;
      dimPixel(&(VUThemes[CurrentTheme].pixels[ledcount]),&(toSend.pixels[ledcount]),dim);
    }
    for(i=ledcount+1;i<=5;i++) {
      toSend.pixels[i]=BlackPixel;
    }
    ledmil=millis();
  }
}

void dimPixel(const struct Pixel* source, struct Pixel* destination, byte brightness) {
  destination->red=(byte)(((long)(source->red))*brightness/255);
  destination->green=(byte)(((long)(source->green))*brightness/255);
  destination->blue=(byte)(((long)(source->blue))*brightness/255);
}












