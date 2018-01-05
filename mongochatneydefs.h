#ifndef MONGOCHATNEYDEFS_H
#define MONGOCHATNEYDEFS_H

#define PORT 4144
#define qColorToString(x) ("rgb("+QString::number(x.red())+","+QString::number(x.green())+","+QString::number(x.blue())+")")

enum State{
    ServerOn,
    ServerOff,
    Connected,
    Unconnected,
    Unknown
};

#endif // MONGOCHATNEYDEFS_H
