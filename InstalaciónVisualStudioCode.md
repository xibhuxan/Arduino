
# Instalación de Visual Studio Code en linux (debian 10) para programar en Arduino (hacer símil para windows)

Primero es necesario instalar el programa oficial de arduino. Para ello se va a la página oficial, y descargar para linux 64 bits. https://www.arduino.cc/en/Main/Software

Una vez descargado se verá un archivo comprimido tar.xz, por lo tanto hay que descomprimirlo, tras ello aparecerá una carpeta con el contenido del programa.

Ahora se copia la carpeta a /opt/ para tenerlo ordenado.  
`sudo cp -R /arduino-1.8.10/ /opt/`  
Se le dan los permisos de usuario.  
`sudo chown $USER:$USER /opt/arduino-1.8.10/`

Se instala VSCode desde sitios oficiales como su página oficial. https://code.visualstudio.com/  
Ya instalado se instala la extensión de Arduino oficial de Microsoft, se busca en su buscador. Además se instalará la extensión para C/C++.

Con todo instalado ahora hay que decirle al VSCode dónde está el arduino para que pueda acceder a sus recursos. Para ello se va a "File, Preferences, Settings, User, Extensions, Arduino configuration" y en "Arduino path" se coloca `/opt/arduino-1.8.10/` o la ruta que corresponda.

Con esto ya se tiene acceso a las funciones de verificar, subir, initialize, configurar placa, etc. Ahora para usarlo como un verdadero IDE es necesario realizar unos pasos extras, ya que de normal va a dar unos errores de que no encuentra las librerias que se utilizan, además del autocompletado y formateo de texto.

Lo primero es instalar en linux el siguiente programa.  
`sudo apt install clang-format-8`

Se busca el binario con el siguiente comando, y donde esté el archivo lo pegamos en el visual studio.  
`whereis clang-format-8`

Se va a "File, Preferences, Settings, User, Extensions, C/C++" y en cualquier `edit in settings.json` (es siempre el mismo archivo) se añade lo siguiente "C_Cpp.clang_format_path": "/usr/bin/clang-format-8" en mi caso, con esto ya podemos formatear el texto. (A veces no es necesario)

Si da un error de que no se encuentra libtinfo.so.5 o similar, se puede realizar el siguiente comando.  
`sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so /usr/lib/x86_64-linux-gnu/libtinfo.so.5`

Para que desaparezcan los errores de libreria son dos pasos, primero añadir las rutas por defecto en un fichero, y luego en cada proyecto utilizar las rutas por defecto.

Primero se va de nuevo al archivo settings "File, Preferences, Settings, User, Extensions, C/C++" y se pisa en cualquier `edit in settings.json`. Y se deja a algo similar a los siguiente, todo dependerá de vuestras rutas reales y usuario. Las más importantes son las que empiezan con C_Cpp, estas solucionan los errores de librería, y un típico error con el objeto Serie.

```
{
    "arduino.path": "/opt/arduino-1.8.9/",
    "window.zoomLevel": 1,
    "C_Cpp.default.intelliSenseMode": "gcc-x64",
    "C_Cpp.default.cppStandard": "c++17",
    "C_Cpp.default.cStandard": "c11",
    "C_Cpp.default.includePath": ["${workspaceRoot}",
        "/opt/arduino-1.8.9/hardware/arduino/avr/**",
        "/opt/arduino-1.8.9/tools/**",
        "/opt/arduino-1.8.9/hardware/tools/**",
        "/opt/arduino-1.8.9/libraries/**",
        "/home/xibhu/Arduino/libraries/**"],
    "C_Cpp.default.forcedInclude": ["/opt/arduino-1.8.9/hardware/arduino/avr/cores/arduino/Arduino.h"],
    "C_Cpp.default.defines": ["ARDUINO=10800",
        "USBCON"],
    "C_Cpp.clang_format_path": "/usr/bin/clang-format-7"
}
```

Cuando se abre una carpeta de proyecto que contendrá los archivos de arduino, y se le da initialize, se crea una carpeta .vscode con un archivo llamado c_cpp_properties.json, este archivo será necesario editarlo en cada proyecto cambiando una línea, y dejarlo a algo similar a esto.

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
Otro archivo que se crea es el de arduino.json, este contendrá la configuración del arduino, como modelo de la placa, usb a usar. Una de las opciones que se puede añadir es la de output para que reutilice archivos compilados y tarde menos en subir los programas.
```
{
"output": "build"
}
```


Para que vscode tenga acceso a los usb, el usuario debe tener los permisos. Tras esto, reiniciar.
`sudo adduser yourUserName dialout`  
O bien:  
`sudo usermod -a -G dialout MY_USER_NAME`

Todo lo explicado es para que funcione en mi pc, a ustedes es posible que solo necesiteis parte, o incluso algo distinto para hacerlo funcionar o solucionar los errores. Y recordar editar las rutas con las propias.
