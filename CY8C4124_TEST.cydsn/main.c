#include <global.h>

#define SEND_INTERVAL 1000

/* Variabili globali */
#define PERIOD 10000   // USA NUMERI PARI
#define W_BRIGHT 1500  // MAX PERIOD / 2
#define R_BRIGHT 1500  // MAX PERIOD / 2

volatile uint32 msTicks = 0;  // Variabile globale per il conteggio dei millisecondi
volatile uint32 msCont = 0;  // Variabile globale per il conteggio dei millisecondi
char myString[25];

// struttura che contiene un bitfield per pilotare i LED
typedef struct {
    uint8_t led0 : 1;
    uint8_t led1 : 1;
    uint8_t led2 : 1;
    uint8_t led3 : 1;
    uint8_t led4 : 1;
    uint8_t led5 : 1;
    uint8_t led6 : 1;
    uint8_t led7 : 1;
    uint8_t led8 : 1;
    uint8_t led9 : 1;
    uint8_t ledA : 1;
    uint8_t ledB : 1;
    uint8_t ledC : 1;
    uint8_t ledD : 1;
    uint8_t ledE : 1;
    uint8_t ledF : 1;
    }my_bits;

// union per accedere ai led sia bit a bit sia a blocchi
union my_LEDS {
    my_bits bit;
    uint16_t data;
    } LED_W, LED_R;

/* prototipi delle funzioni */
CY_ISR_PROTO(driveLED_W);
CY_ISR_PROTO(driveLED_R);
CY_ISR_PROTO(driveLED_OFF);
void SysTick_Handler(void);

int main() {
    /* Inizializza UART */
    //UART_Start();
    // Inizializzo il PWM_W
    PWM_W_WritePeriod(PERIOD);
    PWM_R_WritePeriod(PERIOD);
    PWM_W_WriteCounter(0000);
    PWM_R_WriteCounter(PERIOD / 2);
    PWM_W_Start();
    PWM_R_Start();

    // Inizializza SysTick per generare interrupt ogni 1 ms
    CySysTickStart();
    CySysTickSetCallback(0, SysTick_Handler);  // Associa il gestore dell'interrupt

    /// inizializzo gli interupt
    ISR_R_StartEx(driveLED_R);
    ISR_W_StartEx(driveLED_W);
    ISR_W0_StartEx(driveLED_OFF);
    ISR_R0_StartEx(driveLED_OFF);

    // setto i valori iniziali dei counter dei PWM dei LED
    PWM_W_WriteCounter(0000);
    PWM_R_WriteCounter(5000);

    // Abilita interrupt globali
    CyGlobalIntEnable;

    // quali LEDS accendo?
    LED_W.bit.led1 = 1;
    LED_W.bit.led2 = 1;
    LED_W.bit.led7 = 1;
    LED_W.bit.led9 = 1;

    LED_R.bit.led4 = 1;
    LED_R.bit.led8 = 1;
    LED_R.bit.led5 = 1;
    LED_R.bit.led9 = 1;


    while (1) {
        // ciclo eseguito ad ogni 1000 millisecondi
        if (msTicks % 1000 == 0) {
            // Qui puoi leggere il valore di msTicks per sapere quanti millisecondi sono passati
            sprintf(myString, "Millis: %ldms.\n", msTicks);  // <Stampa il valore di msTicks
            //UART_PutString(myString);
            }

        }
    }


// Funzione chiamata dall'interrupt SysTick ogni millisecondo
void SysTick_Handler(void) {
    msTicks++;  // Incrementa il contatore dei millisecondi
    }


CY_ISR(driveLED_W) {
    /* Clear pending Interrupt */
    (LED_W.bit.led1) ? LED_1_Write(0) : LED_1_Write(1);
    (LED_W.bit.led2) ? LED_2_Write(0) : LED_2_Write(1);
    (LED_W.bit.led3) ? LED_3_Write(0) : LED_3_Write(1);
    (LED_W.bit.led4) ? LED_4_Write(0) : LED_4_Write(1);
    (LED_W.bit.led5) ? LED_5_Write(0) : LED_5_Write(1);
    (LED_W.bit.led6) ? LED_6_Write(0) : LED_6_Write(1);
    (LED_W.bit.led7) ? LED_7_Write(0) : LED_7_Write(1);
    (LED_W.bit.led8) ? LED_8_Write(0) : LED_8_Write(1);
    (LED_W.bit.led9) ? LED_9_Write(0) : LED_9_Write(1);
    PWM_W_WriteCompare(300);
    ISR_W_ClearPending();
    // msCont++;
    }

CY_ISR(driveLED_R) {
    /* Clear pending Interrupt */
    (LED_R.bit.led1) ? LED_1_Write(0) : LED_1_Write(1);
    (LED_R.bit.led2) ? LED_2_Write(0) : LED_2_Write(1);
    (LED_R.bit.led3) ? LED_3_Write(0) : LED_3_Write(1);
    (LED_R.bit.led4) ? LED_4_Write(0) : LED_4_Write(1);
    (LED_R.bit.led5) ? LED_5_Write(0) : LED_5_Write(1);
    (LED_R.bit.led6) ? LED_6_Write(0) : LED_6_Write(1);
    (LED_R.bit.led7) ? LED_7_Write(0) : LED_7_Write(1);
    (LED_R.bit.led8) ? LED_8_Write(0) : LED_8_Write(1);
    (LED_R.bit.led9) ? LED_9_Write(0) : LED_9_Write(1);
    PWM_R_WriteCompare(300);
    ISR_R_ClearPending();
    }

CY_ISR(driveLED_OFF) {
    /* Clear pending Interrupt */
    LED_1_Write(1);
    LED_2_Write(1);
    LED_3_Write(1);
    LED_4_Write(1);
    LED_5_Write(1);
    LED_6_Write(1);
    LED_7_Write(1);
    LED_8_Write(1);
    LED_9_Write(1);
    ISR_W0_ClearPending();
    ISR_R0_ClearPending();
    }


/* [] END OF FILE */
