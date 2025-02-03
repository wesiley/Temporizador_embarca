#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definindo os pinos dos LEDs
#define LED_RED_PIN 11
#define LED_YELLOW_PIN 12
#define LED_GREEN_PIN 13

// Estado do semáforo
typedef enum {
    RED,
    YELLOW,
    GREEN,
} TrafficLightState;

TrafficLightState current_state = RED;

// Função para inicializar os LEDs
void initialize_leds() {
    gpio_init(LED_RED_PIN);
    gpio_init(LED_YELLOW_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
}

// Função para atualizar o estado do semáforo
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

// Callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    update_traffic_light();
    return true; // Continua o temporizador
}

int main() {
    // Inicializa a comunicação serial (para imprimir mensagens)
    stdio_init_all();

    // Inicializa os LEDs
    initialize_leds();

    // Configura o temporizador para 3 segundos (3000 ms)
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {

        printf("Semáforo em funcionamento...\n");
        sleep_ms(1000); // Espera 1 segundo
    }

    return 0;
}