#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include "DataBase.h"
namespace atm {
class ATM {
public:
  using Uni = std::unique_ptr<ATM>;

  ATM()
    : end_{false} {
    db_ = std::make_unique<Database>();
  }
  ~ATM() = default;

  void run() {
    while (true) {
      std::string id = "1000";

      showMenu();

      std::cin >> id;

      if (id == "1") {
        end_ = false;
        break;
      }

      Card card;
      insertCard(id, card);

    }
  }

  void addCard(Card& in) { return db_->addCard(in); }

protected:
  void showMenu() {
    std::cout << "---- MENU ----\n";
    std::cout << "enter 1 to exit or \n";
    std::cout << "intert card : \n";
  }

  bool insertCard(const std::string& id, Card& card) {
    if (db_->queryCard(id, card)) {
      std::cout << "endter passowrd" << std::endl;
      std::string pass;

      std::cin >> pass;
      return true;
    }
    return false;
  }

  
  bool selectAccount(const int& idx) {}

protected:
  Database::Uni db_;
  bool          end_;
  std::thread   thread_;
};
}  //namespace atm