#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "tarefa.pio.h"

uint sm;
PIO pio;
uint valorLed;
uint static volatile ultimoTime = 0;
uint volatile contador = 0;
int static volatile id = 0;

//número de LEDs
#define NUM_PIXELS 25
//pino de saída
#define OUT_PIN 7

//botões de interupção
#define botaoA  5
#define botaoB  6

//Pino do RGB vermelho
#define led_vermelho 13

void setup(){

  // Inicialização da matriz de LED
  gpio_init(OUT_PIN);
  gpio_set_dir(OUT_PIN, GPIO_OUT);

  // Inicialização do led vermelho
  gpio_init(led_vermelho);
  gpio_set_dir(led_vermelho, GPIO_OUT);

  // Inicialização dos botões A e B e ativação do pull up
  gpio_init(botaoA);
  gpio_set_dir(botaoA, GPIO_IN);
  gpio_pull_up(botaoA);
  gpio_init(botaoB);
  gpio_set_dir(botaoB, GPIO_IN);
  gpio_pull_up(botaoB);
}

//Função para piscar o led vermelho 5x por segundo
int piscaLed(int led, int timer){
  gpio_put(led, 1);
  sleep_ms(timer);
  gpio_put(led, 0);
  sleep_ms(timer);
}

// Função para definir a intensidade das cores da matriz de led
uint matrix_rgb(float r, float g, float b)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

// Função para converter a posição da matriz para uma posição do vetor.
int getid(int x, int y)
{
  if (y % 2 == 0)
  {
    return 24 - (y * 5 + x); 
  }
  else
  {
    return 24 - (y * 5 + (4 - x));
  }
}

// Função para desenhar na matriz de leds
void desenho(double *desenho, uint32_t valorLed, PIO pio, uint sm, double r, double g, double b)
{

  for (int16_t i = 0; i < NUM_PIXELS; i++)
  {
    valorLed = matrix_rgb(desenho[i] * r, desenho[i] * g, desenho[i] * b);
    pio_sm_put_blocking(pio, sm, valorLed);
  };
}

//Apagar leds
double apagar_leds[25] = {0.0, 0.0, 0.0, 0.0, 0.0, 
                          0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0};

//Desenho do número 0
double desenho0[25] =    {0.0, 1.0, 1.0, 1.0, 0.0, 
                          0.0, 1.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0};                          

//Desenho do número 1
double desenho1[25] =    {0.0, 1.0, 1.0, 1.0, 0.0, 
                          0.0, 0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0, 0.0,
                          0.0, 1.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0, 0.0};

//Desenho do número 2
double desenho2[25] =    {0.0, 1.0, 1.0, 1.0, 0.0, 
                          0.0, 1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0};

//Desenho do número 3
double desenho3[25] =    {0.0, 1.0, 1.0, 1.0, 0.0, 
                          0.0, 0.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0};

//Desenho do número 4
double desenho4[25] =    {0.0, 1.0, 0.0, 0.0, 0.0, 
                          0.0, 0.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0,
                          0.0, 1.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 0.0, 1.0, 0.0};

//Desenho do número 5
double desenho5[25] =    {0.0, 1.0, 1.0, 1.0, 0.0, 
                          0.0, 0.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0,
                          0.0, 1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0};

//Desenho do número 6
double desenho6[25] =    {0.0, 1.0, 1.0, 1.0, 0.0, 
                          0.0, 1.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0,
                          0.0, 1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0};

//Desenho do número 7
double desenho7[25] =    {0.0, 0.0, 0.0, 0.0, 1.0, 
                          0.0, 1.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 1.0, 0.0,
                          1.0, 1.0, 1.0, 1.0, 1.0};

//Desenho do número 8
double desenho8[25] =    {0.0, 1.0, 1.0, 1.0, 0.0, 
                          0.0, 1.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0,
                          0.0, 1.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0};

//Desenho do número 9
double desenho9[25] =    {0.0, 1.0, 1.0, 1.0, 0.0, 
                          0.0, 0.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0,
                          0.0, 1.0, 0.0, 1.0, 0.0,
                          0.0, 1.0, 1.0, 1.0, 0.0};

//Array para armazenamento dos desenhos
double *numeros[10] = {desenho0, desenho1, desenho2, desenho3, desenho4, desenho5, desenho6, desenho7, desenho8, desenho9};

// função para o loop entre 0 e 9
void loopId() {
  if (id < 0){
    id = 9;
  }
  else if (id > 9){
    id = 0;
  }
}

//rotina da interrupção
  void callback_button(uint botao, uint32_t events)
{
  uint timeAtual = to_us_since_boot(get_absolute_time()); // Tempo em milissegundos 
  //250 ms para evitar ação dupla do botão
  if(timeAtual - ultimoTime > 250000){
    ultimoTime = timeAtual;
    printf("Contador: %d\n", contador);

  bool estadoBotao = gpio_get(botao);
  
  if(!estadoBotao){
    if(botao == botaoA){
      id++;
      loopId();
      printf("Valor do id: %d\n", id);
      desenho(numeros[id], valorLed, pio, sm, 0.0, 0.0, 0.1); // Desenha conforme o número do id
      contador++;
      printf("Valor do contador: %d\n", contador);
    }
    else {
        id--; 
        loopId();
        printf("Valor do id: %d\n", id);
        desenho(numeros[id], valorLed, pio, sm, 0.0, 0.0, 0.1); // Desenha conforme o número do id
        contador++; 
        printf("Valor do contador: %d\n", contador);
       }
    }
  }

}

int main()
{
  bool freqClock;
  float r = 0.0, b = 0.0, g = 0.0;
  pio = pio0;

  freqClock = set_sys_clock_khz(128000, false); // frequência de clock
  setup(); //Chama a função para iniciar os pinos

  // configurações da PIO
  printf("iniciando a transmissão PIO");
  if (freqClock)
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
  uint offset = pio_add_program(pio, &pio_matrix_program);
  sm = pio_claim_unused_sm(pio, true);
  pio_matrix_program_init(pio, sm, offset, OUT_PIN);

  //Chama as funções de callback dos botões
  gpio_set_irq_enabled_with_callback(botaoA, GPIO_IRQ_EDGE_FALL, true, &callback_button);
  gpio_set_irq_enabled_with_callback(botaoB, GPIO_IRQ_EDGE_FALL, true, &callback_button);

while (true)
  {
    piscaLed(led_vermelho, 200); //Chama a função de piscar o led vermelho 5x por segundo
  }
  return 0;
}
