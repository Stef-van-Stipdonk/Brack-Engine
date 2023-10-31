//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_TEST_HPP
#define BRACK_ENGINE_TEST_HPP


class RenderWrapper;

class test {
public:
    test();

    ~test() = default;

    void Run();

private:
    RenderWrapper *renderWrapper;
};


#endif //BRACK_ENGINE_TEST_HPP
