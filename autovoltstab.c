
#define     relay1          RC1_bit
#define     relay2          RC2_bit
#define     relay3          RC3_bit
#define     relay4          RC4_bit
#define     relay5          RC5_bit

#define     delay_led       RA2_bit
#define     high_led        RA1_bit
#define     low_led         RA0_bit


unsigned int line_voltage=0,max_point=0,temp=0;
int i=0,k=0;
bit gap1,gap2,gap3,gap4,gap5;



void main()
{
  TRISA=0x00;//all output
  TRISC=0x01;//all out except RC0_bit
  ANSEL = 0b00010000;//AN4 active
  CMCON=0x07;//comparator off
  ADCON1=0x10;//Fosc/8 speed

  top:
  PORTA = 0x00;//clear port
  PORTC = 0x00;//clear port
  delay_led = 1;
  Delay_ms(5000);
  delay_led = 0;

  while(1)
  {

     //read input voltage
     line_voltage = 0;
     max_point=0;
     temp=0;
     ADCON0 = 0x11; //AN4
     for(i=0;i<5;i++)
     {
         for(k=0;k<500;k++)
         {
            if(temp=ADC_Read(4),temp>max_point)
            {
               max_point = temp;
               Delay_us(1);
            }
         }
         line_voltage+=max_point*37/10;
     }
     line_voltage/=5; //get average value


     if(line_voltage<145 || line_voltage>305)
     {
        relay5 = 0;
        if(line_voltage<145)low_led = 1;
        else if(line_voltage>305)high_led = 1;
        Delay_ms(10000);//wait 10sec
        goto top;
     }
     else
     {
        if(line_voltage>145 && line_voltage<170)
        {
           relay1 = 0;// 150V Tap connected
           relay2 = 0;
           relay3 = 0;
           relay4 = 0;
           relay5 = 1;//injection on
           gap1 = 1;
           gap2 = 0;
        }
        else if(line_voltage>=170 && line_voltage<=172)
        {
           if(gap1)
           {
             relay1 = 0;// 150V Tap connected
             relay2 = 0;
             relay3 = 0;
             relay4 = 0;
             relay5 = 1;//injection on
           }
           if(gap2)
           {
             relay1 = 1;// 180V Tap connected
             relay2 = 0;
             relay3 = 0;
             relay4 = 0;
             relay5 = 1;//injection on
           }
        }
        else if(line_voltage>172 && line_voltage<204)
        {
           relay1 = 1;// 180V Tap connected
           relay2 = 0;
           relay3 = 0;
           relay4 = 0;
           relay5 = 1;//injection on
           gap2 = 1;
           gap1 = 0;
           gap3 = 0;
        }
        else if(line_voltage>=204 && line_voltage<=206)
        {
           if(gap2)
           {
             relay1 = 1;// 180V Tap connected
             relay2 = 0;
             relay3 = 0;
             relay4 = 0;
             relay5 = 1;//injection on
           }
           if(gap3)
           {
             relay1 = 0;
             relay2 = 1;// 210V Tap connected
             relay3 = 0;
             relay4 = 0;
             relay5 = 1;//injection on
           }
        }
        else if(line_voltage>206 && line_voltage<238)
        {
           relay1 = 0;
           relay2 = 1;// 210V Tap connected
           relay3 = 0;
           relay4 = 0;
           relay5 = 1;//injection on
           gap3 = 1;
           gap4 = 0;
           gap2 = 0;
        }
        else if(line_voltage>=238 && line_voltage<=240)
        {
           if(gap3)
           {
             relay1 = 0;
             relay2 = 1;// 210V Tap connected
             relay3 = 0;
             relay4 = 0;
             relay5 = 1;//injection on
           }
           if(gap4)
           {
             relay1 = 0;
             relay2 = 0;
             relay3 = 1;// 240V Tap connected
             relay4 = 0;
             relay5 = 1;//injection on
           }
        }
        else if(line_voltage>240 && line_voltage<270)
        {
           relay1 = 0;
           relay2 = 0;
           relay3 = 1;// 240V Tap connected
           relay4 = 0;
           relay5 = 1;//injection on
           gap3 = 0;
           gap4 = 1;
           gap2 = 0;
        }
        else if(line_voltage>=270 && line_voltage<=272)
        {
           if(gap4)
           {
             relay1 = 0;
             relay2 = 0;
             relay3 = 1;// 240V Tap connected
             relay4 = 0;
             relay5 = 1;//injection on
           }
           if(gap5)
           {
             relay1 = 0;
             relay2 = 0;
             relay3 = 0;
             relay4 = 1;//270V Tap connected
             relay5 = 1;//injection on
           }
        }
        else if(line_voltage>272 && line_voltage<305)
        {
           relay1 = 0;
           relay2 = 0;
           relay3 = 0;
           relay4 = 1;// 270V Tap connected
           relay5 = 1;//injection on
           gap4 = 0;
           gap5 = 1;
        }
     }



  }//while(1)
}//void main()