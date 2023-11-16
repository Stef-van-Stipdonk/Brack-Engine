//
// Created by Olaf van den Berg on 16-11-2023.
//

#include "ContactListener.hpp"
#include "../Logger.hpp"

void ContactListener::BeginContact(b2Contact *contact) {
    Logger::GetInstance().Info("test");

    if (contact->GetFixtureA()) {

    }

}

