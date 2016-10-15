#include <Wire.h>
#include "lib/Tlc5940/Tlc5940.h"
//#define max6955 B1100000
//#define max6956 B1000000

// MODE STUFF ***********************************************************

int CurrentMode=0;
int CurrentTheme=4;
long NewModeTimer=0;
boolean PoweredOn=true;

// GENERAL STUFF ******************************************************
int i;
long writemil=0;

// PIXEL STUFF ********************************************************

struct Pixel {
  byte red;
  byte green;
  byte blue;
};
struct Pixel BlackPixel={
  0,0,0};
struct Pixel RedPixel={
  255,0,0};
struct Pixel GreenPixel={
  0,255,0};
struct Pixel BluePixel={
  0,0,255};
struct Pixel YellowPixel={
  255,255,0};
struct Pixel CyanPixel={
  0,255,255};
struct Pixel MagentaPixel={
  255,0,255};
struct Pixel WhitePixel={
  255,255,255};
struct Pixel GreyPixel={
  128,128,128
};
struct Pixel OrangePixel={
  255,128,0};

struct PixelStream {
  struct Pixel pixels[6];
};
struct PixelStream BlackPixelStream={
  BlackPixel,BlackPixel,BlackPixel,BlackPixel,BlackPixel,BlackPixel};
struct PixelStream WhitePixelStream={
  WhitePixel,WhitePixel,WhitePixel,WhitePixel,WhitePixel,WhitePixel};

PixelStream toSend={
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// REMOTE STUFF *********************************************************

#define RemoteREV  0x10
#define RemoteFWD  0x08
#define RemotePLAY 0x01
#define RemoteVDN  0x04
#define RemoteVUP  0x02

byte RemoteLastCommand=0x00;
boolean gotRemote=false;

// MODE 0 - Audiostuff***************************************************
int audioinputpin=3;

// Statuses
long cur=0;
int avgmax=0;
long smooth=0;
long expo=0;
int topbar=0;
int ledcount=0;
int dim;
byte maxbr=0;

// Cycle stuff
boolean cyclecolors=true;
int curcyclecolor=0;
int curcyclecolortemp1=0;
int curcyclecolortemp2=0;
int cyclered=0;
int cyclegreen=0;
int cycleblue=0;
long cycleinterval=16;
long lightfade=56;
long strongfade=170;

// Blip stuff
int curblipnumber=0;
byte curblipbrightness=0;
int curblipdir=0;
boolean curblipchange=false;
int blipcount=1;
int bliparray[]={
  0,0,0,0,0,0};
struct Pixel curblipcolor=BlackPixel;

// Timers
long smoothmil=0;
long ledmil=0;
long maxavgmil=0;
long topbarmil=0;
long cyclemil=0;
long maxbrmil=0;

int curmaxcounter=0;
int maxes[]={
  0,0,0,0,0,0,0,0,0,0};
//int tempmax=0;

// COLOR THEMES ******************************************************* 

struct PixelStream VUThemes[]={ // do not edit existing ones, only add new ones at the end
  {
    GreenPixel,GreenPixel,GreenPixel,GreenPixel,OrangePixel,RedPixel
  }
  ,
  {
    BluePixel,CyanPixel,GreenPixel,YellowPixel,RedPixel,MagentaPixel
  }
  ,
  { // WHY U NO WORK???
    GreenPixel,
    {
      64, 204,0    }
    ,
    {
      128,153,0    }
    ,
    {
      192,102,0    }
    ,
    {
      255,51, 0    }
    ,
    RedPixel
  }
  ,
  BlackPixelStream // all same

  ,
  BlackPixelStream // light fade
  ,
  BlackPixelStream // strong fade
  ,
  WhitePixelStream
};



/////////////////////////////////////////////////////////////////////

void setup()
{
  Tlc.init();
  delay(500);
  //randomSeed(millis());
  //  WireSetup_MAX6956_4bit();
  Serial.begin(19200);
  toSend=WhitePixelStream;
  WriteColors();
  delay(500);
  toSend=BlackPixelStream;
  WriteColors();
}

void loop()
{
  byte RemoteCommand=GetRemote();
  switch(RemoteCommand) {
  case RemotePLAY: 
    PoweredOn=!PoweredOn;
    //    if(!PoweredOn) {
    //      toSend=BlackPixelStream;
    //      WriteColors();
    //      delay(1000);
    //    }
    break;
  case RemoteFWD: 
    if(++CurrentMode>=6)
      CurrentMode=0;
    //    NewModeTimer=millis();
    maxbr=0;
    break;
  case RemoteREV: 
    if(--CurrentMode<0)
      CurrentMode=5;
    //    NewModeTimer=millis();
    maxbr=0;
    break;
  case RemoteVUP:
    switch(CurrentMode) {
    case 0:
    case 3:
    case 4:
    case 5:
      if(++CurrentTheme>=sizeof(VUThemes)/18)
        CurrentTheme=0;
      break;
    case 1:
      cyclecolors=!cyclecolors;
      break;
    case 2:
      if(cycleinterval>1)
        cycleinterval/=2;
      break;


      break;
    }
    break;
  case RemoteVDN:
    switch(CurrentMode) {
    case 0:
    case 3:
    case 4:
    case 5:
      if(--CurrentTheme<0)
        CurrentTheme=sizeof(VUThemes)/18-1;
      break;
    case 1:
      cyclecolors=!cyclecolors;
      break;
    case 2:
      cycleinterval*=2;
      break;

      break;
    }
    break;
  }

  if(millis()-NewModeTimer<=100) {
    toSend=BlackPixelStream;
    toSend.pixels[CurrentMode]=WhitePixel;
  } 

  else {
    if(cyclecolors) ColorCycle(); 
    switch(CurrentMode) {
    case 0:
      mode0();
      break;
    case 1: 
      mode1();
      break;
    case 2: 
      mode2();
      break;
    case 3: 
      mode3();
      break;
    case 4: 
      mode4();
      break;
    case 5: 
      mode5();
      break;
    }
  }

  //  if(PoweredOn && millis()-writemil>50) {
  if(millis()-writemil>50) {
    WriteColors();
    writemil=millis();
  }

  if(millis()-maxbrmil>1) {
    if(PoweredOn) {
      if(maxbr<128)
        maxbr++;
    } 
    else {
      if(maxbr>0)
        maxbr-=2;
    }
    maxbrmil=millis();
  }
}

void h2rgb(float H, int& R, int& G, int& B) {

  H/=1024;
  int var_i;
  float S=1, V=1, var_1, var_2, var_3, var_h, var_r, var_g, var_b;

  if ( S == 0 )                       //HSV values = 0 ÷ 1
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if ( var_h == 6 ) var_h = 0;      //H must be < 1
    var_i = int( var_h ) ;            //Or ... var_i = floor( var_h )
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    if      ( var_i == 0 ) {
      var_r = V     ;
      var_g = var_3 ;
      var_b = var_1 ;
    }
    else if ( var_i == 1 ) {
      var_r = var_2 ;
      var_g = V     ;
      var_b = var_1 ;
    }
    else if ( var_i == 2 ) {
      var_r = var_1 ;
      var_g = V     ;
      var_b = var_3 ;
    }
    else if ( var_i == 3 ) {
      var_r = var_1 ;
      var_g = var_2 ;
      var_b = V     ;
    }
    else if ( var_i == 4 ) {
      var_r = var_3 ;
      var_g = var_1 ;
      var_b = V     ;
    }
    else                   {
      var_r = V     ;
      var_g = var_1 ;
      var_b = var_2 ;
    }

    R = (1-var_r) * 255;                  //RGB results = 0 ÷ 255
    G = (1-var_g) * 255;
    B = (1-var_b) * 255;
  }
}

