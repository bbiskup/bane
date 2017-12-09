#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace bane {

/// MVC controller base class
template <typename Data> class Controller {
public:
  Controller(const Model<Data>& model, const View<Data>& data);
  View(const View&) = delete;
  View(View&&) = delete;
  View& operator=(const View&) = delete;
  View& operator=(View&&) = delete;

private:
};

} // namespace bane

#endif /* CONTROLLER_H */
