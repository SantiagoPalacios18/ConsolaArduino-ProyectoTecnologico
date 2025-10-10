#include <Adafruit_ILI9341.h>
#include <SPI.h>

const int CSv = 45;
const int RSTv = 47;
const int DCv = 49;
const int MOSIv = 51;
const int SCKv = 52;
const int MISOv = 50;

#define TFT_CS CSv
#define TFT_DC DCv
#define TFT_RST RSTv

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  tft.begin();             // Inicializar pantalla
  tft.setRotation(3);      // Ajusta la rotación (0-3)
  tft.fillScreen(ILI9341_BLACK);  // Limpiar pantalla con negro

  // Mostrar texto simple
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(10, 10);
  tft.println("Hola TFT 2.8\"");
  
  // Dibujar un rectángulo rojo
  tft.fillRect(50, 50, 100, 50, ILI9341_YELLOW);

  // Dibujar un círculo azul
  tft.fillCircle(150, 150, 40, ILI9341_BLUE);
}


void loop() {
  // put your main code here, to run repeatedly:

}