#include "view.h"

template <typename Data>
bane::View<Data>::View(Model<Data>&& model) : model_{std::move(model)} {}

template <typename Data> bane::View<Data>::~View() {}

template <typename Data>
void bane::View<Data>::setModel(const Model<Data>& model) {
  model_ = model;
}
