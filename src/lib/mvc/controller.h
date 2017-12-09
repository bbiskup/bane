#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mvc/model.h"
#include "mvc/view.h"
#include <memory>

namespace bane {

/// MVC controller base class
template <typename ModelT> class Controller {
public:
  Controller(std::shared_ptr<ModelT> model,
             std::shared_ptr<View<ModelT>> view);
  Controller(const Controller&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(const Controller&) = delete;
  Controller& operator=(Controller&&) = delete;
  const ModelT& model() const;

private:
  std::shared_ptr<ModelT> model_;
  std::shared_ptr<View<ModelT>> view_;
};

} // namespace bane

#endif /* CONTROLLER_H */
