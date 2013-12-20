// Automatic Fish Feeder
// @maglovato
// created December 2013
// v 1.1

#include <Servo.h> 
 
Servo servoPorta;
Servo servoPote;
 
int pos = 0;
boolean doloop = true;
int pos_jogar_comida = 58;
int porta_aberta = 145;
int porta_fechada = 0;
int estacionamento = 58;

unsigned Hour = 0;
unsigned Minute = 0;
unsigned long TimeOfLastMinute = 0;

void setup() 
{ 
  servoPote.attach(9);
  servoPorta.attach(8);
} 
 
 
void loop() 
{
  if (doloop)
  {
    inicializacao();
    restaurante_fish();
    despeja_comida();
    estacionar();
    doloop = false;
  }

  unsigned long currentTime = millis();
  if (currentTime-TimeOfLastMinute >= 60000UL)
  {
  Minute++;
  TimeOfLastMinute = currentTime;
  if (Minute > 59)
    {
    Minute = 0;
    Hour++;
    if (Hour > 23)
      Hour = 0;
      doloop = true;
    }
  }

}

void inicializacao()
{
  fecha_porta();
  move_motor(servoPote, 179);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
}

void despeja_comida()
{
  move_motor(servoPote, pos_jogar_comida);
  abre_porta();
  fecha_porta();
}

void restaurante_fish()
{
  //funcao que abastece o mini reservatorio com comida
  move_motor(servoPote, 20);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
  shake(servoPote);
}

void abre_porta()
{
  move_motor(servoPorta, porta_aberta);
}

void fecha_porta()
{
  move_motor(servoPorta, porta_fechada);
}

void estacionar()
{
  // funcao para fazer o pote ficar em posicao de reabastecimento
  move_motor(servoPote, estacionamento); 
}

void move_motor(Servo srv, int pos)
{
  srv.write(pos);
  delay(1000);
}

void shake(Servo srv)
{
  int originalPos = srv.read();

  int pos = originalPos;
  int i = 0;
  int force = 20;

  if (pos<force) {
    pos = force;
  }
  if (pos>(180-force)) {
    pos = (180-force);
  }

  for(i = 0; i < 30; i += 1)
  {
    srv.write(pos + force);
    delay(15);
    srv.write(pos - force);
    delay(15);
  }
  srv.write(originalPos);
  delay(15);
}
