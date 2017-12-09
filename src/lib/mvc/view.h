#ifndef VIEW_H
#define VIEW_H

#include "model.h"

#include <memory>

namespace bane {

/// MVC view base class
template<typename Data>
class View {
public:
  explicit View(Model<Data>&& model);
  View(const View&) = delete;
  View(View&&) = delete;
  View& operator=(const View&) = delete;
  View& operator=(View&&) = delete;
  virtual ~View();

  void setModel(const Model<Data>& model);
  virtual void render() = 0;

private:
  std::unique_ptr<Model<Data>> model_;
};

} // namespace bane

#endif /* VIEW_H */
