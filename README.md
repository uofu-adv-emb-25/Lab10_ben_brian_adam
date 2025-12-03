Development branch for lab 10, authored by Brian Stites, Ben Martins and Adam Billings

VSYS and any shared ground pin should be where the power is supplied to.

vsys input range: 1.8 - 5.5V

wake_en0 0xffff_ffff
wake_en1 0x7fff (15 bit)

sleep_en0 0xffff_fff
sleep_en1 0x7fff (15 bit)

enabled0 0x0000_0000
enabled1 0x0000 (15 bit)

Forward drop of led is 1.723.

Resistor is 217.3 ohm.

Led circiut is running at 3v3, draws 6.65 mA. 

For blinky using sleep ms, the current draw oscillates between 30-34 mA. (off/on)

For blinky using freertos task and vTaskDelay, the current draw oscillates between 34-38 mA. (off/on)

For busy task utilizing ~100% CPU utilization, the current draw is stable around 31 mA. (no LED toggle).


For gpio initiated interrupt, the current draw is stable around 30.8-32.8 mA (off/on) {1Hz}

For gpio initiated interrupt, the current draw is stable around 31.8 average (off/on) {1kHz}

For gpio initiated interrupt, the current draw is stable around 31.8 average (off/on) {10kHz}

For gpio initiated interrupt, the current draw is stable around 32 average (off/on) {100kHz}

For gpio initiated interrupt, the current draw is stable around 32.8 average (off/on) {1MHz}

Using software to interrput a sleep state, the current draw is stable around 1.7 - 27.6 mA (sleep/on)

Using a GPIO hardware interrupt to wake the pico, the current draw is stable around 900 uA  27.7 sleep-mA