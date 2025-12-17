// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <memory>   // for make_shared
#include <utility>  // for move

#include "ftxui/dom/elements.hpp"        // for Element, inverted
#include "ftxui/dom/node.hpp"            // for Node
#include "ftxui/dom/node_decorator.hpp"  // for NodeDecorator
#include "ftxui/screen/box.hpp"          // for Box
#include "ftxui/screen/screen.hpp"       // for Pixel, Screen

namespace ftxui {

namespace {
class Inverted : public NodeDecorator {
 public:
  using NodeDecorator::NodeDecorator;

  void Render(Screen& screen) override {
    Node::Render(screen);
    for (int y = box_.y_min; y <= box_.y_max; ++y) {
      for (int x = box_.x_min; x <= box_.x_max; ++x) {
        screen.PixelAt(x, y).inverted ^= true;
      }
    }
  }
};
}  // namespace

/// @brief Add a filter that will invert the foreground and the background
/// colors.
/// @ingroup dom
Element inverted(Element child) {
  return std::make_shared<Inverted>(std::move(child));
}

// TODO TabRing
// TODO PassiveContainer
// TODO try this out.
/// @brief Add a filter that will invert the foreground and the background
/// colors for a given column and row.
/// @ingroup dom
Decorator crosshairInvert(int x, int y) {
  class Impl : public NodeDecorator {
   public:
    Impl(Element child, int x, int y)
        : NodeDecorator(std::move(child)), x_(x), y_(y) {}

    using NodeDecorator::NodeDecorator;

    void Render(Screen& screen) override {
      Node::Render(screen);
      screen.PixelAt(x_, y_).inverted ^= true;
      for (int y = box_.y_min; y <= box_.y_max; ++y) {
        if (y == y_) {
          continue;
        }
        screen.PixelAt(x_, y).inverted ^= true;
      }
      for (int x = box_.x_min; x <= box_.x_max; ++x) {
        if (x == x_) {
          continue;
        }
        screen.PixelAt(x, y_).inverted ^= true;
      }
    }

   private:
    const int x_;
    const int y_;
  };

  return [x, y](Element child) {
    return std::make_shared<Impl>(std::move(child), x, y);
  };
}

}  // namespace ftxui
