#include "controller.h"

template <typename ModelT>
bane::Controller<ModelT>::Controller(std::shared_ptr<ModelT> model,
                                     std::shared_ptr<View<ModelT>> view)
    : model_{model}, view_{view} {}
