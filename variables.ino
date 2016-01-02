void updVar() {

  if (reqHeat == true) {
    OnTime = motorStart * egyezer;
    OffTime = motorStop * egyezer;
  } else {
    OnTime = motorStart2 * egyezer;
    OffTime = motorStop2 * hatvanezer;   //ez percben van
  }
}

