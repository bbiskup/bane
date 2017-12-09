#include "view.h"

template <typename ModelT>
bane::View<ModelT>::View(std::shared_ptr<ModelT> model) : model_{model} {}

template <typename ModelT> bane::View<ModelT>::~View() {}

template <typename ModelT>
void bane::View<ModelT>::setModel(const ModelT& model) {
  model_ = model;
}
