
# Arduino
Los códigos progresivamente se irán mejorando. Se modificarán tanto archivos como estructuras sin aviso previo.

Puedes unirte a los grupos de `Telegram` donde hay personas como yo que pueden ayudarte de forma más concreta y fluida con dudas. Además de colaborar y publicar a la gente tus proyectos.

- https://t.me/arduinoGP
- https://t.me/arduchino

Otros grupos útiles de autómatas programables PLC y energías renovables.

- https://t.me/plcyautomatas
- https://t.me/energias_renovables


Puedes ayudar a este repositorio mediante una donación. [![paypal](https://www.paypalobjects.com/es_ES/ES/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=CZM8VWFAP5UUY&source=url)

Aquí se colocarán distintos proyectos basados generalmente en arduino UNO y sus sensores/actuadores. Para el resto de modelos de microcontroladores es posible que sea necesario hacer modificaciones al código en base a los pines usados, librerías, o cualquier otra diferencia que tengan con el modelo UNO.

El repositorio está ordenado de la siguiente manera:

La carpeta de ["RecursosProgramacionPrincipiantes"](RecursosProgramacionPrincipiantes) con información útil en forma de PDF(se recomienda encarecidamente su lectura) con tutoriales, ejercicios básicos e imágenes del arduino para principiantes. Estos recursos pertenecen a sus respectivos autores. Además contiene enlaces útiles donde consultar distintas cosas.

La carpeta de ["EjemplosBasicosDeUso"](EjemplosBasicosDeUso) contiene carpetas con información de uso básico de los sensores y actuadores. En cada uno varios elementos, su archivo fritzing del componente si fuera necesario, archivo de conexionado, imagen de conexionado, y un código básico de uso.

La carpeta de ["ProyectosSimples"](ProyectosSimples) contiene distintos ejemplos de los sensores y actuadores, tanto individual como en conjunto. Siendo utilizados de distintas maneras.

La carpeta de ["ProyectosComplejos"](ProyectosComplejos) son aquellos que se consideran más elaborados, con código más complejo o largo.

La carpeta de ["Librerias"](Librerias) contiene las librerias utilizadas, ya sean oficiales como no oficiales. Las creadas por mi se caracterizan por tener `Xib` en el nombre. Para saber las librerías que se necesitan, hay que leer las líneas que ponen `#include <LIBRERIA.h>` en cada código. Si no pone nada no se necesitan librerías extras. Si lo pone, puede que ya vengan incluidas con el programa de arduino, si al verificar el código da error de libreria no encontrada, entonces hay que descargarla, bien desde el propio gestor de librerias del arduino, desde aquí, de su página oficial, o de donde la encontreis. Al tener el zip, se descomprime para tener una carpeta, y esta se debe colocar en `carpetaDeUsuario/Arduino/libraries`.  
Las librerias creadas por mi son:  
- XibDebounceEdge: Permite utilizar botones (o cualquier entrada de sensor) y evitar el debounce, este efecto consiste en tener un ruido electrico al cerrar los contactos del botón, y que el Arduino lo detecte como varias pulsaciones. Además esta librería permite leer los cuatro estados básicos de ese mismo botón, su flanco de subida, bajada, si se mantiene apretado o suelto y realizar acciones en esos estados. Por ejemplo en el flanco de subida, cuando se pise el botón, se puede incremetar un contador de forma ÚNICA y no se incremente más de una sola vez por pulsación.
- XibStave: Permite interpretar pentagramas musicales en arduino, con varios altavoces, cada uno con una melodía de forma sincronizada.
- XibTempo: Permite ejecutar funciones cada X tiempo.
- XibTM1638: Permite utilizar esa placa de una manera más fácil.
- XibXcreen: Gestor de botones gráficos en las pantallas compatibles con adafruitLCD.

La carpeta de ["FritzingParts"](FritzingParts) contiene una colección de archivos de fritzing de distintos componentes aquí utilizados.

Plantilla para organizar un proyecto: [Plantilla](https://github.com/Xibhu/Tutoriales/tree/master/Programacion/General)

Para reportar fallos utilizad el sistema de ["Issues"](https://github.com/Xibhu/Arduino/issues) de la web.

En mi caso utilizo el editor de texto Visual Studio Code en linux con el plugin o extensión de `PlatformIO`. El tutorial de instalación y uso es el siguiente enlace: https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/

Como utilidad añadida, se puede colocar en cada proyecto creado con `PlatforIO` la ruta de una carpeta de librerías. Al crear un proyecto, se abre el archivo `platformio.ini` y se añade la línea `lib_extra_dirs = /home/xibhu/Proyectos/arduino/Librerias/src`. Colocando la ruta que os corresponda. En linux importante colocar la barra `/` al principio de la ruta.

Para utilizar VSCode con el plugin de Arduino en linux es necesario seguir unos pasos descritos en ["InstalaciónVisualStudioCode.md"](InstalaciónVisualStudioCode.md).

Twitter: [@xibhuxan](https://twitter.com/xibhuxan)
