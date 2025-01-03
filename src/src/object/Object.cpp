#include "Object.hpp"
#include <QDebug>
#include <algorithm>
#include <map>

Object::Object() { transform = std::make_unique<TransformationMatrix>(); }

Object::Object(std::unique_ptr<ObjectMemento> memento) {
  restoreMemento(std::move(memento));
}

Object::Object(const Object &origin) {
  transform = std::make_unique<TransformationMatrix>(*origin.transform);
}

void Object::accept(BaseVisitor &vis) {}

bool Object::isComposite() const noexcept { return false; }

bool Object::add(ObjectPtr &obj) { return false; }

bool Object::add(std::unique_ptr<Object> obj) { return false; }

bool Object::remove(const iterator &it) { return false; }

Object::iterator Object::begin() const noexcept { return Object::iterator(); }

Object::iterator Object::end() const noexcept { return Object::iterator(); }

Point3D Object::getPosition() const {
  return transform->apply(Point3D(0, 0, 0));
}

Point3D Object::getDirection() const {
  auto translation = transform->getNegOffset();
  return translation.apply(transform->apply(Point3D(0, 0, 1))).normalize();
}

std::unique_ptr<ObjectMemento> Object::createMemento(void) const {
  return std::make_unique<ObjectMemento>(*this);
}

void Object::restoreMemento(std::shared_ptr<ObjectMemento> memento) {
  transform = std::move(memento->get());
}

void Object::move(double dx, double dy, double dz) const {
  TranslationMatrix t(dx, dy, dz);
  *transform *= t;
}

void Object::scale(double kx, double ky, double kz) const {
  ScalingMatrix t(kx, ky, kz);
  *transform *= t;
}

void Object::rotate(double ax, double ay, double az) const {
  RotationMatrix t(ax, ay, az, true);
  *transform *= t;
}

std::shared_ptr<TransformationMatrix> Object::getTransformation() {
  return transform;
}

ObjectMemento::ObjectMemento(const Object &o) { set(o); }

void ObjectMemento::set(const Object &o) {
  transform = std::make_unique<TransformationMatrix>(*o.transform);
}

std::unique_ptr<TransformationMatrix> ObjectMemento::get() {
  return std::move(transform);
}

ObjectCaretaker::MemPtr ObjectCaretaker::get(size_t id) {
  auto &saves = saveData[id].second;
  MemPtr res = nullptr;

  if (saves.size()) {
    res = saves.back();
    saves.pop_back();
  }

  clear_expired();

  return res;
}

ObjectCaretaker::ObjectCaretaker() {}

void ObjectCaretaker::clear_expired() {
  auto tmp = saveData;

  for (auto &[id, data] : tmp)
    if (data.first.expired() || data.second.size() == 0)
      saveData.erase(id);
}

void ObjectCaretaker::set(size_t id, std::weak_ptr<Object> origin,
                          ObjectCaretaker::MemPtr memento) {
  saveData[id].first = origin;
  saveData[id].second.push_back(std::move(memento));

  clear_expired();
}

void ObjectCaretaker::clear_id(size_t id) { saveData.erase(id); }

bool ObjectCaretaker::contains(size_t id) {
  return saveData.find(id) != saveData.end();
}

void ObjectCaretaker::clear() { saveData.clear(); }
