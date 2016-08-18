void mode1() { // Cycle on or off
  toSend=BlackPixelStream;
  if(cyclecolors)
  toSend.pixels[1]=VUThemes[5].pixels[1];
  else
  toSend.pixels[1]=GreyPixel;
}





