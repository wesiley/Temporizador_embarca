# Projeto Temporizador periodico (atuação do semaforo) 

Este projeto faz com que ascenda cada LED(vermeljo,verde e amarelo) periodicamente a cada 3 segundos por meio de uma interrupção.
## Hardware 🛠️

- Microcontrolador RP2040 (Raspberry Pi Pico).
- 3 LED.
- 3 Resistores de 330 Ω.

## Software 💻

* **SDK do Raspberry Pi Pico:** O SDK (Software Development Kit) do Pico, que inclui as bibliotecas e ferramentas necessárias para desenvolver e compilar o código. [Instruções de instalação](https://www.raspberrypi.com/documentation/pico/getting-started/)
* **CMake:** Um sistema de construção multiplataforma usado para gerar os arquivos de construção do projeto.
* **Compilador C/C++:**  Um compilador C/C++ como o GCC (GNU Compiler Collection).
* **Git:** (Opcional) Para clonar o repositório do projeto.


### O código está dividido em vários arquivos para melhor organização:

- **`temporizador_embarca.c`**: Código com a função de loop principal: gera o código que faz com que alterne os leds periodicamente em um tempo definido.
- **`CMakeLists.txt`:** Define a estrutura do projeto para o CMake.
- **`diagram.json`:** projeta a simulação do semaforo.
- **`wokwi.toml`:** configuração para sicronizar o código a simulação.




## Como Compilar e Executar ⚙️

1. **Instale o SDK do Raspberry Pi Pico:** Siga as instruções no site oficial do Raspberry Pi.
2. **Clone este repositório:** `temporizador_embarca.c`
3. **Navegue até o diretório do projeto:** `cd Temporizador_embarca`
4. **Compile o projeto:** `cmake -B build && cmake --build build`
5. **Copie para o Pico:** Copie o conteúdo da pasta `build` (gerada após a compilação) para o Raspberry Pi Pico. O programa iniciará automaticamente.


## Funcionamento do Loop Principal 🔄 
```
    while (true) {

        printf("Semáforo em funcionamento...\n");
        sleep_ms(1000);
    }
  ```
O loop while (true) garante execução contínua, o printf mantém o programa enviando mensagem para o usuário pelo terminal e o sleep_ms(1000) introdz um atraso de 1 segundos para indicar a alteração de sinal dos leds.

## Funcionamento do Temporizador.
```
void update_traffic_light() {
    switch (current_state) {
        case RED:
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_YELLOW_PIN, 0);
            gpio_put(LED_GREEN_PIN, 0);
            current_state = YELLOW;
            break;
        case YELLOW:
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_YELLOW_PIN, 1);
            gpio_put(LED_GREEN_PIN, 0);
            current_state = GREEN;
            break;
        case GREEN:
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_YELLOW_PIN, 0);
            gpio_put(LED_GREEN_PIN, 1);
            current_state = RED;
            break;
    }
}


bool repeating_timer_callback(struct repeating_timer *t) {
    update_traffic_light();
    return true; 
}
  ```
A função void update_traffic_light() tem como função usar como parâmetro o "current_state" e implementar condições para o controle de liga/desliga dos Leds. bool repeating_timer_callback() é um Temporizador que tem como função imprimir o contador e chamar a função update_traffic_light() para ligar e desligar os leds do semaforo em um tempo definido e sicronizado com o contador.

## Diagrama de Conexões 💡:

https://wokwi.com/projects/421733279201722369

 ## Contribuições 🤝

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.
