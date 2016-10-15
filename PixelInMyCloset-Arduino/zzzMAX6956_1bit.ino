/*
void WireSetup_MAX6956_1bit() {
  Wire.begin();
  Wire.beginTransmission(max6956);
  Wire.send(0x02); // global current register
  Wire.send(0x0F); // max current
  Wire.endTransmission();   
  Wire.beginTransmission(max6956);
  Wire.send(0x04); // config register
  Wire.send(0x01); //  global current control, shutdown disabled
  Wire.endTransmission();   
  for(int i=0x09;i<=0x0F;i++) { // for the 7 port registers
    Wire.beginTransmission(max6956);
    Wire.send(i);
    Wire.send(0x00); // set them as LED drivers
    Wire.endTransmission();   
  }
}

void WriteColors_MAX6956_1bit() {
byte port1320=0;
byte port2128=0;
byte port2930=0;
byte fourbitbrightness[10]={
  0,0,0,0,0,0,0,0,0,0};

  // ports 13 to 30
  port1320=0;
  port2128=0;
  port2930=0;

  if(blues[0]>=128)
    port1320|=B00000001 ;
  if(greens[0]>=128)
    port1320|=B00000010 ;
  if(reds[0]>=128)
    port1320|=B00000100 ;

  if(blues[1]>=128)
    port1320|=B00001000 ;
  if(greens[1]>=128)
    port1320|=B00010000 ;
  if(reds[1]>=128)
    port1320|=B00100000 ;

  if(blues[2]>=128)
    port1320|=B01000000 ;
  if(greens[2]>=128)
    port1320|=B10000000 ;
  if(reds[2]>=128)
    port2128|=B00000001 ;

  if(blues[3]>=128)
    port2128|=B00000010 ;
  if(greens[3]>=128)
    port2128|=B00000100 ;
  if(reds[3]>=128)
    port2128|=B00001000 ;

  if(blues[4]>=128)
    port2128|=B00010000 ;
  if(greens[4]>=128)
    port2128|=B00100000 ;
  if(reds[4]>=128)
    port2128|=B01000000 ;

  if(blues[5]>=128)
    port2128|=B10000000 ;
  if(greens[5]>=128)
    port2930|=B00000001 ;
  if(reds[5]>=128)
    port2930|=B00000010 ;


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
// */
