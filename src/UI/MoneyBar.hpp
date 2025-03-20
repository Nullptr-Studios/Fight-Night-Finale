#pragma once
#include "Core.hpp"
#include "UI/UIElement.hpp"
#include "UI/UINumber.hpp"

namespace Sigma {

class MoneyBar : public UIElement {
public:
  explicit MoneyBar(Sigma::id_t id, int max_digits = 7) : UIElement(id) {
    max_d = max_digits;
    numbers.resize(max_digits);
    for (int i = 0; i < max_digits; i++) {
      numbers[i] = new UINumber(0);
    }
  };
  //Set all values according to current xp value, no resize so clamp to max_digits.
  void SetNumbers(int value);

  //TODO:
  // Set all values in numbers array according to xp value
  // Correctly position them in the centre of the screen, regardless of max_digits
  // Lerp between numbers in set number once the above works
  // Add a lil money icon to it too, to the right
  // Integrate this shit with the HUD

private:
  int max_d;
  std::vector<UINumber *> numbers;
};
}