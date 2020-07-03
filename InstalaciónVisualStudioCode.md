
# Instalación de Visual Studio Code en linux 

Hacer el símil de las partes útiles para windows, desde "Coniguración general vscode, settings.json"

Esta configuración se ha probado primero en `Debian 10` (siendo necesaria la parte OPCIONAL), con `Fedora 32` (NO usando la parte OPCIONAL) y con `POP_OS 20.04` (NO usando la parte OPCIONAL).

Primero es necesario instalar el programa oficial de arduino. Para ello se va a la página oficial, y descargar para linux 64 bits. https://www.arduino.cc/en/Main/Software

Una vez descargado se verá un archivo comprimido tar.xz, por lo tanto hay que descomprimirlo, tras ello aparecerá una carpeta con el contenido del programa.

Ahora se copia la carpeta a /opt/ por ejemplo, es una carpeta en la que se pueden colocar programas.  
`sudo cp -R /arduino-1.8.10/ /opt/`  
Se le dan los permisos de usuario.  
`sudo chown $USER:$USER /opt/arduino-1.8.10/`

Se instala VSCode desde sitios oficiales como su página oficial. https://code.visualstudio.com/ y seguir los pasos para la distribución. O bien desde repositorios de la distribución si estuviera el paquete.

Ya con vscode, se instala la extensión de Arduino oficial de Microsoft, en su buscador se escribe Arduino y una de las primeras opciones. Además se instalará la extensión para C/C++.

Con todo instalado ahora hay que decirle al VSCode dónde está el arduino para que pueda acceder a sus recursos. Para ello se va a "File, Preferences, Settings, User, Extensions, Arduino configuration" y en "Arduino path" se coloca `/opt/arduino-1.8.10/` o la ruta que corresponda.

# Opcional

Esta parte solo ha hecho falta con debian 10.

Con esto ya se tiene acceso a las funciones de verificar, subir, initialize, configurar placa, etc. Ahora para usarlo como un verdadero IDE es necesario realizar unos pasos extras, ya que de normal va a dar unos errores de que no encuentra las librerias que se utilizan, además del autocompletado y formateo de texto.

Lo primero es instalar en linux el siguiente programa.  
`sudo apt install clang-format-8`

Se busca el binario con el siguiente comando, y donde esté el archivo lo pegamos en el visual studio.  
`whereis clang-format-8`

Se va a "File, Preferences, Settings, User, Extensions, C/C++" y en cualquier `edit in settings.json` (es siempre el mismo archivo) se añade lo siguiente "C_Cpp.clang_format_path": "/usr/bin/clang-format-8" en mi caso, con esto ya podemos formatear el texto. (A veces no es necesario)

Si da un error de que no se encuentra libtinfo.so.5 o similar, se puede realizar el siguiente comando.  
`sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so /usr/lib/x86_64-linux-gnu/libtinfo.so.5`

(Acaba opcional)

---

Para que desaparezcan los errores de libreria son dos pasos, primero añadir las rutas por defecto en un fichero, y luego en cada proyecto utilizar las rutas por defecto.

# Coniguración general vscode, settings.json

Primero se va de nuevo al archivo settings "File, Preferences, Settings, User, Extensions, C/C++" y se pisa en cualquier `edit in settings.json`. Y se deja a algo similar a los siguiente, todo dependerá de vuestras rutas reales y usuario. Estas rutas solucionan los errores de librería, y un típico error con el objeto Serie.

Esta configuración solo se hace UNA vez y no hay necesidad de tocarlo más.


```
{
    "arduino.path": "/opt/arduino-1.8.12/",
    "C_Cpp.default.includePath": ["${workspaceRoot}",
        "/opt/arduino-1.8.12/hardware/arduino/avr/**",
        "/opt/arduino-1.8.12/tools/**",
        "/opt/arduino-1.8.12/hardware/tools/**",
        "/opt/arduino-1.8.12/libraries/**",
        "/home/xibhu/Arduino/libraries/**"],
    "C_Cpp.default.forcedInclude": ["/opt/arduino-1.8.12/hardware/arduino/avr/cores/arduino/Arduino.h"],
    "C_Cpp.default.defines": ["ARDUINO=10800",
        "USBCON"
    ],
    "arduino.defaultBaudRate": 9600,
    "arduino.additionalUrls": ""
}
```

# Tutorial simple de creación de proyecto de arduino

Cada proyecto debe estar en una carpeta separada, y con un solo `miPrograma.ino`, pudiendo tener las librerías que se quieran a parte. 

Cuando se quiere acceder a las opciones de arduino se pisa `F1` y se escribe `arduino`, aparecerán las opciones. O bien escribir directamente la opción que se busca como `initialize`. Se pisa `ENTER` para confirmar la selección.

Los pasos a seguir con cada proyecto tras haber configurado bien el `settings.json` son estos.

- Crear carpeta.
- Abrir vscode.
- File -> Open folder.
- F1 -> initialize.
- Darle nombre al `.ino` ejemplo `Main.ino`.
- Elegir el arduino `UNO` por ejemplo.
- F1 -> Select Serial Port. Y saldrán todos los dispositivos serial, elegir uno que contenga `USB0` o similar.
- Si se quiere subir un proyecto a arduino: F1 -> upload.
- Si se quiere abrir el puerto serie para ver los `Serial.print()`: F1 -> Open Serial Monitor.

# Por cada proyecto

Cuando se abre una carpeta que se convertirá en un proyecto de arduino (con File -> open folder) y realizar la configuración básica, esta carpeta concreta contendrá la configuración de arduino. Cuando se le da a `initialize` y se completa, automáticamente se crea una carpeta `.vscode` con un archivo llamado `c_cpp_properties.json`, este archivo será necesario editarlo en cada proyecto cambiando todas estas líneas, y dejarlo a algo similar a esto. Copiar y pegar.

Esta configuración hay que pponerla por CADA proyecto de arduino.

```
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${default}"
            ],
            "forcedInclude": [
                "${default}"
            ],
            "compilerPath": "${default}"
        }
    ],
    "version": 4
}
```
Otro archivo que se crea en `.vscode` es el de `arduino.json`, este contendrá la configuración del arduino, como modelo de la placa, usb a usar. Una de las opciones que se puede añadir es la de output para que reutilice archivos compilados y tarde menos en subir los programas. Y para que deje de dar un aviso cada vez que se compila.

Esta configuración al igual que la inmediata anterior, se realiza por CADA proyecto de arduino. Esta línea de `output` se debe AÑADIR a lo ya existente.

```
{
"output": "build"
}
```

# Configuración de permisos USB

Para que vscode tenga acceso a los usb, el usuario debe tener los permisos. 

`sudo adduser $USER dialout`  
O bien:  
`sudo usermod -a -G dialout $USER`  

Tras realizar UNO de los comandos anteriores (no pasa nada si los haces varias veces), reiniciar el pc, no sirve cerrar sesión y abrirla.  

Comandos extras que pueden ser útiles al utilizar dispositivos USB:  
`sudo usermod -a -G uucp $USER`  
`sudo usermod -a -G lock $USER`  
`sudo usermod -a -G tty $USER`  

---

Todo lo explicado es para que funcione en mi pc, a ustedes es posible que solo necesiteis parte, o incluso algo distinto para hacerlo funcionar o solucionar los errores. Y recordar editar las rutas con las propias.