void ColorCycle() {
  // CYCLE MODE

  /*
  if(millis()-cyclemil>5000) {
   Pixel temp=VUThemes[1].pixels[5];
   for(i=5;i>=1;i--) {
   VUThemes[1].pixels[i]=VUThemes[1].pixels[i-1];
   }
   VUThemes[1].pixels[0]=temp;
   cyclemil=millis();
   }
   // */
  ///*
  if(millis()-cyclemil>cycleinterval&&CurrentMode!=4) {
    if(++curcyclecolor>=1024)
      curcyclecolor-=1024;
    curcyclecolortemp1=curcyclecolor;
    curcyclecolortemp2=curcyclecolor;
    //    for(i=0;i<=5;i++) {
    for(i=5;i>=0;i--) {
      if(curcyclecolortemp1>=1024)
        curcyclecolortemp1-=1024;
      if(curcyclecolortemp2>=1024)
        curcyclecolortemp2-=1024;
      h2rgb(curcyclecolortemp1,cyclered,cyclegreen,cycleblue);
      cyclered=(int)((long)(cyclered*cyclered/255));
      cyclegreen=(int)((long)(cyclegreen*cyclegreen/255));
      cycleblue=(int)((long)(cycleblue*cycleblue/255));
      VUThemes[4].pixels[i].red=cyclered;
      VUThemes[4].pixels[i].green=cyclegreen;
      VUThemes[4].pixels[i].blue=cycleblue;
      h2rgb(curcyclecolortemp2,cyclered,cyclegreen,cycleblue);
      cyclered=(int)((long)(cyclered*cyclered/255));
      cyclegreen=(int)((long)(cyclegreen*cyclegreen/255));
      cycleblue=(int)((long)(cycleblue*cycleblue/255));
      VUThemes[5].pixels[i].red=cyclered;
      VUThemes[5].pixels[i].green=cyclegreen;
      VUThemes[5].pixels[i].blue=cycleblue;
      VUThemes[3].pixels[i]=VUThemes[4].pixels[0];
      curcyclecolortemp1+= lightfade; //50; //analogRead(0); //50;
      curcyclecolortemp2+= strongfade; //50; //analogRead(0); //50;
    }
    cyclemil=millis();
  }
  // */
}

void WriteColors() {
  //WriteColors_MAX6956_4bit();
  WriteColors_TLC5941();
}  

struct Pixel testfkt() {
  struct Pixel bla={
    0,0,0
  };
  return  bla;
}







