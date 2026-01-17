rm app;
g++ -g $(find src/ -type f -iregex ".*\.cpp") src/glad.c -o app \
    -Iinclude \
    -lglfw -lGL; ./app

