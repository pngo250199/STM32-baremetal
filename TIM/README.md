1. Introducing TIM (Time Peripheral)
  - Tim is one of timing of timers such as Systick or delay. Unlike Systick, developer using TIM for specific peripheral while SysTick is simple system hearbeat timer.
  - TIM is a separate hardware peripheral outside the CPU core while SysTick is a dedicated 24-bit countdown timer inside the CPU core.
  - TIM functioning by: A counter register (CNT) -> A clock source (From APB bus) -> A prescaler (PSC) to an auto-reload value( ARR)
  - Core capabilities:  Generate PWM (motor control)
                        Create precise delays (microseconds to seconds)
                        Measure input signals (pulse width, frequency)
                        Capture events (encoder, sensors)
                        Trigger interrupts at exact times
                        Drive multiple channels independently
- Timing formular"
    <img width="640" height="400" alt="Screenshot From 2026-05-04 15-38-05" src="https://github.com/user-attachments/assets/95f638a0-8619-4d1f-8716-098e31c9ce70" />
