
## Arduino

Repositorio dedicado al desarrollo y almacenamiento de códigos de Arduino y compatibles (con posibles modificaciones necesarias para su funcionamiento), realizados y comentados de la mejor manera posible. Podrás usar este repositorio para tener ejemplos básicos en los que apoyarte para aprender. Además de una recopilación de información útil para principiantes.

Para usar este repositorio, puedes verlo a través de un navegador web y navegar entre las distintas carpetas que están clasificadas. Otra manera es descargar el repositorio entero en zip a través del botón download. En ambos casos, copia el código en tu editor de código favorito que compile para Arduino y añade las librerías correspondientes si fueran necesarias.

## Telegram

Puedes unirte a los grupos de `Telegram` donde hay personas como yo que pueden ayudarte de forma más concreta y fluida con dudas. Además de colaborar y publicar a la gente los proyectos que estés realizando.

- (Donde soy admin) https://t.me/arduinoGP
- https://t.me/arduchino

Otros grupos útiles de autómatas programables PLC y energías renovables.

- https://t.me/plcyautomatas
- https://t.me/energias_renovables


## Donaciones

Puedes ayudar a este repositorio mediante una donación. [![paypal](https://www.paypalobjects.com/es_ES/ES/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=CZM8VWFAP5UUY&source=url)

SHIBA INU COIN: 0x91ea37c54662d618c71ce653c4a5bdb3598834da

## Clasificación de las carpetas

La carpeta de ["RecursosProgramacionPrincipiantes"](RecursosProgramacionPrincipiantes) posee información útil en forma de libros y PDF(se recomienda encarecidamente su lectura) con tutoriales, ejercicios básicos e imágenes del arduino para principiantes. Estos recursos pertenecen a sus respectivos autores. Además contiene enlaces útiles donde consultar distintas cosas.

La carpeta de ["EjemplosBasicosDeUso"](EjemplosBasicosDeUso) contiene carpetas con información de uso básico de los sensores y actuadores. En cada uno varios elementos, su archivo fritzing del componente si fuera necesario, archivo de conexionado, imagen de conexionado, y un código básico de uso.

La carpeta de ["ProyectosSimples"](ProyectosSimples) contiene distintos ejemplos de los sensores y actuadores, tanto individual como en conjunto. Siendo utilizados de distintas maneras.

La carpeta de ["ProyectosComplejos"](ProyectosComplejos) son aquellos que se consideran más elaborados, con código más complejo o largo.

La carpeta de ["Librerias"](Librerias) contiene las librerias utilizadas, ya sean oficiales como no oficiales. Las creadas por mi se caracterizan por tener `Xib` en el nombre.
Las librerias creadas por mi son:  
- [XibDebounceEdge](Librerias/src/XibDebounceEdge): Permite utilizar botones (o cualquier entrada digital) evitando el debounce y poder usar las acciones asociadas a un botón.
- [XibStave](Librerias/src/XibStave): Permite interpretar pentagramas musicales en arduino, con varios altavoces, cada uno con una melodía de forma sincronizada.
- [XibTempo](Librerias/src/XibTimer): Permite ejecutar funciones cada X tiempo.
- [XibTM1638](Librerias/src/XibTM1638): Permite utilizar esa placa de una manera más fácil.
- [XibXcreen](Librerias/src/XibXcreen): Gestor de botones gráficos en las pantallas compatibles con adafruitLCD.

La carpeta de ["FritzingParts"](FritzingParts) contiene una colección de archivos de fritzing de distintos componentes aquí utilizados.

## Plantilla proyectos

Plantilla para organizar tus proyectos: [Plantilla](https://github.com/Xibhu/Tutoriales/tree/master/Programacion/General)

## Fallos

Para reportar fallos utilizad el sistema de ["Issues"](https://github.com/Xibhu/Arduino/issues) de la web o comunicarlo a través de telegram.

## Editor de código

En mi caso utilizo el editor de texto Visual Studio Code en linux con el plugin o extensión de `PlatformIO`. El tutorial de instalación y uso es el siguiente enlace: https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/

Como utilidad añadida, se puede colocar en cada proyecto creado con `PlatforIO` la ruta de una carpeta de librerías. Al crear un proyecto, se abre el archivo `platformio.ini` y se añade la línea `lib_extra_dirs = /home/xibhu/Proyectos/arduino/Librerias/src`. Colocando la ruta que os corresponda. En linux importante colocar la barra `/` al principio de la ruta.
