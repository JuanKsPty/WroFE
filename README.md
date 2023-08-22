#Bender 21
conformado por:
- Juan castillo
- Juan Bultron
- Daiana Castillo

###Gestión de movilidad: 
•	Chasis: utilizamos en el chasis una base hecha con lego y algunas bases para soportar los componentes eléctricos los diseñados en 3d para adaptarlos a las piezas lego, específicamente creamos el soporte del driver del motor yRaspberry PI, el soporte del servo y el soporte de las baterias.
•	Realiza un movimiento en su mayor parte en línea recta, pero en caso de detectar el cambio de color en las líneas del suelo, hace el giro pertinente ya sea a la derecha o la izquierda dependiendo del color que lea primero 
•	Para los giros utilizamos un giroscopio el cual está conectado al Arduino. 
•	Entre los motores que utilizames esta el motor mediano de lego EV3 para el movimiento del eje de la parte trasera del robot y el servo para darle direccion al robot.

###Gestión de potencia y sentido: 
•	La fuente de energía que utilizamos en el vehículo son baterías recargables, cuenta con sensores ultrasónicos para mantenerlo alejado de los bordes y un sensor de color para escanear el suelo.
•	Para lo que es regular la potencia del robot utilizamos un controlador de motor L298N. 
•	Para el sentido también utiliza los ultrasónicos. 
•	A la hora de detectar cual giro tiene que hacer el robot, utilizamos una mezcla de los valores del sensor de color y los ultrasonicos.

###Gestión de obstáculos:
•	Para la detección de obstaculos utilizamos una camará conectada a un raspberry para la deteccion de los distintos objetos, además de un ultrasonico al frente para la deteccion de colisiones.
