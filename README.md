# Título do projeto
Controle de nível de líquidos com PID e IHM Web
# Descrição
O projeto consiste em uma planta de controle de nível para líquidos, que utiliza o controlador proporcional integral derivativo (PID), que faz com que o sinal de erro seja minimizado pela ação proporcional, zerado pela ação integral e obtido com uma velocidade antecipativa pela ação derivativa. Além de todo esse sistema a planta também poderá ser comanda pela rede. O circuito funciona em ciclos, em que o reservatório superior encontra-se sempre aberto e possui um sensor ultrasônico de distância para realizar a medição de seu nível. A partir dessa medição do nível, existirá um valor set point no qual o sistema deverá permanecer equilibrado, para que isso ocorra, no reservatório localizado na parte inferior utilizamos uma bomba d'água que faz com que a água retorne para o reservatório superior.
# Pré-requisitos
Para realizar o projeto é necessário que o programador faça a instalação da IDE do arduíno no site www.arduino.cc para realizar a programação e faça a instalação do software livre de código aberto, Fritizing, no site fritzing.org, para executar a simulação do circuito.
# Lista de Materiais
- Arduíno uno R3
- Driver de corrente
- Mini bomba d'água
- Controlador P&D
- Sensor Ultrasonic
- Estrutura
- Módulo com wi-fi
