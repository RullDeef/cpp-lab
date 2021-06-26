#pragma once

#include <memory>
#include "Core/Math/Transform.hpp"
#include "API/Objects/Camera/ICamera.hpp"

// класс для реализации логики мигрирования между мировой и экранной системами координат

class Transformer
{
public:
    enum class State
    {
        None,
        Moving,
        Rotating,
        Zooming
    };

    Transformer() = default;
    void reset(std::shared_ptr<ICamera> camera = nullptr);
    bool isActive() const;
    Transform getResult() const;

    // имитация движения пальцем по экрану (вращение в состоянии Rotating / перенос в состоянии Moving)
    void touchStart(double x, double y);
    void touchMove(double x, double y);
    void touchEnd();
    void touchCancel();

    // имитация зума ()
    void scale(double delta);

    // смена состояния
    void switchState(State newState);

private:
    std::shared_ptr<ICamera> camera;
    Transform t;

    double xPrev = 0.0;
    double yPrev = 0.0;
    
    Matrix initTransform = Matrix::identity();
    Matrix deltaTransform = Matrix::identity();
    State state = State::None;
};
