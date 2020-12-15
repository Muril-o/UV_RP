# UV_RP
ESP-32 and Arduino integration for real-time measurement of the UV index and Telegram integration.

(PS: Domains used in Arduino/ESP32 projects are disabled for security reasons cause I forgot to change from test env before commiting.)

# File tree
- To deploy you need a php server running `project_php` code in a server (can be local server as long as ESP is connected to same network or you have open ports for the desired service.
- Backend routines are from the `project_java` directory, compile it using any JDK and Maven for dependency management.
- Standalone arduino application is in the `project_arduino_LCD` directory.
- For HTTP server integration files are in `project_arduino` directory.
- For direct communication with telegram from ESP32 (without HTTP server) please refer to `project_esp` directory.

Will update this when I get time, for more specific instructions.
