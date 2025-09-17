int A;
int B;
int C;
int D;

void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
}

void loop() {
    A = (10UL * 1UL * 1000UL);
    B = (10UL * 1UL * 1000UL);
    D = (10UL * 1UL * 1000UL);

    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    delay(A);

    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    delay(B);

    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(A);

    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    delay(D);

    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
    delay(60UL * 12UL * 1000UL);

    digitalWrite(7, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
}