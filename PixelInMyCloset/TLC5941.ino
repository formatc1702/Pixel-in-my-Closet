void WriteColors_TLC5941() {
  Tlc.clear();
  
  Tlc.set(5,maxbr*(int)toSend.pixels[0].red/8);
  Tlc.set(3,maxbr*(int)toSend.pixels[0].green/8);
  Tlc.set(1,maxbr*(int)toSend.pixels[0].blue/8);

  Tlc.set(13,maxbr*(int)toSend.pixels[1].red/8);
  Tlc.set(11,maxbr*(int)toSend.pixels[1].green/8);
  Tlc.set(9,maxbr*(int)toSend.pixels[1].blue/8);

  Tlc.set(21,maxbr*(int)toSend.pixels[2].red/8);
  Tlc.set(19,maxbr*(int)toSend.pixels[2].green/8);
  Tlc.set(17,maxbr*(int)toSend.pixels[2].blue/8);

  Tlc.set(28,maxbr*(int)toSend.pixels[3].red/8);
  Tlc.set(26,maxbr*(int)toSend.pixels[3].green/8);
  Tlc.set(24,maxbr*(int)toSend.pixels[3].blue/8);

  Tlc.set(37,maxbr*(int)toSend.pixels[4].red/8);
  Tlc.set(35,maxbr*(int)toSend.pixels[4].green/8);
  Tlc.set(33,maxbr*(int)toSend.pixels[4].blue/8);

  Tlc.set(45,maxbr*(int)toSend.pixels[5].red/8);
  Tlc.set(43,maxbr*(int)toSend.pixels[5].green/8);
  Tlc.set(41,maxbr*(int)toSend.pixels[5].blue/8);
  
  Tlc.update();
  
//  Serial.println(toSend.pixels[0].red,DEC);
//  Serial.println(dim*toSend.pixels[0].red,DEC);
//  Serial.println(dim,DEC);
//  Serial.println();
} 
