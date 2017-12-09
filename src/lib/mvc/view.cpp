#include "view.h"

template <typename Data>
bane::View<Data>::View(const Model<Data>& model) : model_{model} {}

template <typename Data>
void bane::View<Data>::setModel(const Model<Data>& model) {
  model_ = model;
}
