# Multi-Class Waste Disposal System Using Sensor Fusion, IoT Alerting and YOLOv8 Vision Intelligence

An advanced automated smart infrastructure project creating an intelligent waste receptacle that identifies, classifies, and tracks disposal behaviors using deep-learning computer vision combined with hardware sensor arrays.

## Architecture & Framework Components
1. **YOLOv8 Edge Vision:** Runs an object detection layer trained via customized datasets annotated on Roboflow to sort trash immediately into multi-class bins.
2. **Sensor Fusion Subsystem:** Employs an ESP32 microcontroller hosting multiple specialized sensors to map real-time structural fills:
   - **HC-SR04 Ultrasonic Sensors** for volumetric depth calculation.
   - **Inductive Proximity Arrays** for instant metallic material identification.
   - **MQ-135 Gas Sensors** for organic decomposition odor tracking.
   - **IR and Rain Sensor Modules** to check spatial entry status and moisture limits.
3. **IoT Cloud Alerting:** Uses the Telegram Bot API to automatically send real-time alerts to municipality crews when bins are full.

## References
- Ultralytics YOLOv8 Documentation (`docs.ultralytics.com`).
- J. Redmon et al., "You Only Look Once: Unified, Real-Time Object Detection," *Proceedings of CVPR*.
- ESP32 Technical Reference Manual (Espressif Systems).

## Project Authors (Section A1, Group 02)
- **Rejoun Rahi Rad** (2106003)
- **Abrar Fahim** (2106005)
- **Siddhartha Sankar Das** (2106004)
- **Md. Yeasir Alif** (2106011)
- **Al Muktadir Khan** (2106012)

**Course:** Control Systems Laboratory (EEE 318), Bangladesh University of Engineering and Technology (BUET).
