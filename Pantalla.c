#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

String att[] = {"Age", "Sex", "ChestPain", "RestinBloodPressure", "MaxHeartRate", "ExerciseInducedAngina", "PreviousPeak", "Slope", "MajorVessels", "ThalRate"};

float Theta[] = {1.42610339, -0.13385281, -1.21375503, 0.76059476, -0.24898053, 0.40682315, -0.91710596, -0.5523501, 0.40538964, -0.75573673, -0.56414873};
float means[] = {54.366337, 0.683168, 0.966997, 131.623762, 149.646865, 0.326733, 1.039604, 1.399340, 0.729373, 2.313531};
float stds[] = {9.082101, 0.466011, 1.032052, 17.538143, 22.905161, 0.469794, 1.161075, 0.616226, 1.022606, 0.612277};

int N = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Ready.");
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  N = sizeof(means) / sizeof(float);
}

void loop(){
  float X[N];
  float Y = -1;

  for (int i = 0; i < N; i++) {
    X[i] = Serial.parseFloat();
  }

  Serial.println("\n**************************************");
  for (int i = 0; i < N; i++) {
    Serial.print(att[i] + "=");
    Serial.print(X[i]);
    Serial.println();
  }
  
  float Xstd[N];

  standarize(Xstd, X);
  Y = logistic_function(Xstd);

  if (Serial.available() > 0) {
    Serial.print("Y = ");
    Serial.println(Y);
    Serial.println("**************************************");
  }

  if (Y > 0.5) {
    lcd.clear();
    lcd.print("ALERT!");
  } else {
    lcd.clear();
    lcd.print("All right.");
  }
  
  //63 1 3 145 150 0 2.3 0 0 1
  
}

void standarize(float * Xstd, float X[]) {
  for (int i = 0; i < N; i++) {
    Xstd[i] = (X[i] - means[i]) / stds[i];
  }
}

float logistic_function(float X[])
{
  float Xt = Theta[0];
  for (int i = 1; i < N + 1; i++) {
    Xt = Xt + X[i - 1] * Theta[i];
  }
  return 1 / (1 + exp(-Xt));
}





