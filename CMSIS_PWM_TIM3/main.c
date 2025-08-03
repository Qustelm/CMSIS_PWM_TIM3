#include "stm32f10x.h"  

void INIT_TIM3() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enable clocking for tim3
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable clocking for GPIOA

    //Configure PA6 as altenate function push-pull
    GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6); 
    GPIOA->CRL |= GPIO_CRL_CNF6_1;
    GPIOA->CRL |= GPIO_CRL_MODE6;

    TIM3->PSC = 7200-1; //Prescaler: 72MHz / 7200 = 10000Hz freq
    TIM3->ARR = 1000-1; // 1000/10000Hz = 0.1s ~ 10Hz freq

    TIM3->CCMR1 |= TIM_CCMR1_OC1PE; // Output compare channel 1 preload enable, not critical but recommended
    TIM3->CCR1 = 500-1; // duty 50% (500/1000)
    TIM3->CCER |= TIM_CCER_CC1E; // Capture/Compare channel 1 output enable

    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M; // clear OC1M - first channel bits
    //Set PWM mode 1 (OC1M = 110)
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1;
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_2;

    TIM3->CR1 |= TIM_CR1_ARPE; // Enable auto-preload, not critical but recommended
    TIM3->CR1 |= TIM_CR1_CEN; // Start Timer

    //You can modify CCR1 at runtime to adjust the PWM duty cycle
    //Without remapping TIM3 Channel 1 is mapped to PA6
}

int main(void) {
    INIT_TIM3();

    while (1) {}
    return 0;
}