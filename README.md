# Projeto: Controle de LEDs e Interrupções com BitDogLab

## Objetivos

Este projeto tem como objetivos principais:
- Compreender o funcionamento e a aplicação de interrupções em microcontroladores.
- Identificar e corrigir o fenômeno do bouncing em botões por meio de debouncing via software.
- Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.

---

## Descrição do Projeto

Os componentes utilizados são:

- **Matriz 5x5 de LEDs WS2812** (endereçáveis) conectada à GPIO 7.
- **LED RGB**, com os pinos conectados às GPIOs 11, 12 e 13.
- **Botão A**, conectado à GPIO 5.
- **Botão B**, conectado à GPIO 6.

---

## Funcionalidades Implementadas

1. **Piscar LED RGB**: O LED vermelho do LED RGB deve piscar continuamente 5 vezes por segundo.
2. **Incremento com Botão A**: Cada pressionaento do Botão A deve incrementar o número exibido na matriz de LEDs.
3. **Decremento com Botão B**: Cada pressionaento do Botão B deve decrementar o número exibido na matriz de LEDs.
4. **Exibição de Números na Matriz WS2812**:
   - Os LEDs WS2812 serão utilizados para exibir números de **0 a 9**.
   - O formato de exibição deve seguir um padrão fixo, semelhante a caracteres digitais.

---







