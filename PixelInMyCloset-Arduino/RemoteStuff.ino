
byte GetRemote() {
  byte RemoteString[7] = {
    0,0,0,0,0,0,0        };
  while(Serial.available()>=7) {
    for(i=0;i<7;i++) {
      RemoteString[i]=Serial.read();
    }

    if(RemoteString[5]!=0x00) {
      RemoteLastCommand=RemoteString[5];
    } 
    else {
      return RemoteLastCommand;
    }
  }
  return 0x00;
}


