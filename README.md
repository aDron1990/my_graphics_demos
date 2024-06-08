# My graphics demos
Репозиторий с моими графическими демо-проектами.

## Список демо-проектов
* [Triangle](Triangle/README.md)
* [Monkey](Monkey/README.md)

## Сборка:
* Скачать репозиторий командой:
```
git clone --recursive https://github.com/aDron1990/my_graphics_demos.git
```
* Перейти в репозиторий, выполнить сборку:
```
cmake -S . -B build/
cmake --build build/
```
Готовые бинарники будут находится в папке build.

## Зависимости:
* glfw
* glm
* assimp
* openGL 4.6