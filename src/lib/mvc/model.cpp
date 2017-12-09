#include "model.h"

/// Handle change event
template<typename Data>
boost::signals2::connection
bane::Model<Data>::doOnChange(const OnChangeSlotType& slot) {
  return onChange_.connect(slot);
}
