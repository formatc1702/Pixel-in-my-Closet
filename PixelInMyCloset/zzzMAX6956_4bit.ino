/*
void WireSetup_MAX6956_4bit() {
  Wire.begin();
  Wire.beginTransmission(max6956);
  Wire.send(0x02); // global current register
  Wire.send(0x0F); // max current
  Wire.endTransmission();   
  Wire.beginTransmission(max6956);
  Wire.send(0x04); // config register
  Wire.send(0x41); //  individual current control, shutdown disabled
  Wire.endTransmission();   
  for(i=0x09;i<=0x0F;i++) { // for the 7 port registers
    Wire.beginTransmission(max6956);
    Wire.send(i);
    Wire.send(0x00); // set them as LED drivers
    Wire.endTransmission();   
  }
}

void WriteColors_MAX6956_4bit() {
  // ports 13 to 30
  byte port1320=0;
  byte port2128=0;
  byte port2930=0;
  byte fourbitbrightness[10]={
    0,0,0,0,0,0,0,0,0,0  };

  port1320=0;
  port2128=0;
  port2930=0;

  if(toSend.pixels[0].blue>0)
    port1320|=B00000001 ;
  if(toSend.pixels[0].green>0)
    port1320|=B00000010 ;
  if(toSend.pixels[0].red>0)
    port1320|=B00000100 ;

  if(toSend.pixels[1].blue>0)
    port1320|=B00001000 ;
  if(toSend.pixels[1].green>0)
    port1320|=B00010000 ;
  if(toSend.pixels[1].red>0)
    port1320|=B00100000 ;

  if(toSend.pixels[2].blue>0)
    port1320|=B01000000 ;
  if(toSend.pixels[2].green>0)
    port1320|=B10000000 ;
  if(toSend.pixels[2].red>0)
    port2128|=B00000001 ;

  if(toSend.pixels[3].blue>0)
    port2128|=B00000010 ;
  if(toSend.pixels[3].green>0)
    port2128|=B00000100 ;
  if(toSend.pixels[3].red>0)
    port2128|=B00001000 ;

  if(toSend.pixels[4].blue>0)
    port2128|=B00010000 ;
  if(toSend.pixels[4].green>0)
    port2128|=B00100000 ;
  if(toSend.pixels[4].red>0)
    port2128|=B01000000 ;

  if(toSend.pixels[5].blue>0)
    port2128|=B10000000 ;
  if(toSend.pixels[5].green>0)
    port2930|=B00000001 ;
  if(toSend.pixels[5].red>0)
    port2930|=B00000010 ;


  // Dimming
  struct Streamstate curstream;
  curstream.curbyte=fourbitbrightness;
  curstream.curnibble=false;
  fourbitbrightness[0]=0;
  for(i=0;i<=5;i++) {
    packRGB(&(toSend.pixels[i]),&curstream); // equivalent: packRGB(toSend.pixels+i,&curstream);
  }
  

  Wire.beginTransmission(max6956);
  Wire.send(0x16);
  for(i=0;i<=9;i++) {
    Wire.send(fourbitbrightness[i]);
  } 
  Wire.endTransmission();   

  Wire.beginTransmission(max6956);
  Wire.send(0x4D); 
  Wire.send(port1320);
  Wire.endTransmission();   
  Wire.beginTransmission(max6956);
  Wire.send(0x55); 
  Wire.send(port2128);
  Wire.endTransmission();   
  Wire.beginTransmission(max6956);
  Wire.send(0x5D); 
  Wire.send(port2930);
  Wire.endTransmission();   
}

void packRGB(const struct Pixel* source, struct Streamstate* s) {
  // curnibble true = niederwertig zuerst
  if(s->curnibble) {
    *(s->curbyte)=(source->blue>>4);
    *(s->curbyte++)|= (source->green & 0xF0);
    *(s->curbyte) =(source->red>>4);
  }
  else {
    *(s->curbyte++)|=(source->blue & 0xF0);
    *(s->curbyte) =(source->green>>4);
    *(s->curbyte++)|=(source->red&0xF0);

  }
  s->curnibble = !(s->curnibble);
}
//*/
