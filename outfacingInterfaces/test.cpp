//
// Created by jesse on 31/10/2023.
//

#include "test.hpp"
#include "../src/Wrappers/RenderWrapper.hpp"
#include "../src/Logger.hpp"

test::test() : renderWrapper(nullptr) {
    renderWrapper = new RenderWrapper();

    Logger::Error("This is an error boi");
    Logger::Info("This is info boi");
    Logger::Debug("This is an debug boi");
//    logger.Error("Fakka");
}

void test::Run() {
    renderWrapper->Run();
}
