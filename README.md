# Arduino
Los códigos están pendientes de revisión, reestructuración, y edición. Progresivamente se irá mejorando.

Aquí se colocarán distintos proyectos de código basados en arduino y sus sensores.

El repositorio está separado en varias carpetas:

La carpeta de ["Recursos"](Recursos) con información útil en forma de PDF(se recomienda encarecidamente su lectura) con tutoriales, ejercicios básicos e imágenes del arduino.

La carpeta de ["FritzingParts"](FritzingParts) contendrá componentes que no vienen de serie en el programa de esquemas Fritzing, teniendolos todos en un mismo lugar.

La carpeta de ["ProyectosSimples"](ProyectosSimples) los cuales es la utilización de los sensores y actuadores casi siempre de forma individual, junto con su código.

La carpeta de ["ProyectosComplejos"](ProyectosComplejos) son aquellos más elaborados, con varios sensores y/o actuadores.

La carpeta de ["Librerias"](Librerias) contiene las librerias utilizadas, ya sean oficiales como no oficiales. Las creadas por mi se caracterizarán por tener Xibhu o XB en el nombre. Para saber las librerías que se necesitan, hay que leer las líneas que ponen `#include <LIBRERIA.h>` en cada código. Si no pone nada no se necesitan librerías extras. Si lo pone, puede que ya vengan incluidas con el programa de arduino, si al verificar el código da error de libreria no encontrada, entonces hay que descargarla, bien desde el propio gestor de librerias del arduino, o desde aquí.

El archivo de ["EnlacesInterés.md"](EnlacesInterés.md) contiene distintos enlaces de tutoriales, módulos y más cosas.

En mi caso utilizo el editor de texto Visual Studio Code en linux/debian con el plugin o extensión de Arduino hecho por microsoft.

Para reportar fallos utilizad el sistema de ["Issues"](https://github.com/Xibhu/Arduino/issues) de la web. O bien el correo electrónico `xibhuxan@gmail.com`.

## Estandarización en código
Para que el código sea más legible, se asignarán el mismo tipo a las variables en cada caso.

- Definición de pines "const byte"
- Definición de variables de estado (para botones) "byte"
- Definición variables normales "int"


Los códigos sacados de terceras personas, mantendrán los créditos dentro del mismo, con la información que hayan dejado como páginas web.

Para utilizar VSCode en linux es necesario seguir unos pasos descritos en ["Pasos a seguir"](InstalaciónVisualStudioCode.md) y en ["Usar usb"](https://github.com/Xibhu/Tutoriales/blob/master/Sistemas%20Operativos/Linux/Comandos.md)
