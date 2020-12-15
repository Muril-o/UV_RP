# UV_RP
ESP-32 and Arduino integration for real-time measurement of the UV index using a ML8511 sensor, and Telegram integration.

(PS: Domains used in Arduino/ESP32 projects are disabled for security reasons cause I forgot to change from test env before commiting.)
(Also PS: Sorry for bad code, some of it was done in a 2h code session.)

# File tree
- To deploy you need a php server running `project_php` code in a server (can be local server as long as ESP is connected to same network or you have open ports for the desired service.
- Backend routines are from the `project_java` directory, compile it using any JDK and Maven for dependency management.
(Need `.env` file in the same directory as jar file as described in `Info.java` class.)
- Standalone arduino application is in the `project_arduino_LCD` directory.
- For HTTP server integration files are in `project_arduino` directory.
- For direct communication with telegram from ESP32 (without HTTP server) please refer to `project_esp` directory.

Will update this when I get time, for more specific instructions.

# Credits

Thank you for the code inspirations and examples.
- https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
- https://how2electronics.com/uv-sensor-ml8511-arduino-uv-ray-intensity-meter/
- https://www.filipeflop.com/blog/controle-seu-esp32-usando-telegram/
- https://techtutorialsx.com/2020/06/10/esp32-camera-image-server/
- https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/ML8511_3-8-13.pdf (ML8511 datasheet)
- https://stackoverflow.com/a/58099023
