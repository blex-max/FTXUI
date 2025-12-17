// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <ftxui/dom/elements.hpp>  // for text, operator|, inverted, Fit, hbox, Element
#include <ftxui/screen/screen.hpp>  // for Full, Screen

#include "ftxui/dom/node.hpp"      // for Render

int main() {
  using namespace ftxui;
  auto document = vbox(
    hbox(text("1"), text("2"), text("3"), text("4"), text("5")),
    hbox(text("1"), text("2"), text("3"), text("4"), text("5")),
    hbox(text("1"), text("2"), text("X"), text("4"), text("5")),
    hbox(text("1"), text("2"), text("3"), text("4"), text("5")),
    hbox(text("1"), text("2"), text("3"), text("4"), text("5"))
  ) | crosshairInvert(2, 2);
  auto screen = Screen::Create(Dimension::Fit(document), Dimension::Fit(document));
  Render(screen, document);
  screen.Print();

  return 0;
}
