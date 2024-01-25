#include <memory>
#include <iostream>
#include "ATM.h"

int main(int, char**) {
  atm::ATM::Uni atm = std::make_unique<atm::ATM>();
  {
    atm::Card card("black", "1111");
    card.addAcount("dan", 100);
    card.addAcount("hue", 1000);
    atm->addCard(card);
  }
  {
    atm::Card card("pink", "1111");
    card.addAcount("amy", 100);
    card.addAcount("sheldon", 1000);

    atm->addCard(card);
  }

  atm->run();

  return 0;
}
