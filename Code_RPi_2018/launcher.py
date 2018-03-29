import time
import serial
import os
import RPi.GPIO as GPIO
import I2C_LCD_driver
mylcd = I2C_LCD_driver.lcd()

def readAndSave(n):
    print "usart running"
    mylcd.lcd_display_string("Eco-Marathon    ", 1)
    mylcd.lcd_display_string("Mesure"+str(n), 2)
    path="/home/pi/Desktop/mesures"+str(n)+".csv"
    f = open(path,"w")
    port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)
    run=True
    GPIO.output(4,True)
    f.write("nouvelles mesures\n")
    while(run):
        recv= port.read(13)
        f.write(recv)
        print recv
        if (GPIO.input(5)==0):
            run=False
    f.close
    port.close()
    while (GPIO.input(5)==0):
        time.sleep(0.1)
    print "usart off"
    return

# Our function on what to do when the button is pressed
def Shutdown():
    mylcd.lcd_display_string("RPi Shutdown    ", 1)
    mylcd.lcd_display_string("                ", 2)
    time.sleep(2)
    mylcd.lcd_clear()
    os.system("sudo shutdown -h now")


def main():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(5,GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(4,GPIO.OUT)
    GPIO.setup(6,GPIO.IN, pull_up_down=GPIO.PUD_UP)

    n=1

    while True:
        if (GPIO.input(6)==0):
	    while (GPIO.input(6)==0):
                  time.sleep(0.1)
            Shutdown()
        GPIO.output(4,True)
        mylcd.lcd_display_string("Eco-Marathon2018", 1)
        mylcd.lcd_display_string("                ", 2)
       	if (GPIO.input(5)==0):     
            while (GPIO.input(5)==0):
          	  time.sleep(0.1)
            readAndSave(n)
            n=n+1
            print n
        time.sleep(0.25)
        GPIO.output(4,False)
        time.sleep(0.25)
    return

main()
        
