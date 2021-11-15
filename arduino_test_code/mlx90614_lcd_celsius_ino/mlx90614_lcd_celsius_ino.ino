

#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define I2C_ADDR 0x27 



Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  
  mlx.begin();

  Serial.begin(9600);
  Serial.print("AESD TEMPERATURE SENSOR TEST\n");

}

void loop() {

 Serial.print("Ambient\n");
 Serial.print(mlx.readAmbientTempC());
 Serial.print(" C\n");
 

 Serial.print("Target\n");
 Serial.print(mlx.readObjectTempC());
 Serial.print(" C\n");

 delay(1000);

}
