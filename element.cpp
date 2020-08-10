#include "element.h"
#include "scene.h"

Element::Element(Scene* scene, ElementShape shape) : _scene(scene),
    _shape(shape)
{

}

Element* Element::create(ElementShape shape)
{
    auto scene = Scene::getActiveScene();
}
