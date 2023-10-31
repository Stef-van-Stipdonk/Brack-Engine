//
// Created by jesse on 31/10/2023.
//

#include "test.hpp"
#include "../src/Wrappers/RenderWrapper.hpp"

test::test() : renderWrapper(nullptr) {
    renderWrapper = new RenderWrapper();
}

void test::Run() {
    renderWrapper->Run();
}
