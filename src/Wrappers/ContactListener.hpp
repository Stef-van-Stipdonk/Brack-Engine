//
// Created by Olaf van den Berg on 16-11-2023.
//

#ifndef BRACKOCALYPSE_CONTACTLISTENER_HPP
#define BRACKOCALYPSE_CONTACTLISTENER_HPP


#include "../../lib/Box2d/include/box2d/box2d.h"

class ContactListener : public b2ContactListener {
    void BeginContact(b2Contact *contact) override;

    void EndContact(b2Contact *contact) override;

};


#endif //BRACKOCALYPSE_CONTACTLISTENER_HPP
