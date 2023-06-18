Ensure `platformio` cli is installed.

This project uses a ESP32 (2AC7Z-ESPWROOM32) board.

To upload files to board:

```sh
platformio run -t upload -e esp32
```

To connect to serial monitor:

```sh
platformio device monitor
```

To run tests:

```sh
platformio test -e native
```
