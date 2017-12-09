#ifndef VIEW_H
#define VIEW_H

#include "model.h"

namespace bane {

/// MVC view base class
template<typename Data>
class View {
public:
  explicit View(const Model<Data>& model);
  void setModel(const Model<Data>& model);
  virtual void render() = 0;

private:
  Model<Data> model_;
};

} // namespace bane

#endif /* VIEW_H */
