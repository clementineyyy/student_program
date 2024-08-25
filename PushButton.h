#pragma once
#include "BasicWidget.h"
#include "Configure.h"

class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string& text = "Button", int x = 0, int y = 0, int w = 100, int h = 50);
    void show() override;
    void show2();

private:
    std::string m_text;
};

