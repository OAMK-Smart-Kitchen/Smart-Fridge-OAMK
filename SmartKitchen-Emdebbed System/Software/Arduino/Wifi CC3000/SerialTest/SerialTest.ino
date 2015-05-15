char incommingByte;
String incommingString;
char charArray[150];

bool initComplete = false;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
  if (Serial1.available())
  {
    incommingByte = Serial1.read();
    
    incommingString.concat(incommingByte);
    incommingString.toCharArray(charArray,150);
  }
  
  if (!initComplete)
  {
    CheckInit();
  }
  else
  {
     Serial.println(GetId()); 
  }
}

void CheckInit()
{
  int count = 0;
  for(int i = 0; i < sizeof(charArray); i++)
  {
    if(charArray[i] == 'X')
    {
      count++;
    }     
  } 
  if(count >= 2)
  {
    initComplete = true;
  }
}

String GetId()
{
  return GetContentByFilterOn('D');
}
String GetAddress()
{
  return GetContentByFilterOn('A');
}
String GetAvailability()
{
  return GetContentByFilterOn('B');
}

String GetContentByFilterOn(char filter)
{
  bool readd = false;
  bool stopread = false;
  String content = "";
  for(int i = 0; i < sizeof(charArray); i++)
  {      
    if (stopread)
    {
      return content;
    }
    
    if(readd)
    {
      if(charArray[i] != filter)
      {
          content.concat(charArray[i]);
      }
    }
    
    if(charArray[i] == filter)
    {
      readd = !readd;
      if(readd == false)
      {
        stopread = true;
      }
    }
  }
}

