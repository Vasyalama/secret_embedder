# изменение нативных бинарных файлов

## about
FLTK gui app written in c++ that embeds a secret string of text into a windows executable and signs it with a self signed certificate

The input text is unicode utf8 encoded

The maximum amount of code points that can be entered is 10000

By clicking on the Download button on the gui app the text is embedded into the binary, the binary is saved in the downloads folder and signed with a certificate using windows SignTool

### prerequisits: [FLTK](https://www.fltk.org/) 

### how to build project
```
git clone https://github.com/Vasyalama/secret_embedder.git
cd secret_embedder/input_secret
mkdir build
cd build
cmake ..
cmake --build .
.\inputSecret.exe
```






