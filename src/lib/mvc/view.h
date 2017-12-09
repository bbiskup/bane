#ifndef VIEW_H
#define VIEW_H

#include "model.h"

#include <memory>

namespace bane {

/// MVC view base class
template<typename ModelT>
class View {
public:
  explicit View(std::shared_ptr<ModelT> model);
  View(const View&) = delete;
  View(View&&) = delete;
  View& operator=(const View&) = delete;
  View& operator=(View&&) = delete;
  virtual ~View();

  void setModel(const ModelT& model);
  virtual void render() = 0;

private:
  std::shared_ptr<ModelT> model_;
};

} // namespace bane

#endif /* VIEW_H */
