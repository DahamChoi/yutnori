#include "ConsoleGraphics.h"

#include <map>
#include <iostream>

void ConsoleGraphics::ClearBuffer()
{
    _Buffer =
    {
        "..----..----..----..----..----..",
        "..    ..    ..    ..    ..    ..",
        "| \\                          / |",
        "|  \\                        /  |",
        "|   \\                      /   |",
        "|    ..                  ..    |",
        "..   ..                  ..   ..",
        "..     \\                /     ..",
        "|       \\              /       |",
        "|        \\            /        |",
        "|         ..        ..         |",
        "|         ..        ..         |",
        "..          \\      /          ..",
        "..           \\    /           ..",
        "|             \\  /             |",
        "|              ..              |",
        "|              ..              |",
        "|             /  \\             |",
        "..           /    \\           ..",
        "..          /      \\          ..",
        "|         ..        ..         |",
        "|         ..        ..         |",
        "|        /            \\        |",
        "|       /              \\       |",
        "..     /                \\     ..",
        "..   ..                  ..   ..",
        "|    ..                  ..    |",
        "|   /                      \\   |",
        "|  /                        \\  |",
        "| /                          \\ |",
        "..    ..    ..    ..    ..    ..",
        "..----..----..----..----..----.."
    };

}

void ConsoleGraphics::Draw()
{
    for (const auto& line : _Buffer)
    {
        std::cout << line << '\n';
    }
}

void ConsoleGraphics::DrawPoint(int x, int y, char data)
{
    _Buffer[y][x] = data;
}
