//Copyright-2022 CECAR MOISES CANARIA
#define __DEBUG__ //Debug
#include <SPI.h> //libreria
#include <Wire.h> //libreria
#include <Adafruit_GFX.h> //libreria
#include <Adafruit_SSD1306.h> //libreria
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 64 // alto pantalla OLED
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1); // Objeto de la clase Adafruit_SSD1306
const unsigned char carita_feliz [] PROGMEM = { // 'imagen carita-feliz', 32x32px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
  0x00, 0x3f, 0xfc, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 
  0x01, 0xff, 0xff, 0x80, 0x01, 0xc3, 0xc3, 0x80, 0x01, 0xc1, 0x83, 0x80, 0x01, 0xdd, 0xbb, 0x80, 
  0x01, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0x80, 0x01, 0xef, 0xf7, 0x80, 
  0x00, 0xe3, 0xc7, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x7e, 0x7e, 0x00, 0x00, 0x3f, 0xfc, 0x00, 
  0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
//Variables
int contador = 0; //Contador para lunes a viernes
int contador2 = 0; //Contador para Sabado y domingo
int semana = 0;  // Identificar si es  lunes a viernes
void setup() { 
   Serial.begin(9600); //Permite imprimir en el puerto serial
   pinMode(12, OUTPUT); //Pin 12 para el sonido cuando hay un ganador
   pinMode(33, 1); // pin 33 suma el numero numero de clientes el contador
   pinMode(32, 1); // pin 32 para establecer lunes a viernes y sabado y domingo
  #ifdef __DEBUG__
  delay(100); //Tiempo de espera
  Serial.println("Iniciando pantalla OLED"); //imprime en el puerto serial
#endif
  // Iniciar pantalla OLED en la dirección 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //Verifica la conexion del LCD
#ifdef __DEBUG__
    Serial.println("No se encuentra la pantalla OLED"); //imprime en el puerto serial
#endif
    while (true);
  }
  display.clearDisplay(); //Limpia el buffer
  display.setTextSize(2);
  display.setTextWrap(false);
  display.setTextColor(BLACK,WHITE); //Color por defecto para imprimir en el display
  display.setCursor(0, 0); // posicion
  display.println("BIENVENIDO  ");
  display.setTextColor(WHITE);//Color por defecto para imprimir en el display
  display.setTextSize(1);
  display.setTextWrap(true);
  display.setCursor(0, 30); // posicion
  display.println("Donde podras ganar un bono del 50% de tu compra (L a V)y(S y D)");
  display.setCursor(10, 20); // posicion
  display.setTextColor(BLACK,WHITE);//Color por defecto para imprimir en el display
  display.print("Alkosto y Ktronix");
   // Scroll in various directions, pausing in-between: 
  display.startscrollright(0x00, 0x01);
  display.setTextColor(WHITE); //Color por defecto para imprimir en el display
  display.setTextSize(1);  //Tamaño del texto a imprimir en el display
  display.setTextColor(WHITE);//Color por defecto para imprimir en el display
  delay(2000); 
  display.display(); 
}
void loop() {
    display.clearDisplay(); //limpia el buffer
    int punto = digitalRead(32);
    int dia = digitalRead(33);
    if (dia == 0) {
        semana = 0;      
        contador2=0;
        if (punto == 1 && semana == 0 ) {
             display.stopscroll();
            contador++;          
            if (contador %5== 0) {
                //   contador=0; 
               display.drawBitmap(100, 30, carita_feliz, 32,32, 1); //Imprime imagen temperatura  
               display.setTextColor(BLACK,WHITE); //Color por defecto para imprimir en el display 
               display.setCursor(0, 20);// Posición del texto   
               Serial.println(""); //Imprime imagen temperatura
               Serial.println("Cliente #5 rres el feliz ganador de un bono del 50% tu compra");//Imprime imagen temperatura 
               display.println("Eres el feliz ganador");//Imprime imagen temperatura 
               display.println("de un bono del 50%"); //Imprime imagen temperatura
               display.println("tu compra"); //Imprime imagen temperatura              
               digitalWrite(12, 1);
                 tone(12, 200, 3000);  //Tono para el sonido en el pin 12                           
                
            }
            Serial.print("Lunes a viernes ");//Imprime imagen temperatura
            Serial.print(contador);  //Imprime imagen temperatura         
            Serial.println(""); //Imprime imagen temperatura           
              display.setTextSize(2);
               // Color del texto
              display.setTextColor(SSD1306_WHITE); //Color por defecto para imprimir en el display
              display.setCursor(0, 0); // Posición del texto                                    
             display.println("Cliente: ");    // Escribir texto  
             display.setCursor(92, 0); // Posición del texto
             display.print(contador);    // Escribir texto  
             display.setCursor(10, 47); // Posición del texto
             display.setTextSize(1); //Tamaño texto en el display                         
             display.println("Lunes a viernes ");  //imprimir en el display                
             // Enviar a pantalla
            display.display(); //Permite imprimir en el display
            delay(200); //Tiempo de espera 
            //Valida que al dejar precionado el boton no sume infinitamente
            while (digitalRead(33) == 1) {}
            while (digitalRead(32) == 1) {}                       
        }
    } else {    
        semana = 1;  
           contador=0;       
        if (semana == 1) {                                                                                
                if (dia == 1 && punto == 1) {  
                  display.stopscroll(); //Detiene el scroll             
                       contador2++; //Contador para Sabado y domingo                
                    if (contador2 %10== 0) { //Si el contador es estrictamente 10 hay un ganador
                        //   contador=0;   
                  display.drawBitmap(100, 30, carita_feliz, 32,32, 1); //Imprime imagen cara feliz  
                  display.setTextColor(BLACK,WHITE); 
                  display.setCursor(0, 20);  // Posición del texto 
                  display.println("Eres el feliz ganador"); // Escribir texto 
                  display.println("de un bono del 50%"); // Escribir texto 
                  display.println("tu compra");// Escribir texto 
                  Serial.println(""); // Escribir texto   
                  Serial.println("Cliente #10 eres el feliz ganador de un bono del 50% tu compra");   // Escribir texto                  
                 digitalWrite(12, 1);
                 tone(12, 200, 3000);   //Tono para el sonido en el pin 12 
                                            
                    }
        
                    Serial.print("Sabado y domingo ");//Imprime imagen carita feliz
                    Serial.print(contador2);// Escribir texto 
                    delay(200);
                    Serial.println("");// Escribir texto 
                    display.setTextSize(2);
                    // Color del texto
                    display.setTextColor(SSD1306_WHITE);
                    // Posición del texto
                    display.setCursor(0, 0); // Posición del texto
                    // Escribir texto                                  
                    display.println("Cliente: ");
                    display.setCursor(92, 0);// Posición del texto
                    // Escribir texto
                    display.print(contador2); 
                    display.setCursor(8, 47);// Posición del texto
                    display.setTextSize(1);   //tamaño del texto                       
                    display.println("Sabado y domingo");   // Escribir texto                
                    // Enviar a pantalla
                    display.display();
                      //Valida que al dejar precionado el boton no sume infinitamente
                    while (digitalRead(32) == 1) {} 
                    while (digitalRead(33) == 2) {}
                    display.clearDisplay();  //limpia el buffer 
                }
               }  
                 if (contador2 == 0 && dia ==1){ //Espera a que el contador2 sea 1
                      display.stopscroll();  //tamaño del texto           
                      display.setTextSize(1);//tamaño del texto                   
                      display.drawBitmap(50, -8, carita_feliz, 32,32, 1); //Imprime imagen carita feliz 
                      display.setCursor(0, 25); // Posición del texto
                      display.println("Sabado y Domingo"); 
                      display.println("puedes ganar un bono del 50% de tu compra");         
                     display.display();             
          }
       }
    }
 

  
