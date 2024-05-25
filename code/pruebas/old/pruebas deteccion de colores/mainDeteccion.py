import cv2
import numpy as np
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import serial

# Inicializar la cámara de la Raspberry Pi
camera = PiCamera()
camera.resolution = (320, 180)
camera.rotation = 180
raw_capture = PiRGBArray(camera, size=(320, 180))

# Inicializar la comunicación serial con Arduino
ser = serial.Serial('/dev/ttyACM0', 9600)  # Cambiar el puerto según corresponda

# Esperar a que la cámara y la comunicación serial se inicialicen
time.sleep(2)

largest_green_area = 0
largest_red_area = 0

for frame in camera.capture_continuous(raw_capture, format="bgr", use_video_port=True):
    image = frame.array
    
    # Convertir el fotograma a HSV (Hue, Saturation, Value)
    hsv_frame = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    
    # Definir rangos de colores en HSV para verde y rojo
    lower_green = np.array([40, 40, 40])
    upper_green = np.array([80, 255, 255])
    
    lower_red = np.array([0, 100, 100])
    upper_red = np.array([10, 255, 255])
    
    # Crear máscaras para los colores de interés
    green_mask = cv2.inRange(hsv_frame, lower_green, upper_green)
    red_mask = cv2.inRange(hsv_frame, lower_red, upper_red)
    
    # Encontrar contornos en las máscaras
    green_contours, _ = cv2.findContours(green_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    red_contours, _ = cv2.findContours(red_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    # Procesar contornos verdes
    if len(green_contours) > 0:
        largest_green_contour = max(green_contours, key=cv2.contourArea)
        largest_green_area = cv2.contourArea(largest_green_contour)
    
    # Procesar contornos rojos
    if len(red_contours) > 0:
        largest_red_contour = max(red_contours, key=cv2.contourArea)
        largest_red_area = cv2.contourArea(largest_red_contour)
    
    # Enviar señal al Arduino según el color detectado
    if largest_green_area > largest_red_area and largest_green_area > 100:
        ser.write(b'G')  # Enviar 'G' para cuadro verde
        print("Cubo verde detectado")
    elif largest_red_area > largest_green_area and largest_red_area > 100:
        ser.write(b'R')  # Enviar 'R' para cuadro rojo
        print("Cubo rojo detectado")
    
    # Limpiar el buffer de captura para el siguiente fotograma
    raw_capture.truncate(0)
    
    # Salir si se presiona la tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Cerrar ventanas al finalizar
cv2.destroyAllWindows()
ser.close()  # Cerrar la comunicación serial
