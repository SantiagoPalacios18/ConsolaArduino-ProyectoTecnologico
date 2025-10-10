#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Keypad.h>

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

//Bitmaps - Organizados en Spritesheets para animaciones
// Definimos el número de filas y columnas del keypad
const byte ROWS = 4;
const byte COLS = 4;

// Definimos las teclas en una matriz
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Pines del Arduino conectados al teclado
byte rowPins[ROWS] = {3, 4, 5, 6};  
byte colPins[COLS] = {7, 8, 9 ,10};  

byte passwordGame[3]; 
byte passwordPlayer[3]; 
int indexGame = 0; 
int indexPlayer = 0;
String userName = "";

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);



//Animaciones


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

  randomSeed(analogRead(A0)); // Semilla aleatoria unica
  Serial.println("Bienvenido a nuestro proyecto! Ingrese su nombre de usuario:");
  
  while (userName.length() == 0) {
    if (Serial.available() > 0) {
      userName = Serial.readStringUntil('\n'); // Lee hasta que el usuario presione Enter
      userName.trim(); // Quita espacios al inicio o final
    }
  }
  Serial.print("Nombre Ingresado:");
  Serial.println(userName);
}


void loop() {
  if (indexGame < 20) {
    passwordGame[indexGame] = random(1, 10); // Guarda número aleatorio (1-9)
    Serial.print("Numero agregado: ");
    Serial.println(passwordGame[indexGame]);
    indexGame++;
  }

  // MOSTRAR CLAVE GENERADA
  Serial.print("Clave: ");
  for (int i = 0; i < indexGame; i++) {
    Serial.print(passwordGame[i]);
    Serial.print(" ");
  }
  Serial.println("\n----------");

  // JUGADOR INTENTA REPLICAR CLAVE
  indexPlayer = 0;
  while (indexPlayer < indexGame) {
    char key = keypad.getKey(); 
    if (key) {
      passwordPlayer[indexPlayer] = String(key).toInt(); // convierte char '3' → int 3
      Serial.print("Tecla elegida: ");
      Serial.println(passwordPlayer[indexPlayer]);
      indexPlayer++;
    }
  }

  // Comparación
  bool RondaPasada = true;
  for (int i = 0; i < indexGame; i++) {
    if (passwordGame[i] != passwordPlayer[i]) {
      RondaPasada = false;
      break;
    }
  }

  if (RondaPasada) {
    Serial.println("GG, pasaste la ronda!");
  } else {
    Serial.println("Fallaste! Buena suerte la prox.");
    while (1); // detener el juego
  }

  delay(1000);

}