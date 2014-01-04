#pragma once

#include "thirdparty/sigslot.h"
#include "misc/Singleton.h"

class Input_Class
{
public:
    enum Key {
        None,
        Left,
        Right,
        Jump,
        Attack,
        Freeze
    };

    Input_Class();
    virtual ~Input_Class();

public:
    sigslot::signal1<Key> press;
    sigslot::signal1<Key> release;

    // TODO: connectable signal pressed()
    //       connectable signal connected(joypad id)
    //       joypad and keyboard independence
    //       possibility to set input device
};

typedef Singleton<Input_Class> Input;
