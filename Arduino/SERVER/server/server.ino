#include <SoftwareSerial.h>
#include <String.h>
#include <stdlib.h>

SoftwareSerial btSerial(12,11);
char a[15];
char b[15];
char c[5];
char t;
int tmp1,tmp2;
int i;
int state;
int te=0,hu=0,in=0,out=0,rain=0;
int cnt1=0,cnt2=0;
char indust[10];
char temp[10];
char humid[10];
char outdust[10];
char rainst[10];
char winst[1]="0",airst[1]="0";
int autorun = 0 ; //0 일때 자동 1일때 수동
int ok=0;
int num;
int change(int i,char ha[])
{
  int sum;
  int ten=1;
  for(int j=1;j<=i;j++)
  {
    sum+=(((int)ha[i-j])-48)*ten;
    ten*=10;
  }
  return sum;
}
void setup() {

  Serial.begin(9600);
  btSerial.begin(9600);
  // put your setup code here, to run once:

}



void loop() {
  if(Serial.available())
  {
  
 for(i=0;i<15;i++)
 {
  a[i] =Serial.read();
  //Serial.print(a[i]);
 if(a[i]=='*') 
 {
  break;
  }
 //Serial.println();

 }
 strcpy(b,a);
 //Serial.print("dust!!!!===>");
 //Serial.print(b);
 

 
  if(a[i-12]=='$'&&cnt1==0)
  {
   char *ptr= strtok(b,","); 
   ptr=strtok(NULL,","); 
    strcpy(indust,ptr);
 
   
// Serial.print("dust!!!!===>");
  //  Serial.println(indust);
    ptr=strtok(NULL,",");
    strcpy(humid,ptr);
   //  Serial.println(humid);
    ptr=strtok(NULL,",");
    strcpy(temp,ptr);
   //  Serial.println(temp);
    ptr=strtok(NULL,",");
   cnt1++;
  }
  if(a[i-8]=='@'&&cnt2==0)
  {
    char *pta= strtok(b,",");
    pta=strtok(NULL,","); 
    strcpy(outdust,pta);
 //Serial.print("ddddust!!!!===>");
  //  Serial.println(outdust);
    pta=strtok(NULL,",");
    strcpy(rainst,pta);
   //  Serial.println(rainst);
    pta=strtok(NULL,",");
     
   cnt2++; 
 // Serial.print(a[i-6]);
  }


  if(cnt1==1||cnt2==1)
  { 
   /* for(int j=0;j<13;j++)
    {
      num=b[j];
      if(num<58&&num>47)
      {
      ok=1;  
      }
      else
      {
        ok=0; break;
      }
     
    }
     if(ok==1)
      { 
        for(int j=0;j<13;j++)
        {
          btSerial.write(b[j]);
        }
        
      }
      
    btSerial.write(indust[0]);
    btSerial.write(indust[1]);
    btSerial.write(indust[2]);
    btSerial.write(humid[0]);
    btSerial.write(humid[1]);
    btSerial.write(temp[0]);
    btSerial.write(temp[1]);
    btSerial.write(outdust[0]);
    btSerial.write(outdust[1]);
    btSerial.write(outdust[2]);
    btSerial.write(rainst[0]);
    btSerial.write(winst[0]);
    btSerial.write(airst[0]);
  */
   btSerial.write(indust);
    btSerial.write(humid);
    btSerial.write(temp);
    btSerial.write(outdust);
    btSerial.write(rainst);
  
   
    
  
  
    cnt1=0;
    cnt2=0;  
/*
   Serial.print("dust");
   Serial.print(indust);

   Serial.print("hu");
   Serial.print(humid);
   Serial.print("temp");
   Serial.print(temp);

   Serial.print("out");
   Serial.println(outdust);
   Serial.print("rain");
 */
  

     Serial.println("전송");
  }
  
 }

 /*
  if(btSerial.available())
   btSerial.write(Serial.read());
*/
 delay(1000);



in=atoi(indust);
hu=atoi(humid);
te=atoi(temp);
out=atoi(outdust);
rain=atoi(rainst);
/*
Serial.println(in);
Serial.println(te);
Serial.println(hu);
Serial.println(out);

Serial.println(rain);
*/
Serial.println("이후로 제어데이터");


 if(btSerial.available())
 {
  t=btSerial.read();
  Serial.print(t);
 }
  if(t=='5') //수동화
  {
    autorun=1;
  }
  else if(t=='6')//자동화
  {
    autorun=0;
  }
  if(autorun==0)
  {
    if(te>50)
    {
      Serial.println("3");
      Serial.println("화재");
   
    }
    else
    {
      if(rain==1) //비가 안오고 있는중
      {
        if(out>75)//창문이 닫힐때
        {
          Serial.println("4");
          if(te>26||in>65)
          {
            Serial.println("1");
            Serial.println("외부상태별로");
          }
        }
        else //창문이 열릴때
        {
            Serial.println("2");
            
            if(te>26||in>=60)
            {
            Serial.println("3");
            Serial.println("공기정화");
            }
            else if(te<11)
            {
            Serial.println("4");
     
            }
        }
      }
      else if(rain==0)
      {
        Serial.println("4");
       
        delay(1000);
        if(hu>65||te>26||in>65)
        {
          Serial.println("1");
        }
      }
    }
    
  }
  else if(autorun==1)
{
  if(t=="1")
  {
 
    Serial.println("1");
    
  }
  else if(t=="2")
  {

    Serial.println("2");
    
  }
  if(t=="3")
  {
    Serial.println("3");
    
  }
  else if(t=="4")
  {
    Serial.println("4");
    
  }
}
 
  // put your main code here, to run repeatedly:
  }
