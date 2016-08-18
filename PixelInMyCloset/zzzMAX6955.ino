/*
void WireSetup_MAX6955() {
  Wire.begin();
  Wire.beginTransmission(max6955);
  Wire.send(0x01); // config register
  Wire.send(0x00); // no decode!
  Wire.send(0x08); // global current to max
  Wire.send(0x01); // only use digits 0 and 1
  Wire.send(0x01); // global current control, shutdown disabled
  Wire.endTransmission(); 

  for(i=0x20;i<=0x4F;i++) {
    Wire.beginTransmission(max6955);
    Wire.send(i); // digit registers
    Wire.send(0x00); // clear all
    Wire.endTransmission();   
  }
}

void WriteColors_MAX6955() {
byte led01=0;
byte led23=0;
byte led45=0;

  led01=0;
  led23=0;
  led45=0;

  if(reds[0]>=128)
    led01|=B01000000 ;
  if(greens[0]>=128)
    led01|=B00100000 ;
  if(blues[0]>=128)
    led01|=B00010000 ;

  if(reds[1]>=128)
    led01|=B00000100 ;
  if(greens[1]>=128)
    led01|=B00000010 ;
  if(blues[1]>=128)
    led01|=B00000001 ;

  if(reds[2]>=128)
    led23|=B01000000 ;
  if(greens[2]>=128)
    led23|=B00100000 ;
  if(blues[2]>=128)
    led23|=B00010000 ;

  if(reds[3]>=128)
    led23|=B00000100 ;
  if(greens[3]>=128)
    led23|=B00000010 ;
  if(blues[3]>=128)
    led23|=B00000001 ;

  if(reds[4]>=128)
    led45|=B01000000 ;
  if(greens[4]>=128)
    led45|=B00100000 ;
  if(blues[4]>=128)
    led45|=B00010000 ;

  if(reds[5]>=128)
    led45|=B00000100 ;
  if(greens[5]>=128)
    led45|=B00000010 ;
  if(blues[5]>=128)
    led45|=B00000001 ;

}
// */
