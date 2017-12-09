#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace bane {

/// MVC controller base class
template <typename Data> class Controller {
    public:
  Controller(const Model<Data>& model, const View<Data>& data);

    private:

};

} // namespace bane

#endif /* CONTROLLER_H */
