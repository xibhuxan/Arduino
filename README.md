
# Arduino
Los códigos están pendientes de revisión, reestructuración, y edición. Progresivamente se irá mejorando.

Aquí se colocarán distintos proyectos basados en arduino y sus sensores.

El repositorio está ordenado de la siguiente manera:

La carpeta de ["RecursosProgramacion"](RecursosProgramacion) con información útil en forma de PDF(se recomienda encarecidamente su lectura) con tutoriales, ejercicios básicos e imágenes del arduino. Estos PDF pertenecen a sus respectivos autores.

La carpeta de ["EjemplosBasicosDeUso"](EjemplosBasicosDeUso) contiene carpetas de todos los sensores y actuadores, en cada uno varios elementos. Su archivo fritzing del componente si fuera necesario, archivo de conexionado, imagen de conexionado, y un código básico de uso.

La carpeta de ["ProyectosSimples"](ProyectosSimples) contiene distintos ejemplos de los sensores y actuadores, tanto individual como en conjunto. Siendo utilizados de distintas maneras.

La carpeta de ["ProyectosComplejos"](ProyectosComplejos) son aquellos que se consideran más elaborados, con código más complejo o largo.

La carpeta de ["Librerias"](Librerias) contiene las librerias utilizadas, ya sean oficiales como no oficiales. Las creadas por mi se caracterizan por tener XB en el nombre. Para saber las librerías que se necesitan, hay que leer las líneas que ponen `#include <LIBRERIA.h>` en cada código. Si no pone nada no se necesitan librerías extras. Si lo pone, puede que ya vengan incluidas con el programa de arduino, si al verificar el código da error de libreria no encontrada, entonces hay que descargarla, bien desde el propio gestor de librerias del arduino, desde aquí, de su página oficial, o de donde la encontreis. Al tener el zip, se descomprime para tener una carpeta, y esta se debe colocar en `carpetaDeUsuario/Arduino/libraries`.

El archivo de ["EnlacesInterés.md"](EnlacesInterés.md) contiene distintos enlaces de tutoriales, módulos y más cosas.

Para reportar fallos utilizad el sistema de ["Issues"](https://github.com/Xibhu/Arduino/issues) de la web. O bien el correo electrónico `xibhuxan@gmail.com`.

Los códigos sacados de terceras personas, mantendrán los créditos dentro del mismo, con la información que hayan dejado como páginas web.

En mi caso utilizo el editor de texto Visual Studio Code en linux/debian con el plugin o extensión de Arduino hecho por microsoft.

Para utilizar VSCode en linux es necesario seguir unos pasos descritos en ["InstalaciónVisualStudioCode.md"](InstalaciónVisualStudioCode.md).
