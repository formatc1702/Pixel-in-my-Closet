void mode3() { // single blips
  toSend=BlackPixelStream;

  mode3sub(false);
}

void mode3sub(boolean multiblip) {
  if(millis()-ledmil>10) { // update LEDs
    if(curblipbrightness==0) { // create new blip at zero brightness
      // choose pixel
      curblipchange=true;
      for(int i=0;i<6;i++)
        bliparray[i]=0;

      int curblipnumbertemp=curblipnumber;
      while(curblipnumbertemp==curblipnumber) // ensure same pixel does not light up twice in a row
        curblipnumbertemp=random(0,6);
      curblipnumber=curblipnumbertemp;

      if(multiblip==true) {
        for(int i=0;i<6;i++) {
          bliparray[i]=random(0,3); // 0 and 1 = pixel off, 2 = pixel on
        }
      }

      bliparray[curblipnumber]=99; // ensure at least one pixel is on



      // raise brightness
      curblipdir=1;
    }
    else
      curblipchange=false;

    // at max brightness
    if(curblipbrightness>=254)
      curblipdir=-1; // reverse, dim

    curblipbrightness+=2*curblipdir;
    ledmil=millis();
  }

  for(int i=0;i<6;i++) {
    if(bliparray[i]>=2) { // which pixels should turn on?
      toSend.pixels[i]=VUThemes[CurrentTheme].pixels[i];

      dimPixel(&toSend.pixels[i],&toSend.pixels[i],curblipbrightness);
    }
  }
}




















