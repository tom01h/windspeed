#define echoPin0 D5 // Echo Pin
#define trigPin0 D6 // Trigger Pin
#define echoPin1 D7 // Echo Pin
#define trigPin1 D8 // Trigger Pin

#define Len 3

double l_V[Len] = {0};
double l_C[Len] = {0};

void setup() {
  Serial.begin( 115200 );
  pinMode( echoPin0, INPUT );
  pinMode( trigPin0, OUTPUT );
  pinMode( echoPin1, INPUT );
  pinMode( trigPin1, OUTPUT );
  digitalWrite(trigPin0, LOW);
  digitalWrite(trigPin1, LOW);
}

void loop() {
  double T0 = 0;
  double T1 = 0;
  double V = 0; // 風速
  double C = 0; // 音速
  double Distance = 84;

  digitalWrite( trigPin0, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin0, LOW );
  T0 = pulseIn( echoPin0, HIGH ); //センサからの入力

  delay(10);

  digitalWrite( trigPin1, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin1, LOW );
  T1 = pulseIn( echoPin1, HIGH ); //センサからの入力

  V = Distance/2.0*(1/T0 - 1/T1)*1000*1000/100; // us -> s ; cm -> m
  C = Distance/2.0*(1/T0 + 1/T1)*1000*1000/100;

  int num = 0;
  double AC = 0;
  double AV = 0;
  for(int i=0; i < Len-1; i++){
    if(l_C[i] != 0){num++; AC += l_C[i]; AV += l_V[i];}
    l_V[i] = l_V[i+1];
    l_C[i] = l_C[i+1];
  }

  AV += V;
  num++;
  l_V[Len-1] = V;
  l_C[Len-1] = C;
  
  Serial.print("風速: ");
  Serial.print(V);
  Serial.print(" m/s");
  Serial.print("    平均: ");
  Serial.print(AV/num);
  Serial.print(" m/s");
  Serial.print("    音速: ");
  Serial.print(C);
  Serial.print(" m/s");
  Serial.println("");

  delay(500);
}
