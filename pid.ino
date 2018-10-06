//Bhushan Patil PID

int leftir=10,rightir=12,centerir=11,forwardir=13, backir=9;  //sensors
int a[5]={0};
double kp,ki,kd,change; //pid
int p,i=0,d,error,pprev=0;  //pid
unsigned long lasttime,now; //time
double dt;    //pid

const int maxspeed=255;

int rightmotorspeed=255,leftmotorspeed=255;
int rightforward=5   , leftforward=2,rightback=4 ,leftback=3;
int rightenable=6,leftenable=7;

void setup()
{
    pinMode(leftir,INPUT);
    pinMode(rightir,INPUT);
    pinMode(centerir,INPUT);
    pinMode(forwardir,INPUT);
    pinMode(backir,INPUT);
    pinMode(rightforward,OUTPUT);
    pinMode(leftforward,OUTPUT);
    pinMode(rightback,OUTPUT);
    pinMode(leftback,OUTPUT);
    pinMode(rightenable,OUTPUT);
    pinMode(leftenable,OUTPUT);
    analogWrite(leftenable,255);
    analogWrite(rightenable,255);
    digitalWrite(rightforward,HIGH);
    digitalWrite(leftforward,HIGH);
    digitalWrite(rightback,LOW);
    digitalWrite(leftback,LOW);
    Serial.begin(9600);
}

void loop()
{
    double motorvd= pid();
    if((leftmotorspeed-motorvd)<=255 && !((leftmotorspeed-motorvd)<0))
    {
      analogWrite(leftenable,leftmotorspeed-motorvd);
      Serial.print("left motor:");
      Serial.print(leftmotorspeed-motorvd);
    }
    else if(leftmotorspeed-motorvd<0)
    {
      leftmotorspeed=0;
      analogWrite(leftenable,leftmotorspeed);
      Serial.print("left motor:");
      Serial.print(leftmotorspeed);
    }
    else
    {
      leftmotorspeed=255;
      analogWrite(leftenable,leftmotorspeed);
      Serial.print("left motor:");
      Serial.print(leftmotorspeed);
    }
    if(rightmotorspeed+motorvd<=255 && !((rightmotorspeed+motorvd)<0))
    {
      analogWrite(rightenable,rightmotorspeed+motorvd);
      Serial.print("right motor:");
      Serial.print(rightmotorspeed+motorvd);
    }
    else if(rightmotorspeed+motorvd<=0)
    {
      rightmotorspeed=0;
      analogWrite(rightenable,rightmotorspeed);
      Serial.print("right motor:");
      Serial.print(rightmotorspeed);
    }
    else
    {
      rightmotorspeed=255;
      analogWrite(rightenable,rightmotorspeed);
      Serial.print("right motor:");
      Serial.print(rightmotorspeed);
    }
    Serial.print("\n");
     delay(50);
}

double pid()
{
    now=millis();
    dt=(double)(now-lasttime);
    error=sensorread();
    p=error;
    i=(i+p)/*dt*/;
    d=(p-pprev)/*dt*/;
    pprev=p;
    kp=150;
    ki=10;
    kd=150;
    change=kp*p+ki*i+kd*d;
    lasttime=now;
    return change;
}

int overturn=0;
int sensorread()
{
    a[0]=digitalRead(leftir);
    a[1]=digitalRead(rightir);
    a[2]=digitalRead(centerir);
    a[3]=digitalRead(forwardir);
    a[4]=digitalRead(backir);
    
    if(a[2]==1)
    {
        overturn=0;
        leftmotorspeed=255;
        rightmotorspeed=255;
        i=0;
        return 0;  //center
    }
    else if(a[0]==1)
    {
        overturn=2;
        return 1; //left;
    }
    else if(a[1]==1)
    {
        overturn=-2;
        return - 1;  //right;
    }
    else if(a[2]==1)
    {
        overturn=0;
        leftmotorspeed=255;
        rightmotorspeed=255;
        i=0;
        return 0;  //center
    }
    else
    {
         return overturn;
    }
    return 0;
}
