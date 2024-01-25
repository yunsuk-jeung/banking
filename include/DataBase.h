#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <unordered_map>

namespace atm {
class Account {
public:
  Account() = default;
  Account(const std::string& id, uint32_t money = 0)
    : id_{id}
    , money_{money} {}
  ~Account() = default;

  const uint32_t Balance() const { return money_; }
  void           Deposit(uint32_t money) { money_ += money; }
  bool           Withdraw(uint32_t money) {
    if (money > money_)
      return false;

    money_ -= money;
  }

  const std::string& id() const { return id_; }

protected:
  std::string id_;
  uint32_t    money_;
};

class Card {
public:
  Card()
    : id_{""} {}

  Card(const std::string& id, const std::string& password)
    : id_{id}
    , password_{password} {}

  ~Card() = default;
  bool checkPassword(const std::string& password) {
    if (password == password_) {
      return true;
    }
    std::cout << "invalid password" << std::endl;
    return false;
  }

  void addAcount(const std::string& id, uint32_t money = 0) {
    std::hash<std::string> hasher;
    size_t                 key = hasher(id);

    if (!accounts_.count(key)) {
      accounts_.insert({
        key,
        {id, money}
      });
    }
    else {
      std::cout << "choose different id for account" << std::endl;
    }
  }

  void deleteAccount(const std::string& id) {
    std::hash<std::string> hasher;
    size_t                 key = hasher(id);
    if (accounts_.count(key)) {
      accounts_.erase(key);
    }
    else {
      std::cout << "deleting non-existing account" << std::endl;
    }
  }

  bool queryAccount(const std::string& id, Account& out) {
    std::hash<std::string> hasher;
    size_t                 key = hasher(id);
    if (accounts_.count(key)) {
      out = accounts_[key];
      return true;
    }
    std::cout << "non existing account" << std::endl;
    return false;
  }

  void showAccounts() {
    for (auto& [key, account] : accounts_) {
      std::cout << account.id() << " - Balance : " << account.Balance() << std::endl;
    }
  }

  const std::string& id() const { return id_; }

protected:
  std::string                         id_;
  std::string                         password_;
  std::unordered_map<size_t, Account> accounts_;
};

class Database {
public:
  using Uni   = std::unique_ptr<Database>;
  Database()  = default;
  ~Database() = default;

  void addCard(const Card& card) {
    auto                   id = card.id();
    std::hash<std::string> hasher;
    size_t                 key = hasher(id);
    if (!cards_.count(key)) {
      cards_.insert({key, card});
    }
  }

  bool queryCard(const std::string& id, Card& out) {
    std::hash<std::string> hasher;
    size_t                 key = hasher(id);
    if (cards_.count(key)) {
      out = cards_[key];
      return true;
    }
    std::cout << "non existing card" << std::endl;
    return false;
  }

protected:
  std::unordered_map<size_t, Card> cards_;
};
}  //namespace atm