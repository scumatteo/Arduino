#define PIN_A 12 //pin del led del giocatore A
#define PIN_B 10 //pin del led del giocatore B
#define PIN_MIDDLE 11 //pin del led centrale
#define BUTTON_A 3 //pin del bottone che governa il giocatore A
#define BUTTON_B 2 //pin del bottone che governa il giocatore B
#define BUTTON_START 4 //pin del bottone di START
#define PIN_RED 9 //pin del led rosso
#define POT A0 //pin del potenziometro
#define S2 2000 //2 secondi in millisecondi
#define S1 1000 //1 secondo in millisecondi
#define S05 500 //0.5 secondi in millisecondi
#define RTFactor 7/8 //fattore di diminuzione del reaction time
#define POT_MIDDLE 512 //potenza media del potenziometro
#define MIN_SPEED 1 //velocità minima
#define MAX_SPEED 2 //velocità massima
#define PULSE_T 50 //periodo di pulsione del led rosso
#define BOUNCE_T 50000 //periodo di attesa in microsecondi tra una reazione e l'altra dello stesso pulsante
#define MIN_INT 0 //intensità minima del led
#define MAX_INT 255 //intensità massima del led

//variabili del programma
int fadeAmount = 5;
int currIntensity;
volatile bool isAOn; 
volatile bool isBOn; 
bool giocoIniziato; 
volatile bool giocoFinito; 
volatile bool win_A;
volatile bool win_B;
volatile bool reaction_A; 
volatile bool reaction_B; 
volatile bool verso;
int speed;
int currentPin;
long currentTime;
long initialTime;
volatile int RT;
long reactionTime;
volatile int scambio;
volatile long buttonTyped_A;
volatile long buttonTyped_B;

/*
 * Diminuisce il reaction time di 1/8 dopo ogni scambio.
 */
void changeRT() {
  if (scambio > 1) {
    RT = RT * RTFactor;
  }
}

/*
 * Fa blinkare il led del giocatore A dopo la vittoria per 2 secondi.
 */
void winner_A() {
  digitalWrite(PIN_MIDDLE, LOW);
  digitalWrite(PIN_B, LOW);
  initialTime = millis();
  while (millis() - initialTime <= S2) {
    digitalWrite(PIN_A, HIGH);
    delay(S1);
    digitalWrite(PIN_A, LOW);
    delay(S1);
  }
}

/*
 * Fa blinkare il led del giocatore B dopo la vittoria per 2 secondi.
 */
void winner_B() {
  digitalWrite(PIN_MIDDLE, LOW);
  digitalWrite(PIN_A, LOW);
  initialTime = millis();
  while (millis() - initialTime <= S2) {
    digitalWrite(PIN_B, HIGH);
    delay(S1);
    digitalWrite(PIN_B, LOW);
    delay(S1);
  }
}

/*
 * Funzione associata all'interruzione data dal pulsante del giocatore A.
 */
void react_A() {
  if (micros() - buttonTyped_A > BOUNCE_T && !giocoFinito) { // elimina i rimbalzi
    if (isAOn) {
      scambio++;
      verso = !verso;
      reaction_A = true;
      isAOn = false;
      buttonTyped_A = micros();
      changeRT();
    }
    else {
      giocoFinito = true;
      win_B = true;
    }
  }
}

/*
 * Funzione associata all'interruzione data dal pulsante del giocatore B.
 */
void react_B() {
  if (micros() - buttonTyped_B > BOUNCE_T && !giocoFinito) { //elimina i rimbalzi
    if (isBOn) {
      scambio++;
      verso = !verso;
      reaction_B = true;
      buttonTyped_B = micros();
      isBOn = false;
      changeRT();
    }
    else {
      giocoFinito = true;
      win_A = true;
    }
  }

}

/*
 * Permette il movimento dei led da una parte all'altra.
 */
void move() {
  if (millis() - currentTime > S1 / speed || reaction_A || reaction_B) {
    if (!verso && currentPin < PIN_A) {
      digitalWrite(currentPin, LOW);
      currentPin++;
      digitalWrite(currentPin, HIGH);
      if (PIN_A == currentPin) {
        reactionTime = millis();
        isAOn = true;
        
      }
      currentTime = millis();

    }
    else if (verso && currentPin > PIN_B) {
      digitalWrite(currentPin, LOW);
      currentPin--;
      digitalWrite(currentPin, HIGH);
      if (PIN_B == currentPin) {
        reactionTime = millis();
        isBOn = true;
      }
      currentTime = millis();
    }
    reaction_A = false;
    reaction_B = false;
  }
  if (millis() - reactionTime > RT ) {
    if (isAOn) {
      giocoFinito = true;
      win_B = true;
    }
    else if (isBOn) {
      giocoFinito = true;
      win_A = true;
    }
  }
}

/*
 * Imposta la speed iniziale in accordo con la potenza data dal potenziometro, su una scala di due livelli di difficoltà.
 */
void setSpeed() {
  analogRead(A0) < POT_MIDDLE ? speed = MIN_SPEED : speed = MAX_SPEED;
}

/*
 * Fa blinkare il led rosso prima dell'inizio del gioco.
 */
void ledPulse() {
  if (millis() - initialTime > PULSE_T) {
    analogWrite(PIN_RED, currIntensity);   
    currIntensity = currIntensity + fadeAmount;
    initialTime = millis();
    if (currIntensity == MIN_INT || currIntensity == MAX_INT) {
      fadeAmount = -fadeAmount ;
    } 
  }     
}

void initialize(){
  isAOn = false;
  isBOn = false;
  currIntensity = MIN_INT;
  giocoIniziato = false;
  giocoFinito = false;
  win_A = false;
  win_B = false;
  reaction_A = false;
  reaction_B = false;
  RT = S2;
  scambio = 0;
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_MIDDLE, OUTPUT);
  pinMode(BUTTON_B, INPUT);
  pinMode(BUTTON_A, INPUT);
  pinMode(BUTTON_START, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_A), react_A, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_B), react_B, FALLING);
}

void loop() {
  initialize();
  initialTime = millis();
  Serial.println("Welcome to Led Pong. Press key T3 to start");
  while (!giocoIniziato) {
    ledPulse();
    if (digitalRead(BUTTON_START) == HIGH) {
      setSpeed();
      giocoIniziato = true;
      digitalWrite(PIN_MIDDLE, HIGH);
      currentPin = PIN_MIDDLE;
      millis() % 2 == 0 ? verso = false : verso = true;
    }
  }
  digitalWrite(PIN_RED, LOW);
  Serial.println("Go!");
  currentTime = millis();
  buttonTyped_A = micros();
  buttonTyped_B = micros();
  while (!giocoFinito) {
    move();
  }
  if (win_A) {
    Serial.print("Game over! The winner is the player A after ");
    Serial.print(scambio);
    Serial.println(" shots.");
    winner_A();
  }
  else {
    Serial.print("Game over! The winner is the player B after ");
    Serial.print(scambio);
    Serial.println(" shots.");
    winner_B();
  } 
}
