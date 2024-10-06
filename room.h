#ifndef ROOM_H
#define ROOM_H

#include <string>

struct Room
{
public:
    Room();
    ~Room();

private:
    unsigned long id;
    std::string label;
};

#endif // ROOM_H
