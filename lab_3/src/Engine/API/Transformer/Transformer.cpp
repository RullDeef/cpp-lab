#include "Transformer.hpp"

constexpr auto rotationSensetivity = 0.001;
constexpr auto translationSensetivity = 0.001;


void Transformer::reset(std::shared_ptr<ICamera> camera)
{
    this->camera = camera;
    t = Transform();
    deltaTransform = Transform();
}

bool Transformer::isActive() const
{
    return state != State::None;
}

Transform Transformer::getResult() const
{
    return deltaTransform;
}

void Transformer::touchStart(double x, double y)
{
    xPrev = x;
    yPrev = y;

    initTransform = t;
    deltaTransform = Transform();
}

void Transformer::touchMove(double x, double y)
{
    if (state == State::Moving)
    {
        deltaTransform = Matrix::translation({
            -(x - xPrev) * translationSensetivity,
            (y - yPrev) * translationSensetivity,
            0.0
        });

        //if (camera)
        //    deltaTransform = camera->getProjectionMatrix().inverse() * deltaTransform;

        t = initTransform * deltaTransform;
    }
    else if (state == State::Rotating)
    {
        deltaTransform = Matrix::rotation({ 0.0, 1.0, 0.0 }, (x - xPrev) * rotationSensetivity)
            * Matrix::rotation({ 1.0, 0.0, 0.0 }, (y - yPrev) * rotationSensetivity);
        t = initTransform * deltaTransform;
    }
    xPrev = x;
    yPrev = y;
}

void Transformer::touchEnd()
{
    state = State::None;
}

void Transformer::touchCancel()
{
    t = initTransform;
    state = State::None;
}

void Transformer::scale(double delta)
{
    if (state == State::Zooming)
    {
        double f = 1.0 + delta;
        t = initTransform * Matrix::scaling({ f, f, f });
    }
}

void Transformer::switchState(State newState)
{
    state = newState;
}
