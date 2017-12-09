#ifndef MODEL_H
#define MODEL_H

#include <boost/signals2.hpp>

namespace bane {

/// MVC Model base class
template<typename Data>
class Model {
public:
  using OnChange = boost::signals2::signal<void(const Data&)>;
  using OnChangeSlotType = typename OnChange::slot_type;

  boost::signals2::connection doOnChange(const OnChangeSlotType& slot);

private:
  OnChange onChange_;
  Data data_;
};

} // namespace bane

#endif /* MODEL_H */
