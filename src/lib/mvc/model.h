#ifndef MODEL_H
#define MODEL_H

#include <boost/signals2.hpp>

namespace bane {

/// MVC Model base class
class Model {
public:
  Model(){}
  Model(const Model&) = delete;
  Model(Model&&) = delete;
  Model& operator=(const Model&) = delete;
  Model& operator=(Model&&) = delete;

  using OnChange = boost::signals2::signal<void()>;
  using OnChangeSlotType = typename OnChange::slot_type;

  boost::signals2::connection doOnChange(const OnChangeSlotType& slot);

private:
  OnChange onChange_;
};

} // namespace bane

#endif /* MODEL_H */
